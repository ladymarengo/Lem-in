#!/bin/bash
for filename in ./maps/caruy_maps/*; do
    echo "$filename"
    ./lem-in -file "$filename" > 1
    grep "^#Here" 1 | head -n 1
    grep "^L" 1 | wc -l
    echo ""
done
for filename in ./maps/beautymapper/*; do
    echo "$filename"
    ./lem-in -file "$filename" > 1
    grep "^#Here" 1 | head -n 1
    grep "^L" 1 | wc -l
    echo ""
done