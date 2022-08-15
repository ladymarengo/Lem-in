#!/bin/bash
VAR=${1:-50}
./generator --big-superposition > map_from_generator
./beautymapper_mac map_from_generator $VAR
./lem-in -paths -file map_from_generator-beautified-$VAR > beautified
./visualizer_mac beautified 
