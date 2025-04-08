#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ws.h>

int PWRStatus = 0;
int ACTStatus = 0;

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
    if (strcmp(msg, "PWR") == 0) {
        if (PWRStatus == 0) {
            system("echo 1 >/sys/class/leds/PWR/brightness");
            PWRStatus = 1;
        } else {
            system("echo 0 >/sys/class/leds/PWR/brightness");
            PWRStatus = 0;
        }

        message = "PWR processed";
        ws_sendframe(client, message, strlen(message), 1);
    } else if (strcmp(msg, "ACT") == 0) {
        if (ACTStatus == 0) {
            system("echo 1 >/sys/class/leds/ACT/brightness");
            ACTStatus = 1;
        } else {
            system("echo 0 >/sys/class/leds/ACT/brightness");
            ACTStatus = 0;
        }

        message = "ACT processed";
        ws_sendframe(client, message, strlen(message), 1);
    }
}

int main() {
    system("echo none >/sys/class/leds/PWR/trigger");
    system("echo none >/sys/class/leds/ACT/trigger");
    system("echo 0 >/sys/class/leds/PWR/brightness");
    system("echo 0 >/sys/class/leds/ACT/brightness");

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