#!/bin/bash

# Check if a directory path is provided as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

# Assign the directory path provided as the first argument
directory=$1

# Check if the directory exists
if [ ! -d "$directory" ]; then
    echo "Error: Directory '$directory' does not exist."
    exit 1
fi

# Count the number of regular files
num_files=$(find "$directory" -type f | wc -l)

# Find the largest file
largest_file=$(find "$directory" -type f -exec ls -lS {} + | head -n 1)

# Output the results
echo "Number of files in directory '$directory': $num_files"
if [ -n "$largest_file" ]; then
    echo "Largest file in directory structure:"
    echo "$largest_file"
else
    echo "No files found in directory structure."
fi
