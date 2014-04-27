#!/bin/bash

for i in {1..1}
do
  echo "Treads: $i"
  for j in {1..15}
  do
    ./nbodies -n $((2**$j)) -t 1
  done
done
