import sys
import multiprocessing
import time

def flops():
    """
    floating point operations per second
    """
    nums = [1.3, 10.5, 12.1, 30.4]

def iops():
    """
    integer operations per second
    """
    nums = [5, 20, 12, 30]

def main():
    """
        argv 1:number of thread argv 2: iops or flops, note:0 is script
        thread: 1, 2, 4, 8
        operation: iops, flops
    """
    if len(sys.argv) != 3:              # error handling
        print('Error: invalid arguments')
    else:
        num_of_thread = int(sys.argv[1])
        data_type = sys.argv[2]

        if data_type == 'iops':
            start = time.time()
            print('iops')
            duration = time.time() - start

        elif data_type == 'flops':
            start = time.time()
            print('flops')
            duration = time.time() - start
        print(duration)

if __name__ == '__main__':
    main()
