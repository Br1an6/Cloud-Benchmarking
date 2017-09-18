#!/bin/sh
# please do chmod +x run.sh
if [ ! -d "results" ]; then
    mkdir results
fi

# loopback

for threads in 1 2 4 8
do
    echo "Number of Thread: $threads"
    python UDPServer.py $threads &  # Launch script in background
    PID=$!
    python UDPClient.py $threads >> "thread_"$threads"_UDP.txt"
    echo "--> Write to file: thread_"$threads"_UDP.txt"
    mv "thread_"$threads"_UDP.txt" results
    kill $PID
done

# Wait for 1 seconds
sleep 1

for threads in 1 2 4 8
do
    echo "Number of Thread: $threads"
    python TCPServer.py $threads &  # Launch script in background
    PID=$!
    sleep 1  # Wait for 1 seconds
    python TCPClient.py $threads >> "thread_"$threads"_TCP.txt"
    echo "--> Write to file: thread_"$threads"_TCP.txt"
    mv "thread_"$threads"_TCP.txt" results
    kill $PID
done