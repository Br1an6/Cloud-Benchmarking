#!/bin/sh
rm -r results
mkdir results

for data_type in iops flops
do
    for threads in 1 2 4 8 
    do
        python cpu.py $threads $data_type >> thread"_"$threads"_type_"$data_type.txt
		mv thread"_"$threads"_type_"$data_type.txt results
    done 
done
