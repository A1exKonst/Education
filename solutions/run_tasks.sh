#!/usr/bin/env bash

# 1. Check if the directory argument is provided
if [ -z "$1" ]; then
    echo "Error: Please specify the target directory as an argument (build or build_strict)."
    echo "Usage: $0 <directory_name>"
    exit 1
fi

TARGET_DIR="$1"

# 2. Check if the specified directory exists and is a valid directory
if [ ! -d "$TARGET_DIR" ]; then
    echo "Error: Directory '$TARGET_DIR' does not exist."
    exit 1
fi

# Flag to track whether any matching executable files were found
found_any=false

# 3. Iterate through all files matching the pattern task_* in the target directory
for file in "$TARGET_DIR"/task_*; do
    # Check if the file actually exists (in case the glob pattern matches nothing)
    # and verify that it is an executable file
    if [ -x "$file" ]; then
        found_any=true
        
        # Extract only the filename without the path for clean console output
        filename=$(basename "$file")
        
        # Print the required tracking message before execution
        echo "call $filename"
        
        # Execute the file
        "$file"
        
        # Add an empty line for better output readability between tasks
        echo ""
    fi
done

if [ "$found_any" = false ]; then
    echo "No executable files starting with 'task_' were found in directory '$TARGET_DIR'."
fi
