#!/bin/sh
# please do chmod +x run.sh
if [ ! -d "results" ]; then
    mkdir results
fi

for threads in 1 2 4 8
do
    echo "Number of Thread: $threads"
    python UDPServer.py $threads &
    python UDPClient.py $threads >> "thread_"$threads"_UDP.txt"
    echo "--> Write to file: thread_"$threads"_UDP.txt"
    mv "thread_"$threads"_UDP.txt" results
done
