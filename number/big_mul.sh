#!/bin/bash

function usage()
{
	echo "Helper to do really big multiplications"
	echo "Run as:"
	echo "./big_mul.sh <number of digits> <digit> | xargs ./column_mul"
}

if [ $# -ne 2 ]
then
	usage
	exit 1
fi

n=$1
d=$2

for i in $(seq 1 $n)
do 
	echo -n $d; 
done

echo ' '

for i in $(seq 1 $n)
do 
	echo -n $d; 
done
