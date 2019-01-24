#!/bin/bash
set -e

echo "Compiling..."
mkdir -p bin output
g++ score.cpp --std=c++14 -O2 -o bin/score
g++ sol-naive.cpp --std=c++14 -O3 -o bin/solution

if [[ $1 == "all" ]]; then
	files="busy_day mother_of_all_warehouses redundancy";
elif [[ $1 == "fast" ]]; then
	files="busy_day mother_of_all_warehouses redundancy";
else
	files="example";
fi

total=0

for name in $files; do
	printf "Running for file $name...";
	time ./bin/solution < "input/${name}.in" > "output/${name}.out" ;
	score=`./bin/score "output/$name.out" < "input/$name.in"`
	echo "Your score for $name is: $score"
	total=$(python3 -c "print($total+$score)")
done

echo "Total score: $total"
