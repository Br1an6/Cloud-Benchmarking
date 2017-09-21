#include <stdio.h>
#include <time.h>
#include <math.h>
__global__ void
floatAdd(const float *A, const float *B, float *C, int numElements)
{
    //Get the index 
    int i = blockDim.x * blockIdx.x + threadIdx.x;

    if (i < numElements)
    {
        C[i] = A[i] + B[i];
    }
}


int main(void)
{


    //Define number of elements
    int numElements = 50000;

	//FLOPS
    size_t size = numElements * sizeof(float);
    printf("FLoatoperations on %d elements\n", numElements);

    // Allocate the host input vector A
    float *h_A = (float *)malloc(size);
    float *h_B = (float *)malloc(size);
    float *h_C = (float *)malloc(size);

 
    // Initialize the host input with random generators
    for (int i = 0; i < numElements; ++i)
    {
        h_A[i] = rand()/(float)RAND_MAX;
        h_B[i] = rand()/(float)RAND_MAX;
    }

    // Allocate the device input vector A
    float *d_A = NULL;
    float *d_B = NULL;
    float *d_C = NULL;

    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);
	    
    // Copy the host input data in host memory to the device input variables in device memory
    printf("Copy input data from the host memory to device memory\n");
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Launch the  FloatAdd CUDA Kernel
    int threadsPerBlock = 3584;  //probably more than that
    int blocksPerGrid =(numElements + threadsPerBlock - 1) / threadsPerBlock;
    printf("CUDA kernel launch with %d blocks of %d threads\n", blocksPerGrid, threadsPerBlock);

	//Time to calculate
	//Timing
	clock_t start, stop;

    start = clock();
	printf("%6.3f\n", (double)start);

    floatAdd<<<1, 1>>>(d_A, d_B, d_C, numElements);
     

    // Copy the device result vector in device memory to the host result vector in host memory.
    printf("Copy output data from the CUDA device to the host memory\n");
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    
	//End time
	//check end time
	 stop = clock();
				  
	//10^9 for G for flops,iops,hops,qops
	double elapsed = double(stop-start);

	printf("Time taken : %6.3f\n", double(stop-start));
	printf  ("Time taken in GFLOPS: %9.9f\n", elapsed/pow(10,9));

	// Clearing device global memory
     cudaFree(d_A);
	 cudaFree(d_B);
	 cudaFree(d_C);

    // Clearing host memory
    free(h_A);
    free(h_B);
    free(h_C);

    printf("Process completed\n");
    return 0;
}

