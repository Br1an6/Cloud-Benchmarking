#include < stdio.h >
#include < time.h >
#include < math.h > 
#include < pthread.h >

  __global__ void doubleKernel(double * x, int n) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    for (int i = tid; i < n; i += blockDim.x * gridDim.x) {
      // x[i] = sqrt(pow(3.14159,i));
      x[i] = x[i] * 2.333 + x[i] * 3.444;
      printf("Value of x[i] is %0.2d\n", &x[i]);
    }
  }

__global__ void intKernel(int * x, int n) {
  int tid = threadIdx.x + blockIdx.x * blockDim.x;
  for (int i = tid; i < n; i += blockDim.x * gridDim.x) {
    x[i] = x[i] * 2 + x[i] * 3;
    printf("Value of x[i] is %d\n", & x[i]);
  }
}

__global__ void shortKernel(short int * x, int n) {
  int tid = threadIdx.x + blockIdx.x * blockDim.x;
  for (int i = tid; i < n; i += blockDim.x * gridDim.x) {
    x[i] = x[i] * 2 + x[i] * 3;
    printf("Value of x[i] is %d\n", x[i]);
  }
}

__global__ void charKernel(char * x, int n) {
  int tid = threadIdx.x + blockIdx.x * blockDim.x;
  for (int i = tid; i < n; i += blockDim.x * gridDim.x) {

    printf("Value of x[i] is %s\n", x[i]);
  }
}

int main(int argc, char * * argv) {
  //Define number of elements
	const int numElements = 50000;

  printf("Char is %zd: \n", sizeof(char));

  //Timing
  clock_t start, stop;
  double elapsed;

  //define number of streams 
  const int cores = 8;
  cudaStream_t streams[cores];

  int op = 0;

  if (argc < 1) {
    printf("Please enter operation type");
    return 0;
  }

  if (argc > 0) {
    op = atoi(argv[1]);
    printf("Optn is %d\n", op);
  }

  switch (op) {

  case 1:
    printf("You selected FLOPS\n");
	 int *flops[cores];

    start = clock();

    for (int i = 0; i < cores; i++) {
      cudaStreamCreate( & streams[i]);
      cudaMalloc( & flops[i], cores * sizeof(int));

      // launch one worker kernel per stream
      intKernel << < 1, 32, 0, streams[i] >>> (flops[i], numElements);
      printf("Creating kernel for flops  %d\n", i);

    }
    //End time
    //check end time
    stop = clock();
    //10^9 for G for flops,iops,hops,qops
    elapsed = double(stop - start);
    printf("Time taken : %6.3f\n", double(stop - start));
    printf("Time taken in GFLOPS: %9.9f\n", elapsed / pow(10, 9));
    break;

  case 2:
    printf("You selected IOPS\n");
    int * iops[cores];

    start = clock();

    for (int i = 0; i < cores; i++) {
      cudaStreamCreate( & streams[i]);
      cudaMalloc( & iops[i], cores * sizeof(int));

      // launch one worker kernel per stream
      intKernel << < 1, 32, 0, streams[i] >>> (iops[i], numElements);
      printf("Creating kernel for iops  %d\n", i);

    }
    //End time
    //check end time
    stop = clock();
    //10^9 for G for flops,iops,hops,qops
    elapsed = double(stop - start);
    printf("Time taken : %6.3f\n", double(stop - start));
    printf("Time taken in GIOPS: %9.9f\n", elapsed / pow(10, 9));
    break;
  case 3:
    printf("You selected HOPS\n");
    short int * hops[cores];

    start = clock();

    for (int i = 0; i < cores; i++) {
      cudaStreamCreate( & streams[i]);
      cudaMalloc( & hops[i], cores * sizeof(short int));

      // launch one worker kernel per stream
      shortKernel << < 1, 16, 0, streams[i] >>> (hops[i], numElements);
      printf("Creating kernel for iops  %d\n", i);

    }
    //End time
    //check end time
    stop = clock();
    //10^9 for G for flops,iops,hops,qops
    elapsed = double(stop - start);
    printf("Time taken : %6.3f\n", double(stop - start));
    printf("Time taken in GHOPS: %9.9f\n", elapsed / pow(10, 9));
    break;
  case 4:
    printf("You selected QOPS\n");
    char * qops[cores];

    for (int j = 0; j < cores; j++) {
      qops[j] = "a";
    }
    for (int k = 0; k < cores; k++) {
      printf("q is %s\n", qops[k]);
    }

    start = clock();

    for (int i = 0; i < cores; i++) {
      cudaStreamCreate( & streams[i]);
      cudaMalloc( & qops[i], cores * sizeof(char));

      // launch one worker kernel per stream
      charKernel << < 1, 8, 0, streams[i] >>> (qops[i], numElements);
      printf("Creating kernel for qops  %d\n", i);

    }
    //End time
    //check end time
    stop = clock();
    //10^9 for G for flops,iops,hops,qops
    elapsed = double(stop - start);
    printf("Time taken : %6.3f\n", double(stop - start));
    printf("Time taken in GQOPS: %9.9f\n", elapsed / pow(10, 9));
    break;

  default:
    printf("Please enter valid operation type 1 or 2 or 3 or 4 for flops/iops/hops/qops respectively.\n");
    break;
  }

  printf("Process completed\n");
  cudaDeviceReset();

  return 0;
}