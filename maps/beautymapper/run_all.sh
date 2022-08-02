#!/bin/bash
for filename in ./*; do
    ../../beautymapper/target/release/beautymapper "$filename"
done