//
//  main.cpp
//  memory
//
//  Created by Brian Liu on 9/23/17.
//  Copyright © 2017 Brian Liu. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

enum opt{
    rw = 1,
    seqread = 2,
    ranread = 3
};

struct arg {
    int block_size;
    int num_of_thread;
    int itr;
};

double LatencyInms(double result, int itr) {
    double ret = double(((double)result / 1000) / (double)itr);
    return ret;
}

double ThroughputInMBps(double result, int block_size, int itr) {
    double ret = ((double)(block_size*itr) / (1000 * 1000)) / (((double)result / (1000 * 1000)));
    return ret;
}

int RandomNumber(int upperLimit) {
    int random = rand() % upperLimit;
    return random;
}

void MemoryReadWriteOperation(int block_size, int itr) {
    ifstream is("~/TestFile20MB", ifstream::binary);
    is.seekg(0);
    char **memRead = new char*[itr];
    char **memWrite = new char*[itr];
    cout << "\nmemory copying.." << endl;
    for (int i = 0; i<itr; i++) {
        memRead[i]=new char[block_size];
        memWrite[i]=new char[block_size];
        memcpy(memWrite[i], memRead[i], block_size);
    }
    
    is.close();
}

void MemoryRandomReadOperation(int block_size, int itr) {
    int r = RandomNumber(itr); //or define any number upto 20MB
    ifstream is("~/TestFile20MB", ifstream::binary);
    char **memRead = new char*[itr];
    cout << "\nRandomly Reading.." << endl;
    is.seekg(r, is.beg);
    
    for (int i = 0; i<itr; i++)
        is.read(memRead[i], block_size);
    
    is.close();
}

void MemorySequentialReadOperation(int block_size, int itr) {
    ifstream is ("~/TestFile20MB", ifstream::binary);
    char **memRead = new char*[itr];
    cout << "\nSequentially Reading.." << endl ;
    is.seekg(0, is.beg);
    
    for (int i = 0; i<itr; i++)
        is.read(memRead[i], block_size);
    
    is.close();
}

void getResult(int block_size, int itr, int opt) {
    switch (opt) {
        case rw:
            MemoryReadWriteOperation(block_size, itr);
            break;
        case seqread:
            MemorySequentialReadOperation(block_size, itr);
            break;
        case ranread:
            MemoryRandomReadOperation(block_size, itr);
            break;
            
        default: cout << "Error in getting result.\n";
    }
}

void * ReadWriteThread(void * args) {
    struct arg *arguments;
    arguments = (struct arg *)args;
    getResult(arguments->block_size, arguments->itr, rw);
    pthread_exit(NULL);
}

void * SequentialReadThrerad(void * args) {
    struct arg *arguments;
    arguments = (struct arg *)args;
    getResult(arguments->block_size, arguments->itr, seqread);
    pthread_exit(NULL);
}

void * RandomReadThread(void * args) {
    struct arg *arguments;
    arguments = (struct arg *)args;
    getResult(arguments->block_size, arguments->itr, ranread);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int block_size;
    struct arg arguments;
    pthread_t threads[8];
    
    //rw, seqread, ranread
    string oType = argv[1];
    int opT = atoi(oType.c_str());
    
    //(1B, 1KB, 1MB, 10MB)
    string bsize = argv[2];
    block_size = atoi(bsize.c_str());
    
    // (1, 2 ,4 ,8)
    string threadCnt = argv[3];
    int num_of_thread = atoi(threadCnt.c_str());
    int itr =  ceil((20*1000*1000) / block_size); // 20MB
    
    //add to the argument
    arguments.block_size = block_size;
    arguments.itr = itr;
    clock_t startclock, finishclock;
    startclock = clock();
    switch (opT) {
        case rw:
            for (int i = 0; i < num_of_thread; i++) {
                arguments.block_size = block_size;
                arguments.num_of_thread = i;
                pthread_create(&threads[i], NULL, &ReadWriteThread, (void *)&arguments);
            }
            break;
        case seqread:
            for (int i = 0; i < num_of_thread; i++) {
                arguments.block_size = block_size;
                arguments.num_of_thread = i;
                pthread_create(&threads[i], NULL,  &SequentialReadThrerad, (void *)&arguments);
            }
            break;
        case ranread:
            srand(time(NULL));
            for (int i = 0; i < num_of_thread; i++) {
                arguments.block_size = block_size;
                arguments.num_of_thread = i;
                pthread_create(&threads[i], NULL, &RandomReadThread, (void *)&arguments);
            }
            break;
            
        default: cout << "Please enter 1 for Read+Write, 2 for Random read or 3 for Sequential read.\n";
    }
    
    /* block until all threads complete */
    for ( int i = 0; i < num_of_thread; ++i)
        pthread_join(threads[i], NULL);

    finishclock = clock();
    double durationtime = (double)(finishclock - startclock) / CLOCKS_PER_SEC;
    cout << LatencyInms(durationtime, itr) << "\tms \t" << ThroughputInMBps(durationtime, block_size, itr) << "\tMBps" << endl;
    
    pthread_exit(NULL);
}