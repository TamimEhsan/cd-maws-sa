#!/bin/bash

# Directory containing input files
DATA_DIR="../benchmark/data/assembled-fish_mito"

# Input directory
INPUT_DIR="${DATA_DIR}/input"
# Output directory
OUTPUT_DIR="${DATA_DIR}/output-maw"

# Create the output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"
OUTPUT_FILE="${OUTPUT_DIR}/maw_cd_maws_sa.txt"

# Remove the output file if it already exists
rm -f "$OUTPUT_FILE"

# Iterate over all files in the data directory
for FILE in "$INPUT_DIR"/*; do
    # Extract the file name without its directory and extension
    TEMP_OUTPUT=$(mktemp)
    # Run the command with the input file and specified output file
    "../cd-maws-sa/maw-gen"  "$FILE" "$TEMP_OUTPUT" 4 14
    
    cat "$TEMP_OUTPUT" >> "$OUTPUT_FILE"
    rm "$TEMP_OUTPUT"

    echo "Processed $FILE -> $OUTPUT_FILE"

done

echo "Processing complete."
