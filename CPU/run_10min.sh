#!/bin/sh
# please do chmod +x run_10min.sh
if [ -d "results_10min" ]; then
    rm -r results_10min
fi
mkdir results_10min

for data_type in iops flops
do
    echo "data type: "$data_type""
    python cpu_10min.py $data_type >> type_"$data_type".txt
    echo "--> Write to file: type_"$data_type".txt"
	mv type_"$data_type".txt results_10min
done
