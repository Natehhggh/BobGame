#!/bin/bash

build=debug

if [ $build == "debug" ]; then
    gcc -O1 ./src/main.c  -lraylib -lm -o ./debug/game;
else
    gcc -O3 ./src/main.c  -lraylib -lm -o ./release/game;
fi
