#!/bin/sh
# please do chmod +x run_for_2nodes.sh
# make sure run run_servers.sh on another KVM first

if [ ! -d "results" ]; then
    mkdir results
fi

# 2 nodes AKA not for loopback

for threads in 1 2 4 8
do
    echo "Number of Thread: $threads"
    python UDPClient_2nodes.py $threads >> "thread_"$threads"_UDP_2nodes.txt"
    echo "--> Write to file: thread_"$threads"_UDP_2nodes.txt"
    mv "thread_"$threads"_UDP_2nodes.txt" results
done

# Wait for 1 seconds
sleep 1

for threads in 1 2 4 8
do
    echo "Number of Thread: $threads"
    sleep 2  # Wait for 1 seconds
    python TCPClient_2nodes.py $threads >> "thread_"$threads"_TCP_2nodes.txt"
    echo "--> Write to file: thread_"$threads"_TCP_2nodes.txt"
    mv "thread_"$threads"_TCP_2nodes.txt" results
done
