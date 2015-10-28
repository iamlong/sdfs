#!/bin/bash

g++ -g -std=gnu++11 testStorage.cpp -o testStorage.o -I../include/cygwin -L../ -L../external/cygwin -lsdfs -lgtest

./testStorage.o
