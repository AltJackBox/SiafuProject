#!/bin/sh

loop=$1;
days=$2;
for ((i = 0; i < $loop; i++)); do ./bin/Simulation -d $days; done
