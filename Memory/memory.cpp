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
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

enum opt{
    rw = 1,
    seqread = 2,
    ranread = 3
};

class Memory {
    void MemorySequentialReadOperation(int, int);
    void MemoryRandomReadOperation(int, int);
    void MemoryReadWriteOperation(int,int);
    int RandomNumber(int);
    
public:
    int ReadWriteCall(int,int);
    int SequentialReadAccess(int, int);
    int RandomReadAccess(int, int);
}memory;

struct arg {
    int block_size;
    int num_of_thread;
    int itr;
};

double LatencyInms(int result, int itr) {
    return double(((double)result / 1000) / (double)itr);
}

double ThroughputInMBps(int result, int block_size, int itr) {
    return ((double)(block_size*itr) / (1000 * 1000)) / (((double)result / (1000 * 1000)));
}

int Memory::RandomNumber(int upperLimit) {
    int random = rand() % upperLimit;
    return random;
}

void Memory::MemoryReadWriteOperation(int block_size, int itr) {
    ifstream is("~/TestFile20MB", ifstream::binary);
    is.seekg(0);
    char **memRead = new char*[itr];
    char **memWrite = new char*[itr];
    
    for (int i = 0; i<itr; i++) {
        memRead[i]=new char[block_size];
        memWrite[i]=new char[block_size];
        memcpy(memWrite[i], memRead[i], block_size);
    }
    
    is.close();
}

void Memory::MemoryRandomReadOperation(int block_size, int itr) {
    int r = RandomNumber(itr); //or define any number upto 20MB
    ifstream is("~/TestFile20MB", ifstream::binary);
    char **memRead = new char*[itr];
    cout << "\nReading file from memory from random seeek.." << endl;
    is.seekg(r, is.beg);
    
    for (int i = 0; i<itr; i++)
        is.read(memRead[i], block_size);
    
    is.close();
}

void Memory::MemorySequentialReadOperation(int block_size, int itr) {
    ifstream is ("~/TestFile20MB", ifstream::binary);
    char **memRead = new char*[itr];
    cout << "\nReading file from memory from the beginning.." << endl ;
    is.seekg(0, is.beg);
    
    for (int i = 0; i<itr; i++)
        is.read(memRead[i], block_size);
    
    is.close();
}

int Memory::RandomReadAccess(int block_size, int itr) {
    time_t start, end;
    time(&start);
    MemoryRandomReadOperation(block_size, itr);
    time(&end);
    //keeping it int not double for calc purpose
    int dif = difftime(end, start);
    return dif;
}

int Memory::SequentialReadAccess(int block_size, int itr) {
    time_t start, end;
    time(&start);
    MemorySequentialReadOperation(block_size, itr);
    
    time(&end);
    //keeping it int not double for calc purpose
    int dif = difftime(end, start);
    return dif;
}

int Memory::ReadWriteCall(int block_size, int itr) {
    time_t start, end;
    time(&start);
    MemoryReadWriteOperation(block_size, itr);
    time(&end);
    //keeping it int not double for calc purpose
    int dif = difftime(end, start);
    return dif;
}

void * ReadWriteThread(void * args) {
    struct arg *arguments;
    arguments = (struct arg *)args;
    int result = memory.ReadWriteCall(arguments->block_size, arguments->itr);
    cout << LatencyInms(result, arguments->itr) << "\tms \t\t" << ThroughputInMBps(result, arguments->block_size, arguments->itr) << "\tMBps" << endl;
    
    pthread_exit(NULL);
}

void * SequentialReadThrerad(void * args) {
    struct arg *arguments;
    arguments = (struct arg *)args;
    int result = memory.SequentialReadAccess(arguments->block_size, arguments->itr);
    cout << LatencyInms(result, arguments->itr) << "\tms \t\t" << ThroughputInMBps(result, arguments->block_size, arguments->itr) << "\tMBps" << endl;
    
    pthread_exit(NULL);
}

void * RandomReadThread(void * args) {
    struct arg *arguments;
    arguments = (struct arg *)args;
    int result = memory.RandomReadAccess(arguments->block_size, arguments->itr);
    cout << LatencyInms(result, arguments->itr) << "\tms \t\t" << ThroughputInMBps(result, arguments->block_size, arguments->itr) << "\tMBps" << endl;
    
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
    
    switch (opT) {
        case rw:
            for (int i = 0; i<num_of_thread; i++) {
                arguments.block_size = block_size;
                arguments.num_of_thread = i;
                pthread_create(&threads[i], NULL, &ReadWriteThread, (void *)&arguments);
            }
            break;
        case seqread:
            for (int i = 0; i<num_of_thread; i++) {
                arguments.block_size = block_size;
                arguments.num_of_thread = i;
                pthread_create(&threads[i], NULL,  &SequentialReadThrerad, (void *)&arguments);
            }
            break;
        case ranread:
            srand (time(NULL));
            for (int i = 0; i<num_of_thread; i++) {
                arguments.block_size = block_size;
                arguments.num_of_thread = i;
                pthread_create(&threads[i], NULL, &RandomReadThread, (void *)&arguments);
            }
            break;
            
        default: cout << "Please enter 1 for Read+Write, 2 for Random read or 3 for Sequential read.\n";
    }
    
    pthread_exit(NULL);
}