#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ws.h>
#include <wiringPi.h>

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

    char *message;
    if (strcmp(msg, "GPIO5") == 0) {
        int value = digitalRead(5);

        if (value == 0) {
            digitalWrite(5, HIGH);
            value = 1;
        } else {
            digitalWrite(5, LOW);
            value = 0;
        }

        snprintf(message, 8, "%s %d", msg, value);
        ws_sendframe(client, message, strlen(message), 1);
    }
}

int main() {

    wiringPiSetupGpio();
    pinMode(5, OUTPUT);
    digitalWrite(5, LOW);

    ws_socket(&(struct ws_server){
        .host = "0.0.0.0",
        .port = 8080,
        .thread_loop = 0,
        // .timeout_ms = 1000,
        .evs.onopen = &onopen,
        .evs.onclose = &onclose,
        .evs.onmessage = &onmessage
    });

    return 0;
}