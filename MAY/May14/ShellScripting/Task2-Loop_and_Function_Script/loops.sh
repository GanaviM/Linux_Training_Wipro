#!/bin/bash

# Function to print the number of lines in a file
print_lines() {
    local file="$1"
    local num_lines=$(wc -l < "$file")
    echo "Number of lines in $file: $num_lines"
}

# List of file names
files=("sample1.txt" "sample2.txt")

# Loop to iterate over the list of file names
for file in "${files[@]}"; do
    # Call the function for each file
    print_lines "$file"
done
