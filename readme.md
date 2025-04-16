[wsServer](https://github.com/Theldus/wsServer)
[WiringPi](https://github.com/WiringPi/WiringPi)

`gcc led-server.c -o build/led-server -I./wsServer/include  -L./wsServer -lws`
`gcc gpio-server.c -o build/gpio-server -I./wsServer/include  -L./wsServer -lws -I./WiringPi/WiringPi -L./WiringPi/WiringPi -lwiringPi`

[dosato_websockets](https://github.com/Robotnik08/dosato_websockets)

`export LD_LIBRARY_PATH=./dosato_websockets`