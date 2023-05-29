#!/bin/bash

rm -rf build
make
st-flash --reset write ./build/linefollower.bin 0x08000000
