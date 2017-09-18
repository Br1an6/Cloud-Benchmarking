#!/bin/sh
# please do chmod +x run_servers.sh

python UDPServer_2nodes.py $threads &  # Launch script in background
python TCPServer_2nodes.py $threads &  # Launch script in background

# after ctrl + c, please make sure you kill the process
# ps -fA | grep python
# kill PID1 PID2