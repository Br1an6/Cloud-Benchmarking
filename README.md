# Cloud-Computing
CS553: Cloud Computing

## TODO:

Brian         | Sharel
------------- | -------------
Linpack       | Linpack
IPref         |
Stream        |
creat graph   |creat graph
doc           |doc

> comparing result with benchmark-testing tool
>> test on KVM

###### Useful link

<https://github.com/hparik11/Cloud_Benchmarking>

___

<https://openstack.tacc.chameleoncloud.org>

<https://drive.google.com/file/d/0B_hC3I6jDR_-ZUZtWlRkNzVVb3M/view?usp=sharing>

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
[Iperf](http://www.slashroot.in/iperf-how-test-network-speedperformancebandwidth)


**LINPACK:**
```
cd spack/opt/spack/linux-centos7-x86_64/gcc-4.8.5/hpl-2.2-bhssr2qm5lwigf65o6dvvks2whbsegaw/bin/
mpirun -n 8 ./xhpl
```

first make sure you have a c compiler (gcc, icc, clang) and fortran (gfortran) installed:

git clone https://github.com/llnl/spack.git
export PATH="spack/bin:$PATH"
spack find
spack install hpl cflags="-march=native -mtune=native -O3" ^intel-mkl ^mpich 

spack is basically a package manager that takes care of a lot of dependencies. the ^-intel-mkl and ^mpich flags in the installation command are just instructions to install those implementations of the needed dependencies (they are the best ones, and the ones that will compile without any trouble).. The cflags are the best possible compilation optimizations that will give you the fastest binary. They compile the binary to work with all the instructions available on your particular CPU, while also providing the most number of code optimizations.

Then find the folder where the hpl binary is (the binary will be called "xhpl") and in that same directory there will be a file called HPL.dat. Edit that file and give it a large enough problem size by modyfing the N parameter.

To run, make sure you have mpi in your path:

mpirun -n (number of MPI ranks, equal to product of the P and Q parameters that you chose in HPL.dat) ./xhpl
