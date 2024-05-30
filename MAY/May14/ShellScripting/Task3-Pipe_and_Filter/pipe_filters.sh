#!/bin/bash

# Prompt the user to enter the word to search for
echo "Enter the word to search for:"
read search_word

# Prompt the user to enter the file name
echo "Enter the file name:"
read file_name

# Use grep to find and list all occurrences of the specific word in the file,
# then pipe the output to sort to display the results alphabetically
grep -o "\b$search_word\b" "$file_name" | sort
