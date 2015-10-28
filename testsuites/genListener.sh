#!/bin/bash

g++ -g -std=gnu++11 testlistener.cpp -o testlistener.o -I../include/cygwin -L../ -L../external/cygwin -lsdfs -lgtest

./testlistener.o
