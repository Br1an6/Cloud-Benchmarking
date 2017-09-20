# Cloud-Computing
CS553: Cloud Computing

## TODO:

Brian         | Sharel
------------- | -------------
CPU fix output| GPU
Network FO    | Memory
benchmark     |
creat graph   |creat graph
doc           |doc

> comparing result with benchmark-testing tool
>> test on KVM

###### Useful link

<https://github.com/vinits91/Cloud-Computing>

<https://github.com/hparik11/Cloud_Benchmarking>

<https://github.com/CS553CloudComputing/Assgn1Benchmarking/tree/master/Source/Code>

___

<https://openstack.tacc.chameleoncloud.org>

<https://drive.google.com/file/d/0B_hC3I6jDR_-ZUZtWlRkNzVVb3M/view?usp=sharing>

## benchmark tools 

**IOZone benchmark**
[IOZone benchmark](http://www.thegeekstuff.com/2011/05/iozone-examples/#comments)


**IPERF**
[Iperf](http://www.slashroot.in/iperf-how-test-network-speedperformancebandwidth)


**LIPPACK:**
first make sure you have a c compiler (gcc, icc, clang) and fortran (gfortran) installed:

git clone https://github.com/llnl/spack.git
export PATH="spack/bin:$PATH"
spack find
spack install hpl cflags="-march=native -mtune=native -O3" ^intel-mkl ^mpich 

spack is basically a package manager that takes care of a lot of dependencies. the ^-intel-mkl and ^mpich flags in the installation command are just instructions to install those implementations of the needed dependencies (they are the best ones, and the ones that will compile without any trouble).. The cflags are the best possible compilation optimizations that will give you the fastest binary. They compile the binary to work with all the instructions available on your particular CPU, while also providing the most number of code optimizations.

Then find the folder where the hpl binary is (the binary will be called "xhpl") and in that same directory there will be a file called HPL.dat. Edit that file and give it a large enough problem size by modyfing the N parameter.

To run, make sure you have mpi in your path:

mpirun -n (number of MPI ranks, equal to product of the P and Q parameters that you chose in HPL.dat) ./xhpl
