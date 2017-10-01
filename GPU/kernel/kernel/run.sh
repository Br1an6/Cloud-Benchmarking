#!/bin/sh
echo "Compiling.."
nvcc -default-stream per-thread kernel.cu -o kernel

if [ -d "results" ]; then
    rm -r results
fi
mkdir results

echo "Start Benchmark testing for GPU"
for op in 1 2 3 4
do
   echo Operation: "$op"
   ./kernel "$op" >> Op_"$op".txt
   echo "--> Write to file: Op_"$op".txt"
   mv Op_"$op".txt results
done
