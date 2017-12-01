# Cloud-Benchmarking

How to start benchmarking CPU
First, change the current directory to /CPU under folder “Cloud-Benchmarking”:

`cd CPU/`

Run the shell script: run.sh:

`./run.sh`

If any permission issues show up, please do chmod for the permission:

`chmod +x run.sh`

After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 8 files)

For 8 threads 10-minute, Please run:

`./run_10min.sh`

After the script finished, all the results will be store under /results_10min. The file title will contain all the informations for different parameters. (Total: 2 files)


How to start benchmarking GPU
First, change the current directory to /GPU under folder “Cloud-Benchmarking”:

`cd GPU/kernel/kernel/`

Run the shell script: run.sh:

`./run.sh`

If any permission issues show up, please do chmod for the permission:

`chmod +x run.sh`

After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 4 files)

How to start benchmarking Memory
First, change the current directory to /Memory under folder “Cloud-Benchmarking”:

`cd Memory/`

Run the shell script: run.sh:

`./run.sh`

If any permission issues show up, please do chmod for the permission:

`chmod +x run.sh`

After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 48 files)

How to start benchmarking Disk
First, change the current directory to /Disk under folder “Cloud-Benchmarking”:

`cd Disk/`

Run the shell script: run.sh:

`./run.sh`

If any permission issues show up, please do chmod for the permission:

`chmod +x run.sh`

After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 48 files)

How to start benchmarking Network
First, change the current directory to /Network under folder “Cloud-Benchmarking”:

`cd Network/`

**For loopback(1 node):**

Run the shell script: run.sh for testing UDP and TCP connection with loopback(1 node):

`./run.sh`

**For 2 nodes:**

For this testing, you will need two machines. The following is represented as node:1 & node:2.
You will need to modify 2 files (UDPClient_2nodes.py, TCPClient_2nodes.py).
1. UDPClient_2nodes.py: line 18: target_host = "node:1 IP"
2. TCPClient_2nodes.py: line 14: target_host = "node:1 IP"
Change the ports in python files “target_port = “ if necessary.

First, run the shell script: run_servers.sh on node:1 for starting servers.

`./run_servers.sh`

Then run the shell script: run_for_2nodes.sh on node:2 for testing UDP and TCP connection with 2 nodes(2 node):

`./run_for_2nodes.sh`

If any permission issues show up, please do chmod for the permission:

`chmod +x run.sh`

**important:**

After using ctrl + c to stop the servers script, please make sure you kill all the processes

`ps -fA | grep python`

> kill PID1 PID2

↑ PID1 and PID2 are the python servers’ processes IDs

Also, please make sure IPs are correct and ports (9999. 9998) are open. Change the ports in python files `target_port = ` if necessary.

After the script finished, all the results will be store under /results. The file title will contain all the informations for different parameters. (Total: 16 files)

**Appendix:**

In Memory, Disk, and Network folders, there are several createfile.sh and TestFile{$size_of_file}. These scripts are for generating testing files with particular size. No need to run the scripts again, since all the files are already generated.

For quickly browsing results, change directory to results:

`cd results/`

And “cat” all the files:

`cat *`

If testing Network part UDP over macOS server, please make sure you do 

`sudo sysctl -w net.inet.udp.maxdgram=65535 `

due to by default macOS has limited the maximum UDP-package to be 9216 bytes


## Running Tools

> For setting up CentOS DNS

```
sudo vi /etc/resolv.conf
sudo service dnsmasq restart
```
[Tutorial](http://ask.xmodulo.com/configure-static-dns-centos-fedora.html)

## benchmark tools 

**IOZone benchmark**
```
cd iozone3_470/src
./iozone -a
```
[IOZone benchmark](http://www.thegeekstuff.com/2011/05/iozone-examples/#comments)

**STREAM**
```
cd spack/opt/spack/linux-centos7-x86_64/gcc-4.8.5/stream-5.10-uuffcl3mhvonezosbpo4ys5vzarhg4dj/bin
./stream_c.exe
```
[STREAM](http://www.cs.virginia.edu/stream/ref.html#what)

**IPERF**
```
iperf -c 192.168.0.101
```
[IPerf](http://www.slashroot.in/iperf-how-test-network-speedperformancebandwidth)


**LINPACK:**
```
cd spack/opt/spack/linux-centos7-x86_64/gcc-4.8.5/your_path/bin/
mpirun -n 8 ./xhpl
```

```
git clone https://github.com/llnl/spack.git
export PATH="spack/bin:$PATH"
spack find
spack install hpl cflags="-march=native -mtune=native -O3" ^intel-mkl ^mpich 
```

License
-------

This software is licensed under the MIT license
© 2017 Cloud Benchmarking  contributors [Br1an6](https://github.com/Br1an6) &  [Sh4rel](https://github.com/Sh4rel)
