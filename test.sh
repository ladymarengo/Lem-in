#!/bin/bash

Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
NC='\033[0m'              # No Color
Yellow='\033[0;33m'       # Yellow
for value in {1..10} 
do
    ./generator $1 > tmp
    ./lem-in -file tmp | grep "^L" > grep_tmp
	a=($(wc -l grep_tmp))
	required=($(grep "^#Here" tmp | head -n 1 | cut -d " " -f 8))
	lines=${a[0]}
	echo "lines: $lines, required: $required"
	if ((($lines - $required) < 1 ))
	then
		echo -e "${Green}OK${NC}"
	elif ((($lines - $required) < 3 ))
	then
		echo -e "${Yellow}OK${NC}"
	else
		echo -e "${Red}KO${NC}"
	fi
done
