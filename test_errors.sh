#!/bin/bash
for filename in ./maps/invalid/*; do
	echo "$filename"
    ./lem-in < "$filename"
done
for filename in ./maps/valid/*; do
	echo "$filename"
    ./lem-in < "$filename"
done