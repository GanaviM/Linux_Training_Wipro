#!/bin/bash

# Define the directory path
directory="sample_dir"

# Count the number of files
num_files=$(find "$directory" -type f | wc -l)

# Find the largest file
largest_file=$(find "$directory" -type f -exec ls -lS {} + | head -n 1)

# Output the results
echo "Number of files in directory '$directory': $num_files"
echo "Largest file in directory structure:"
echo "$largest_file"
