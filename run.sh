#!/bin/bash
./cpu-freq-stable.sh enable

make

sleep 1

cat /proc/cpuinfo | grep -m1 "MHz"

taskset -c 0 ./latency


cat /proc/cpuinfo | grep -m1 "MHz"

make clean

./cpu-freq-stable.sh disable
