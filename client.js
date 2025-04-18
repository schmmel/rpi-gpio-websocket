const logElement = document.getElementById('log');
logElement.value = '';

let address = '192.168.67.223'
let port = 8080
let ws = new WebSocket(`ws://${address}:${port}`);

ws.onopen = function() {
    log(`connected to ${address}:${port}`);
}

ws.onmessage = function(e) {
    log(`received: ${e.data}`);
}

// const messageText = document.getElementById('messageText');
// const messageButton = document.getElementById('messageButton');

// messageButton.onclick = function() {
//     let message = messageText.value;

//     if (message.length > 0) {
//         ws.send(message);
//         log.value += `sent: ${message}\n`
//         message = '';
//     }
// }

const PWR = document.getElementById('PWR');
const ACT = document.getElementById('ACT');

const GPIO5 = document.getElementById('GPIO5');

PWR.onclick = function() {
    let message = 'PWR';
    ws.send(message);
    log(`sent: ${message}`);
}

ACT.onclick = function() {
    let message = 'ACT';
    ws.send(message);
    log(`sent: ${message}`);
}

GPIO5.onclick = function() {
    let message = 'GPIO5';
    ws.send(message);
    log(`sent: ${message}`);
}

function log(message) {
    logElement.value += message + '\n';
    logElement.scrollTop = logElement.scrollHeight;
}