#!/bin/bash
set -e

echo "Compiling..."
mkdir -p bin output
g++ score.cpp --std=c++14 -O2 -o bin/score
g++ sol-naive.cpp --std=c++14 -O3 -o bin/solution

if [[ $1 == "all" ]]; then
	files="a_example  b_lovely_landscapes  c_memorable_moments  d_pet_pictures  e_shiny_selfies";
elif [[ $1 == "fast" ]]; then
	files="a_example  c_memorable_moments  d_pet_pictures";
else
	files="a_example";
fi

total=0

for name in $files; do
	printf "Running for file $name...";
	time ./bin/solution < "input/${name}.txt" > "output/${name}.out" ;
	score=`./bin/score "output/$name.out" < "input/$name.txt"`
	echo "Your score for $name is: $score"
	total=$(python3 -c "print($total+$score)")
done

echo "Total score: $total"
