#!/bin/sh
# please do chmod +x run.sh
if [ -d "results" ]; then
    rm -r results
fi
mkdir results

for data_type in iops flops
do
    for threads in 1 2 4 8 
    do
        echo "Number of Thread: "$threads", data type: "$data_type
        python cpu.py $threads $data_type >> thread_"$threads"_type_"$data_type".txt
        echo "--> Write to file: thread_"$threads"_type_"$data_type".txt"
		mv thread_"$threads"_type_"$data_type".txt results
    done 
done
