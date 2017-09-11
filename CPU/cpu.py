import sys
import threading
import time

def flops():
    """
    floating point operations per second
    """
    nums = [1.3, 10.5, 12.1, 30.4]
    nums[0] += nums[1] + nums[2] + nums[3]

def iops():
    """
    integer operations per second
    """
    nums = [5, 20, 12, 30]
    nums[0] += nums[1] + nums[2] + nums[3]

def createAndRunThread(num_of_thread, data_type):
    """
    Create and run the thread
    Args:
        num_of_thread
        data_type
    Returns:
        Nothing
    """
    if data_type == 'flops':
        for i in range(num_of_thread):
            t = threading.Thread(target=flops)
            t.start()
    elif data_type == 'iops':
        for i in range(num_of_thread):
            t = threading.Thread(target=iops)
            t.start()


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

        start = time.time()
        createAndRunThread(num_of_thread, data_type)
        duration = time.time() - start
        g_duration = duration / (10**9)
        if data_type == 'flops':
            print(  "Giga FLOPS:", g_duration)
        else:
            print(  "Giga ILOPS:", g_duration)

if __name__ == '__main__':
    main()
