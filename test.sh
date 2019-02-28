#!/bin/bash
set -e

echo "Compiling..."
mkdir -p bin output
g++ sol-naive.cpp --std=c++14 -o bin/solution

if [[ $1 == "all" ]]; then
	files="busy_day mother_of_all_warehouses redundancy";
elif [[ $1 == "fast" ]]; then
	files="busy_day mother_of_all_warehouses redundancy";
else
	files="example";
fi

for name in $files; do
	# printf "Running for file $name...";
	./bin/solution < "input/${name}.in" ;
done
