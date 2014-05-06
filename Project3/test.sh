#!/bin/bash

for numt in {1..4}
do
  for num in {0..20}
  do
    gcc -Wall -std=c99 -fopenmp -O3 -g -I. main.c -o false-share -lrt -lpthread -lm -D"NUM=$num" -D"NUMT=$numt"
    sleep 2
    ./false-share | tee -a fix1-time
  done
done



for numt in {1..4}
do
  for num in {0..20}
  do
    gcc -Wall -std=c99 -fopenmp -O3 -g -I. main.c -o false-share -lrt -lpthread -lm -D"NUM=$num" -D"NUMT=$numt" -DFIX2
    sleep 2
    ./false-share | tee -a fix2-time
  done
done
