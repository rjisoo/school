#!/bin/bash

for i in {1..10}
do
  echo "Treads: $i"
  ./nbodies $i
  sleep 1
done
