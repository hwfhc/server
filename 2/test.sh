#! /bin/bash

if [ ! -d "./bin" ]; then
    mkdir -p ./bin
fi

gcc ./server.c -o ./bin/server
gcc ./client.c -o ./bin/client

./bin/server
./bin/client
