#!/bin/bash

# Loop through all files in the current directory
for file in *; do
    # Check if it's a regular file
    if [ -f "$file" ]; then
        # Convert the file name to uppercase
        new_name=$(echo "$file" | tr '[:lower:]' '[:upper:]')

        # Rename the file
        mv "$file" "$new_name"

        echo "Renamed: $file to $new_name"
    fi
done
