#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ws.h>

#define serverHost "localhost"
#define serverPort 8080

// called when client connects to server
void onopen(ws_cli_conn_t client) {
    char *address, *port;
    address = ws_getaddress(client);
    port = ws_getport(client);

    printf("connection opened, addr: %s, port: %s\n", address, port);
}

// called when client disconnects from server
void onclose(ws_cli_conn_t client) {
    char *address, *port;
    address = ws_getaddress(client);
    port = ws_getport(client);

    printf("connection closed, addr: %s, port: %s\n", address, port);
}

// called when message is received
void onmessage(ws_cli_conn_t client, const unsigned char *msg, uint64_t size, int type) {
    char *address, *port;
    address = ws_getaddress(client);
    port = ws_getport(client);

    printf("message received: %s (size: %ld, type: %d), from: %s, port: %s\n", msg, size, type, address, port);

    // sends recieved message to all connected clients
    ws_sendframe_bcast(serverPort, (char *)msg, size, type);
}

int main(void) {
    ws_socket(&(struct ws_server){
        .host = serverHost,
        .port = serverPort,
        .thread_loop = 0,
        // .timeout_ms = 1000,
        .evs.onopen = &onopen,
        .evs.onclose = &onclose,
        .evs.onmessage = &onmessage
    });

    return 0;
}