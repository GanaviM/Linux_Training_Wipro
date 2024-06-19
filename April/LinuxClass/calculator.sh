#!/bin/bash

read -p "Enter the first number: " num1
read -p "Enter the operator(+, -, *, /): " operator
read -p "Enter the second number: " num2
case $operator in
	+)
		result=$(echo "$num1 + $num2" | bc)
		;;
	-)
		result=$(echo "$num1 - $num2" | bc)
		;;
	*)
		result=$(echo "$num1 * $num2" | bc)
		;;
	/)
		result=$(echo "$num1 / $num2" | bc)
		;;
	*)
		echo "Invalid operation!"
		exit 1
		;;
esac
echo "Result: $result"
