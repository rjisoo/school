#!/bin/bash

for i in {1..13}
do
  for j in {1..10}
  do
    g++ -fopenmp -O3 -g -w -march=native -I. first.cpp -o first -lrt -lpthread -lm -lOpenCL -D"LOCAL=$((2 ** $j))" -D"GLOBAL=$((2 ** $i))"
    optirun ./first
  done
done