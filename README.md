# Cloud-Benchmarking

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
