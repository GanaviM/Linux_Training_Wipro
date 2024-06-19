#!/usr/bin/env bash

num=101
if [ $num -gt 1000 ]
then
	echo "That's a huge number!"
elif [ $num -gt 100 ]
then
	echo "That's a big number!"
else
	echo "That's a small number."
fi

