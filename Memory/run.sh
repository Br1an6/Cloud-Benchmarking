#!/bin/sh
# please do chmod +x run.sh
echo "Compiling memory.cpp.."
g++ memory.cpp -o memory -pthread

if [ -d "results" ]; then
    rm -r results
fi
mkdir results

echo "Start Benchmark testing"
for op in 1 2 3
do
    for block in 1 1000 1000000 10000000
    do
        for threads in 1 2 4 8 
        do
            echo "Operation: "$op", block size: "$block", thread:"$threads
            ./memory $op $block  $threads >> Op_"$op"_block_"$block"_thread_"$threads".txt
            echo "--> Write to file: Op_"$op"_block_"$block"_thread_"$threads".txt"
            mv  Op_"$op"_block_"$block"_thread_"$threads".txt results
        done 
    done
done
