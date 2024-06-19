#!/bin/bash

for item in apple banana cherry; do
        echo "Fruit: $item"
done

echo

counter=1

max_iteration=5

while [ $counter -le $max_iteration ]; do
        echo "Iteration $counter"
        ((counter++))
done

echo "Completed"

