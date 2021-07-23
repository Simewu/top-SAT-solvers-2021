#!/bin/bash


file=$1
if [ -z "$file" ]
then
	file="simple.cnf"
fi


echo Running SAT solvers on file \"$file\"...


echo
echo Running kissat_gb...
read -t 3 -n 1
./kissat_gb/build/kissat $file

echo
echo Running kissat_MAB...
read -t 3 -n 1
./kissat-MAB-1.0.3-79d8d8f2/build/kissat $file


echo
echo Running lstech_maple...
read -t 3 -n 1
./lstech_maple/core/glucose $file
