DATA_DIR="../benchmark/data/assembled-fish_mito"

INPUT_FILE="${DATA_DIR}/output-maw/maw_barton.txt"


OUTPUT_FILE="${DATA_DIR}/output-maw/maw-distance-cd-maws.txt"

# Remove the output file if it already exists
rm -f "$OUTPUT_FILE"

touch "$OUTPUT_FILE"

time ../cd-maws/main -i $INPUT_FILE -o $OUTPUT_FILE