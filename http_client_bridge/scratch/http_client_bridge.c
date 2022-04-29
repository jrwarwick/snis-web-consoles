#include "mongoose.h"

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  struct mg_http_serve_opts opts = {.root_dir = "."};   // Serve local dir
  if (ev == MG_EV_HTTP_MSG) mg_http_serve_dir(c, ev_data, &opts);

  /* http://hostname/SHIPNAME/STATIONNAME/COMMAND/PARAM=VAL
   * http://foo.bar/ASTRISK/HELM/RUDDER/-1
   * http://foo.bar/ASTRISK/SCIENCE/LRS/PULSE
   */
}

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);                                        // Init manager
  mg_http_listen(&mgr, "http://localhost:8000", fn, &mgr);  // Setup listener
  for (;;) mg_mgr_poll(&mgr, 1000);                         // Event loop
  mg_mgr_free(&mgr);                                        // Cleanup
  return 0;
}
