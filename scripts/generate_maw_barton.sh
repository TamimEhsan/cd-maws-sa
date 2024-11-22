#!/bin/bash

# Directory containing input files
DATA_DIR="../benchmark/data/assembled-fish_mito"

# Input directory
INPUT_DIR="${DATA_DIR}/input"
# Output directory
OUTPUT_DIR="${DATA_DIR}/output-maw"

# Create the output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"
OUTPUT_FILE="${OUTPUT_DIR}/maw_barton.txt"

# Remove the output file if it already exists
rm -f "$OUTPUT_FILE"

# Iterate over all files in the data directory
for FILE in "$INPUT_DIR"/*; do
    # Extract the file name without its directory and extension
    TEMP_OUTPUT=$(mktemp)
    # Run the command with the input file and specified output file
    ../cd-maws/maw -a DNA -i "$FILE" -o "$TEMP_OUTPUT" -k 4 -K 14 -r 0
    
    # Sort the output, keeping the first line (header) at the top
    # Sort the output, keeping the first line (header) and ignoring the last line
    {
        head -n 1 "$TEMP_OUTPUT" # Get the header
        tail -n +2 "$TEMP_OUTPUT" | head -n -1 | sort # Exclude the last line and sort the remaining
        tail -n 1 "$TEMP_OUTPUT" # Get the last line
    } >> "$OUTPUT_FILE"
    
    # Clean up the temporary file
    rm "$TEMP_OUTPUT"

    echo "Processed $FILE -> $OUTPUT_FILE"
done

echo "Processing complete."
