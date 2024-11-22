DATA_DIR="../benchmark/data/assembled-fish_mito"

INPUT_FILE="${DATA_DIR}/output-maw/maw_cd_maws_sa.txt"


OUTPUT_FILE="${DATA_DIR}/output-maw/maw-distance-cd-maws_sa.txt"

# Remove the output file if it already exists
rm -f "$OUTPUT_FILE"
rm -f "$OUTPUT_FILE"

touch "$OUTPUT_FILE_CD_MAWS"

time "../cd-maws-sa/dist-cal" $INPUT_FILE $OUTPUT_FILE
