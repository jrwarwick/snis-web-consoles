/* SPDX-License-Identifier: GPL-2.0-or-later
 * Based on example simple API server which was Copyright (c) 2020 Cesanta Software Limited
 * https://github.com/cesanta/mongoose/blob/7.3/examples/http-restful-server/main.c
 *
 * Modified into http_client_bridge.c by justin.warwick@gmail.com
 * HTTP server example. This server serves both static and limited dynamic content
 * to bridge into https://smcameron.github.io/space-nerds-in-space/#speech-recognition
 * It opens two ports: plain HTTP on port 8000 and HTTP on port 8443.
 * It implements the following endpoints:
 *    /SHIP/NAVIGATION
 *
 *    /api/f1 - respond with JSON string {"result": 123}
 *    /api/f2/:id - wildcard example, respond with JSON string {"result": "URI"}
 *
 *    any other URI serves static files from s_root_dir
 *
 * To enable SSL/TLS (using self-signed certificates in PEM files),
 *    1. make MBEDTLS_DIR=/path/to/your/mbedtls/installation
 *    2. curl -k https://127.0.0.1:8443
 *
 */

/* Consider the scenario of non-responsive controls (in-game), as well as bug/svc-fail.
 * what about feedback from gameserver? stuff like control disable, custom labeling, hypoxia effects, powerfail
 *
 * TODO: overall style/formatting to match snis code corpus
 */

#include <stdio.h>
#include <string.h>
#include "mongoose.h"

#define SNIS_NL_FIFO "/tmp/snis-natural-language-fifo"
#define SNIS_SOUNDS_PATH "/usr/local/share/snis/sounds/"  /* actually we probably don't need this right? just client side? */
#define MAX_COMMAND_LENGTH  1000

/*TODO: port number default and arg override*/
static const char *s_http_addr = "http://0.0.0.0:8000";    /* HTTP port  */
static const char *s_https_addr = "https://0.0.0.0:8443";  /* HTTPS port */
static const char *s_root_dir = ".";


static int insert_fifo_message(char *message)
{
	FILE *fifo;
	char clean_message[100];

	fifo = fopen(SNIS_NL_FIFO, "w");
	if (!fifo) {
		fprintf(stderr, "%s: Failed to open '%s': %s\n",
				"http_client_bridge", SNIS_NL_FIFO, strerror(errno));
		return 1;
	}

	int offset = strlen("/SHIP/");
	int i = offset;

	for (i = offset; i <= (int)strlen(message) ; i++) {
		clean_message[i - offset] = (message[i] == '/') ? ' ' : toupper(message[i]);
	}
	clean_message[i+1] = '\n';
	clean_message[i+2] = '\0';
	fprintf(fifo, clean_message);
	fclose(fifo);
	return 0;
}


/*TODO: signal handling */
/* We use the same event handler function for HTTP and HTTPS connections */
/* request_data is NULL for plain HTTP, and non-NULL for HTTPS */
static void request_handler(struct mg_connection *c, int ev, void *ev_data, void *request_data)
{
	/*
	 * http://hostname/SHIPNAME/STATIONNAME/COMMAND/PARAM=VAL
	 * http://hostname/SHIPNAME/STATIONNAME/NOUN/VERB?param=value
	 * http://foo.bar/ASTRISK/NAVIGATION/RUDDER/-1
	 * http://foo.bar/ASTRISK/SCIENCE/LRS/PULSE
	 */
	char control_spec[100];

	if (ev == MG_EV_ACCEPT && request_data != NULL) {
		struct mg_tls_opts opts = {
			/*.ca = "ca.pem",  */      /* Uncomment to enable two-way SSL */
			.cert = "server.pem",     /* Certificate PEM file */
			.certkey = "server.pem",  /* This pem conains both cert and key */
		};
		mg_tls_init(c, &opts);
	} else if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		/*todo:stat /tmp/snis-natural-language-fifo , resp: "ctrl offline" if missing */
		/*todo:restrict referrer to this host? cors?*/
		if (mg_http_match_uri(hm, "/CMD/QUIT")) {
			mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);  /*TODO:  quit/restart?*/
		} else if (mg_http_match_uri(hm, "/api/f2/*")) {
			mg_http_reply(c, 200, "", "{\"result\": \"%.*s\"}\n", (int) hm->uri.len, hm->uri.ptr);
		} else if (mg_http_match_uri(hm, "/SHIP/NAVIGATION/*/*")) {  /* Serve pseudo-RESTfully */
			/*strlcpy(control_spec,&hm->uri[5],*/
			/* copy string, strip /SHIP/ prefix, uppercase,
			 * remove anything not [A-Z/], replace '/' with ' ', send to NL fifo.
			 */
			snprintf(control_spec, (int)hm->uri.len+1, hm->uri.ptr, "(%s)\n");
			fprintf(stdout, "  [CMD]:%s\n", control_spec);

			/*insert_fifo_message("throttle x");*/
			insert_fifo_message(control_spec);
			mg_http_reply(c, 200, "", "{\"command\": \"%.*s\",\"result\": \"ACK\"}\n",
					(int) hm->uri.len, hm->uri.ptr);
		} else {
			struct mg_http_serve_opts opts = {.root_dir = s_root_dir};

			mg_http_serve_dir(c, ev_data, &opts);

			if (hm->uri.ptr) {
				snprintf(control_spec, (int)hm->uri.len + 1, hm->uri.ptr, "(%s)\n");
				fprintf(stdout, "  static srv:%s\n", control_spec);
			}
		}
	}
	(void) request_data;
}


int main(int argc, char **argv)
{
	struct mg_mgr mgr;    /* Event manager */

	if (argc > 2) {
		fprintf(stderr, "Arguments not yet implemented.");
	}

	mg_log_set("2");     /* Set to 3 to enable debug */
	mg_mgr_init(&mgr);   /* Initialise event manager */
	mg_http_listen(&mgr, s_http_addr, request_handler, NULL);    /* Create HTTP listener */
	mg_http_listen(&mgr, s_https_addr, request_handler, (void *) 1);  /* HTTPS listener  */
	/*todo: does this need graceful exit via signals and keyboard? */
	/* Infinite event loop: */

	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);

	return 0;
}
