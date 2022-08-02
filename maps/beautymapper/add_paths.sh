#!/bin/bash
for filename in ./*-beautified; do
    ../../lem-in -paths -file "$filename" > ../../visualizer/$filename-paths
done