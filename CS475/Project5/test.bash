#!/bin/bash

#for i in {1..13}
#do
#  for j in {1..10}
#  do
#    g++ -fopenmp -O3 -g -w -march=native -I. first.cpp -o first -lrt -lpthread -lm -lOpenCL -D"LOCAL=$((2 ** $j))" -D"GLOBAL=$((2 ** $i))"
#    optirun ./first
#  done
#done


for i in 1024 2048 3072 4096 5120 6144 7168 8192
do
  g++ -fopenmp -O3 -g -w -march=native -I. first.cpp -o first -lrt -lpthread -lm -lOpenCL -D"GLOBAL=$i"
  optirun ./first
done