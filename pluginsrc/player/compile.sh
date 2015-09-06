#!/bin/sh
g++ -std=c++11 -I../../include/ -I../../src -L../../res/lib/ -Wl,-rpath=./res/lib -fpic --shared AudioDevice.cpp Player.cpp -o Player.so -lmaudio -ldl -lportaudio && \
mkdir -p ../../res/plugins && cp Player.so ../../res/plugins/Player.so
