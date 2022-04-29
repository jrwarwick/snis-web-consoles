PROG ?= snis_http_bridge

ifneq ($(MBEDTLS_DIR),)
CFLAGS += -DMG_ENABLE_MBEDTLS=1 -I$(MBEDTLS_DIR)/include -I/usr/include
CFLAGS += -L$(MBEDTLS_DIR)/lib -lmbedtls -lmbedcrypto -lmbedx509
else ifneq ($(OPENSSL_DIR),)
CFLAGS += -DMG_ENABLE_OPENSSL=1 -I$(OPENSSL_DIR)/include
CFLAGS += -L$(OPENSSL_DIR)/lib -lssl -lcrypto
endif

all: $(PROG)
	cd .. ; $(DEBUGGER) ./$(PROG) $(ARGS)

$(PROG): http_client_bridge.c
	$(CC) ./mongoose.c -I../.. -W -Wall -DMG_ENABLE_LINES=1 -DMG_ENABLE_DIRECTORY_LISTING=1 $(CFLAGS) -o $(PROG) http_client_bridge.c
	cp $(PROG) ../

clean:
	rm -rf ../$(PROG) $(PROG) *.o *.dSYM *.gcov *.gcno *.gcda *.obj *.exe *.ilk *.pdb
