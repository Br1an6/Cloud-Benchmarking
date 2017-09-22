#include <iostream>
#include <pthread.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

enum opt{
    rw = 1,
    seqread = 2,
    ranread = 3
};

class Memory {
	void MemorySequentialReadOperation(long, long);
	void MemoryRandomReadOperation(long, long);
	void MemoryReadWriteOperation(long,long);
	long RandomNumber(long);

	public:
	long ReadWriteCall(long,long);
	long SequentialReadAccess(long, long);
	long RandomReadAccess(long, long);
}memory;

struct arg {
	long block_size;
	int num_of_thread;
	long itr;
};

double LatencyInms(long result, long itr) {
	return double(((double)result / 1024) / (double)itr);
}

double ThroughputInMBps(long result, long block_size, long itr) {
	return ((double)(block_size*itr) / (1024 * 1024)) / (((double)result / (1024 * 1024)));
}

long Memory::RandomNumber(long upperLimit) {
	srand(time(NULL));
	long random = rand() % upperLimit;
	return random;
}

void Memory::MemoryReadWriteOperation(long block_size, long itr) {
	ifstream is("~/TestFile20MB", ifstream::binary);
	is.seekg(0);
	char **memRead = new char*[itr];
	char **memWrite = new char*[itr];
	long r;

	for (long i = 0; i<itr; i++) {
		r = RandomNumber(itr);
		memRead[r] = new char[block_size];
		memWrite[r] = new char[block_size];

		is.read(memRead[i], block_size);
		memcpy(memWrite[r], memRead[r], block_size);
	}

	is.close();
}

void Memory::MemoryRandomReadOperation(long block_size, long itr) {
	long r = RandomNumber(itr); //or define any number upto 20MB
	ifstream is("~/TestFile20MB", ifstream::binary);
	char **memRead = new char*[itr];
	cout << "\nReading file from memory from random seeek.." << endl;
	is.seekg(r, is.beg);

	for (long i = 0; i<itr; i++)
		is.read(memRead[i], block_size);

	is.close();
}

void Memory::MemorySequentialReadOperation(long block_size, long itr) {
	ifstream is ("~/TestFile20MB", ifstream::binary);
	char **memRead = new char*[itr];
	cout << "\nReading file from memory from the beginning.." << endl ;
	is.seekg(0, is.beg);

	for (long i = 0; i<itr; i++)
		is.read(memRead[i], block_size);

	is.close();
}

long Memory::RandomReadAccess(long block_size, long itr) {
	time_t start, end;
	time(&start);
	MemoryRandomReadOperation(block_size, itr);
	time(&end);
	//keeping it long not double for calc purpose
	long dif = difftime(end, start);
	return dif;
}

long Memory::SequentialReadAccess(long block_size, long itr) {
	time_t start, end;
	time(&start);
	MemorySequentialReadOperation(block_size, itr);

	time(&end);
	//keeping it long not double for calc purpose
	long dif = difftime(end, start);
	return dif;
}

long Memory::ReadWriteCall(long block_size, long itr) {
	time_t start, end;
	time(&start);
	MemoryReadWriteOperation(block_size, itr);
	time(&end);
	//keeping it long not double for calc purpose
	long dif = difftime(end, start);
	return dif;
}

void * ReadWriteThread(void * args) {
	struct arg *arguments;
	arguments = (struct arg *)args;
	long result = memory.ReadWriteCall(arguments->block_size, arguments->itr);
	cout << LatencyInms(result, arguments->itr) << "\tms \t\t" << ThroughputInMBps(result, arguments->block_size, arguments->itr) << "\tMBps" << endl;

	pthread_exit(NULL);
}

void * SequentialReadThrerad(void * args) {
	struct arg *arguments;
	arguments = (struct arg *)args;
	long result = memory.SequentialReadAccess(arguments->block_size, arguments->itr);
	cout << LatencyInms(result, arguments->itr) << "\tms \t\t" << ThroughputInMBps(result, arguments->block_size, arguments->itr) << "\tMBps" << endl;

	pthread_exit(NULL);
}

void * RandomReadThread(void * args) {
	struct arg *arguments;
	arguments = (struct arg *)args;
	long result = memory.RandomReadAccess(arguments->block_size, arguments->itr);
	cout << LatencyInms(result, arguments->itr) << "\tms \t\t" << ThroughputInMBps(result, arguments->block_size, arguments->itr) << "\tMBps" << endl;

	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	long block_size;
	struct arg arguments;
	pthread_t threads[8];

	//rw, seqread, ranread
	string oType = argv[1];
	int opT = atoi(oType.c_str());

	// (1, 2 ,4 ,8)
	string threadCnt = argv[2];
	int num_of_thread = atoi(threadCnt.c_str());

	//(1B, 1KB, 1MB, 10MB)
	string bsize = argv[3];
	block_size = atol(bsize.c_str());

	long itr = (20*1024*1024) / block_size;
	itr = itr/ num_of_thread;

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
			pthread_create(&threads[i], NULL, &RandomReadThread, (void *)&arguments);
		}
		break;
	case ranread:
		for (int i = 0; i<num_of_thread; i++) {
			arguments.block_size = block_size;
			arguments.num_of_thread = i;
			pthread_create(&threads[i], NULL,  &SequentialReadThrerad, (void *)&arguments);
		}
		break;

	default: cout << "Please enter 1 for Read+Write, 2 for Random read or 3 for Sequential read.\n";
	}

	pthread_exit(NULL);
}

