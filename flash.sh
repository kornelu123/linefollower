#!/bin/bash

st-flash --reset write ./build/linefollower.bin 0x08000000
