#!/bin/sh
# please do chmod +x run.sh
if [ -d "results" ]; then
    rm -r results
fi
mkdir results
for op in rw seqread ranread
do
    for block in 1B 1KB 1MB 10MB
    do
        for threads in 1 2 4 8 
        do
            echo "Operation: "$op", block size: "$block", thread:"$threads
            python disk.py $op $block  $threads >> Op_"$op"_block_"$block"_thread_"$threads".txt
            echo "--> Write to file: Op_"$op"_block_"$block"_thread_"$threads".txt"
            mv  Op_"$op"_block_"$block"_thread_"$threads".txt results
        done 
    done
done
