// memory.cpp : Defines the entry point 
//VS needs stdafx header 
#include "stdafx.h"

#include <iostream>
#include <fstream> 
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXTHREADS 16

using namespace std;

struct arg
{
	long blockSize;
	int threadNo;	
	int loopCnt;
	long itrn;
};

class Memory
{
	void MemorySequentialReadOperation(long, long);
	void MemoryRandomReadOperation(long, long);
	void MemoryReadWriteOperation(long,long);
	long RandomNumber(long);

public:
	long ReadWriteCall(long,long);
	long SequentialReadAccess(long, long);
	long RandomReadAccess(long, long);
}memory;


long Memory::RandomNumber(long upperLimit)
{
	srand(time(NULL));
	long random = rand() % upperLimit;
	return random;
}

void Memory::MemoryReadWriteOperation(long blockSize, long itrn)
{
	ifstream is("TestFile20MB", ifstream::binary);
	ofstream os("TestFile20MBWrite", ofstream::binary);

	is.seekg(0);
	char **memRead = new char*[itrn];
	char **memWrite = new char*[itrn];
	long r;

	for (long i = 0; i<itrn; i++)
	{
		r = RandomNumber(itrn);
		memRead[r] = new char[blockSize];
		memWrite[r] = new char[blockSize];

		is.read(memRead[i], blockSize);
		memcpy(memWrite[r], memRead[r], blockSize);
	}

	is.close();
	os.close();
}

void Memory::MemoryRandomReadOperation(long blockSize, long itrn)
{
	long r = RandomNumber(itrn); //or define any number upto 20MB
	ifstream is("TestFile20MB", ifstream::binary);
	char **memRead = new char*[itrn];
	cout << "\nReading file from memory from random seeek..\n";
	is.seekg(r, is.beg);

	for (long i = 0; i<itrn; i++)
	{
		is.read(memRead[i], blockSize);

	}
	is.close();
}

void Memory::MemorySequentialReadOperation(long blockSize, long itrn)
{

	ifstream is ("TestFile20MB", ifstream::binary);
	char **memRead = new char*[itrn];
	cout << "\nReading file from memory from the beginning..\n" ;
	is.seekg(0, is.beg);

	for (long i = 0; i<itrn; i++)
	{
		is.read(memRead[i], blockSize);
		
	}
	is.close();
}

long Memory::RandomReadAccess(long blockSize, long itrn)
{
	time_t start, end;
	time(&start);
	MemoryRandomReadOperation(blockSize, itrn);
	time(&end);
	//keeping it long not double for calc purpose
	long dif = difftime(end, start);
	return dif;
}

long Memory::SequentialReadAccess(long blockSize, long itrn)
{
	time_t start, end;
	time(&start); 
	MemorySequentialReadOperation(blockSize, itrn);
	
	time(&end);
	//keeping it long not double for calc purpose
	long dif = difftime(end, start);
	return dif;
}

long Memory::ReadWriteCall(long blockSize, long itrn)
{
	time_t start, end;
	time(&start);
	MemoryReadWriteOperation(blockSize, itrn);
	time(&end);
	//keeping it long not double for calc purpose
	long dif = difftime(end, start);
	return dif;
}

double LatencyInms(long result, long itrn)
{
	return double(((double)result / 1024) / (double)itrn);
}

double ThroughputInMBps(long result, long blockSize, long itrn)
{
	return ((double)(blockSize*itrn) / (1024*1024)) / (((double)result / (1024 * 1024)));
}


void * ReadWriteThread(void * args)
{
	struct arg *arguments;
	arguments = (struct arg *)args;
	long result = memory.ReadWriteCall(arguments->blockSize, arguments->itrn);
	cout << LatencyInms(result, arguments->itrn) << "\tms \t\t" << ThroughputInMBps(result, arguments->blockSize, arguments->itrn) << "\tMBps\n";

	pthread_exit(NULL);
}

void * SequentialReadThrerad(void * args)
{
	struct arg *arguments;
	arguments = (struct arg *)args;
	long result = memory.SequentialReadAccess(arguments->blockSize, arguments->itrn);
	cout << LatencyInms(result, arguments->itrn) << "\tms \t\t" << ThroughputInMBps(result, arguments->blockSize, arguments->itrn) << "\tMBps\n";

	pthread_exit(NULL);
}

void * RandomReadThread(void * args)
{
	struct arg *arguments;
	arguments = (struct arg *)args;
	long result = memory.RandomReadAccess(arguments->blockSize, arguments->itrn);
	cout << LatencyInms(result, arguments->itrn) << "\tms \t\t" << ThroughputInMBps(result, arguments->blockSize, arguments->itrn) << "\tMBps\n";

	pthread_exit(NULL);
}

int main(int argi, char *argc[]) {

	long blockSize;
	struct arg arguments;
	pthread_t threads[MAXTHREADS];


	//rw, seqread, ranread
	string oType = argc[1];
	int opType = atoi(oType.c_str());

	// (1, 2 ,4 ,8)
	string threadCnt = argc[2];
	int tCnt = atoi(threadCnt.c_str());
	
	//(1B, 1KB, 1MB, 10MB)
	string bsize = argc[3];
	blockSize = atol(bsize.c_str());
	
	long itrn = (20*1024*1024) / blockSize;
	itrn = itrn/ tCnt;

	//add to the argument
	arguments.blockSize = blockSize;
	arguments.itrn = itrn;

	switch (opType)
	{
	case 1:
		for (int i = 0; i<tCnt; i++)
		{
			arguments.blockSize = blockSize;
			arguments.threadNo = i;
			pthread_create(&threads[i], NULL, &ReadWriteThread, (void *)&arguments);
		}
		break;
	case 2:
		for (int i = 0; i<tCnt; i++)
		{
			arguments.blockSize = blockSize;
			arguments.threadNo = i;
			pthread_create(&threads[i], NULL, &RandomReadThread, (void *)&arguments);
		}
		break;
	case 3:
		for (int i = 0; i<tCnt; i++)
		{
			arguments.blockSize = blockSize;
			arguments.threadNo = i;
			pthread_create(&threads[i], NULL,  &SequentialReadThrerad, (void *)&arguments);
		}
		break;
	
	default: cout << "Please enter 1 for Read+Write, 2 for Random read or 3 for Sequential read.\n";
	}


	pthread_exit(NULL);
}

