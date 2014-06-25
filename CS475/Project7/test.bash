#!/bin/bash

for i in {1..13}
do
  g++  -DNUM=$((1000 * (2 ** $i)))  -o arraymult  arraymult.cpp simd.o  -lm  -fopenmp
  sleep 1
  ./arraymult
done