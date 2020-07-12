#!/bin/bash

g++ gen.cpp -o gen
g++ cf_624_e.cpp
g++ brute.cpp -o brute

for i in `seq 0 50`
do
	./gen 10000 > data.txt

	./a.out < data.txt > a.ans
	./brute < data.txt > b.ans

	cat a.ans
	cat b.ans

	diff a.ans b.ans

	if [ $? -ne 0 ]
	then
		exit 1
	fi
done

