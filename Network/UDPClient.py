import socket
import sys
import multiprocessing
import time
"""
for mac testing command: 
due to by default macOS has limited the maximum UDP-package to be 9216 bytes
"""

def send2server(bytes2send):
    """
    Send packet to server
    arg:
        bytes2send...bytes
    """
    target_host = "127.0.0.1"
    target_port = 9999

    # create a socket object
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    client.sendto(bytes2send, (target_host, target_port))
    data, addr = client.recvfrom(4096)

    print '[*] Get data:', data

def main():
    if len(sys.argv) != 2:              # error handling
        print 'Error: invalid arguments'
    elif int(sys.argv[1]) not in  [1, 2, 4, 8]:
        print 'Error: invalid arguments (Thread has to be 1, 2, 4, 8)'
    else:
        num_of_thread = int(sys.argv[1])

        f = open('TestFile64KB','rb')
        bt = f.read()
        print '[*] Send Packet with size(bytes)',  len(bt)
        # thread handling
        flg = int(len(bt) / num_of_thread)
        start_index = 0
        list_of_t = []
        start = time.time()
        for i in range(num_of_thread):
            end_index = start_index + flg
            if end_index > len(bt): #error handling
                break
            bytes2send = bt[start_index:end_index]
            t = multiprocessing.Process(target=send2server, args=(bytes2send,))
            list_of_t.append(t)
            t.start()
            start_index = end_index

        for t in list_of_t:
            t.join()

        duration = time.time() - start
        print 'Time elapsed', duration
        print 'Throughput(Mega Bits/Sec)', (len(bt) * 0.000008) / duration 
        f.close()



if __name__ == '__main__':
    main()
