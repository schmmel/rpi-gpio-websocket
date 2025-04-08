const messageText = document.getElementById('messageText');
const messageButton = document.getElementById('messageButton');

const log = document.getElementById('log');
log.value = '';

let address = 'localhost'
let port = 8080
let ws = new WebSocket(`ws://${address}:${port}`);

ws.onopen = function() {
    log.value += `connected to ${address}:${port}\n`;
}

ws.onmessage = function(e) {
    log.value += `received: ${e.data}\n`
}

messageButton.onclick = function() {
    let message = messageText.value;

    if (message.length > 0) {
        ws.send(message);
        log.value += `sent: ${message}\n`
        message = '';
    }
}