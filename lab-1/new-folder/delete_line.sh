#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <file_name> <line_number>"
    exit 1
fi

file_name=$1
line_number=$2

# Check if the file exists
if [ ! -e "$file_name" ]; then
    echo "Error: File '$file_name' not found."
    exit 1
fi

# Check if the line number is valid
if ! [[ "$line_number" =~ ^[0-9]+$ ]]; then
    echo "Error: Line number must be a positive integer."
    exit 1
fi

# Delete the specified line from the file
sed -i "${line_number}d" "$file_name"

echo "Line $line_number deleted from $file_name."
