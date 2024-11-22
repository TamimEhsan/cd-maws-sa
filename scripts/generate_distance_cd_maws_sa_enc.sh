DATA_DIR="../benchmark/data/assembled-fish_mito"

INPUT_FILE="${DATA_DIR}/output-maw/maw_cd_maws_sa_enc.txt"


OUTPUT_FILE="${DATA_DIR}/output-maw/maw-distance-cd-maws_sa_enc.txt"

# Remove the output file if it already exists
rm -f "$OUTPUT_FILE"

touch "$OUTPUT_FILE"

time "../cd-maws-sa-enc/dist-calc-enc" $INPUT_FILE $OUTPUT_FILE
