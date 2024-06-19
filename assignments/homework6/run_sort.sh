#!/bin/bash

# Sort 프로그램 실행 파일
SORT_PROG="./sort"
# 정렬 알고리즘 옵션 배열
ALGORITHMS=("insert" "heap" "quick" "merge")
# 각 알고리즘을 100번 실행
NUM_RUNS=100
DATAS=(25000 50000 100000 200000)
# 결과를 저장할 파일
RESULT_FILE="results.txt"
OUTPUT_FOLDER="output"

# 결과 폴더 생성
mkdir -p "$OUTPUT_FOLDER"

# 결과 파일 초기화
echo "" > $RESULT_FILE

# 각 알고리즘에 대해 반복
for DATA in "${DATAS[@]}"; do
    echo "Running $DATA..." >> $RESULT_FILE

    for ALGO in "${ALGORITHMS[@]}"; do
        echo "Running $ALGO sort 100 times..." >> $RESULT_FILE
        TOTAL_TIME=0
        
        # 알고리즘 100번 실행
        for ((i = 1; i <= $NUM_RUNS; i++)); do
            OUTPUT_FILE="$OUTPUT_FOLDER/output-$DATA-$ALGO-$i.txt"
            TIME=$($SORT_PROG -n $DATA -i data-$DATA -o $OUTPUT_FILE -s $ALGO)
            echo "Run $i: $TIME seconds"
            TOTAL_TIME=$(echo "$TOTAL_TIME + $TIME" | bc)
        done

        # 평균 시간 계산
        AVERAGE_TIME=$(echo "scale=6; $TOTAL_TIME / $NUM_RUNS" | bc)
        echo "Average time for $ALGO sort: $AVERAGE_TIME seconds" >> $RESULT_FILE
        echo "" >> $RESULT_FILE
    done

done

exit