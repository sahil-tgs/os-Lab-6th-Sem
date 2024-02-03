#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <source_path> <destination_path>"
    exit 1
fi

source_path=$1
destination_path=$2

# Check if the source file exists
if [ ! -e "$source_path" ]; then
    echo "Error: Source file '$source_path' not found."
    exit 1
fi

# Copy the source file to the destination
cp "$source_path" "$destination_path"

echo "File '$source_path' copied to '$destination_path'."
