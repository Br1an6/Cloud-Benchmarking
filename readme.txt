Manual
A20375099 Yuan-An Liu, 
A20382007 Sharel Clavy Pereira


How to start benchmarking CPU
	First, change the current directory to /CPU under folder “PA1_Liu_Pereira”:
		cd CPU/
	Run the shell script: run.sh:
		./run.sh
	If any permission issues show up, please do chmod for the permission:
		chmod +x run.sh
After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 8 files)

	For 8 threads 10-minute, Please run:
	./run_10min.sh
After the script finished, all the results will be store under /results_10min. The file title will contain all the informations for different parameters. (Total: 2 files)


How to start benchmarking GPU
       	First, change the current directory to /GPU under folder “PA1_Liu_Pereira”:
		cd GPU/kernel/kernel/
	Run the shell script: run.sh:
		./run.sh
	If any permission issues show up, please do chmod for the permission:
		chmod +x run.sh
After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 4 files)

How to start benchmarking Memory
	First, change the current directory to /Memory under folder “PA1_Liu_Pereira”:
		cd Memory/
	Run the shell script: run.sh:
		./run.sh
	If any permission issues show up, please do chmod for the permission:
		chmod +x run.sh
After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 48 files)

How to start benchmarking Disk
	First, change the current directory to /Disk under folder “PA1_Liu_Pereira”:
		cd Disk/
	Run the shell script: run.sh:
		./run.sh
	If any permission issues show up, please do chmod for the permission:
		chmod +x run.sh
After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 48 files)

How to start benchmarking Network
	First, change the current directory to /Network under folder “PA1_Liu_Pereira”:
		cd Network/
For loopback(1 node):
	Run the shell script: run.sh for testing UDP and TCP connection with loopback(1 node):
		./run.sh
	For 2 nodes:
	For this testing, you will need two machines. The following is represented as node:1 & node:2.
	You will need to modify 2 files (UDPClient_2nodes.py, TCPClient_2nodes.py).
UDPClient_2nodes.py: line 18: target_host = "node:1 IP"
TCPClient_2nodes.py: line 14: target_host = "node:1 IP"
 Change the ports in python files “target_port = “ if necessary.

	First, run the shell script: run_servers.sh on node:1 for starting servers.
./run_servers.sh
Then run the shell script: run_for_2nodes.sh on node:2 for testing UDP and TCP connection with 2 nodes(2 node):
		./run_for_2nodes.sh
	If any permission issues show up, please do chmod for the permission:
		chmod +x run.sh
	Important:
	After using ctrl + c to stop the servers script, please make sure you kill all the processes
ps -fA | grep python
kill PID1 PID2
↑ PID1 and PID2 are the python servers’ processes IDs


Also, please make sure IPs are correct and ports (9999. 9998) are open. Change the ports in python files “target_port = “ if necessary.

After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 16 files)

*Appendix:* 
In Memory, Disk, and Network folders, there are several createfile.sh and TestFile{$size_of_file}. These scripts are for generating testing files with particular size. No need to run the scripts again, since all the files are already generated.

For quickly browsing results, change directory to results:
		cd results/
	And “cat” all the files:
	cat *

If testing Network part UDP over macOS server, please make sure you do 
		sudo sysctl -w net.inet.udp.maxdgram=65535 
due to by default macOS has limited the maximum UDP-package to be 9216 bytes
