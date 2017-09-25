import sys
import multiprocessing
import time
import math
import random

testfile_size = 20 * 1024 * 1024  # File: TestFile20MB


def readAndWrite(block_size):
    """
    Do r+w operation
    Args:
        block_size
    """
    f = open('TestFile20MB', 'rb')
    dst = open('TestFile20MBWrite', 'wb')
    while True:
        copy_buffer = f.read(block_size)
        if not copy_buffer:
            break
        dst.write(copy_buffer)
    f.close()
    dst.close()


def sequentialRead(block_size):
    """
    Do Sequential Read operation
    Args:
        block_size
    """
    f = open('TestFile20MB', 'rb')
    itr = int(math.ceil(testfile_size / block_size))
    for i in range(itr):
        f.read(block_size)
    f.close()


def randomRead(block_size):
    """
    Do Random Read operation
    Args:
        block_size
    """
    f = open('TestFile20MB', 'rb')
    itr = int(math.ceil(testfile_size / block_size))
    for i in range(itr):
        ran_start_offset = random.randint(0, itr)
        # get random starting offset
        f.seek(ran_start_offset)
        f.read(block_size)
    f.close()


def createAndRunThread(op, block_size, num_of_thread):
    """
    Create and run the thread
    Args:
        op ... operations           (rw, seqread, ranread)
        block_size ... block sizes  (1B, 1KB, 1MB, 10MB)
        num_of_thread ... threads   (1, 2 ,4 ,8)
    Returns:
        No
    """
    list_of_t = []
    for i in range(num_of_thread):
        if op == 'rw':
            t = multiprocessing.Process(target=readAndWrite, args=(block_size,))
        elif op == 'seqread':
            t = multiprocessing.Process(target=sequentialRead, args=(block_size,))
        elif op == 'ranread':
            t = multiprocessing.Process(target=randomRead, args=(block_size,))
        list_of_t.append(t)
        t.start()

    for t in list_of_t:
        t.join()


def main():
    """
    Argv[1] ... operations  (rw, seqread, ranread)
    Argv[2] ... block sizes (1B, 1KB, 1MB, 10MB)
    Argv[3] ... threads     (1, 2 ,4 ,8)
    """
    if len(sys.argv) != 4:              # error handling
        print 'Error: invalid arguments'
    else:
        op = sys.argv[1]
        if sys.argv[2] == '1B':
            block_size = 1
        elif sys.argv[2] == '1KB':
            block_size = 1024       # 1024 bit = 1 KB in file
        elif sys.argv[2] == '1MB':
            block_size = 1024 * 1024
        elif sys.argv[2] == '10MB':
            block_size = 10 * 1024 * 1024
        num_of_thread = int(sys.argv[3])

        start = time.time()
        createAndRunThread(op, block_size, num_of_thread)
        duration = time.time() - start
        diskspeed = (num_of_thread * (testfile_size / (1024 * 1024))) / duration
        print "Disk reading speed(MBytes/s): ", diskspeed
        print "Latency(ms):", duration / block_size / 1000

if __name__ == '__main__':
    main()
