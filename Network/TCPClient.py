import sys
import socket
import time

def main():
    """ main """
    target_host = '127.0.0.1'
    target_port = 9999

    # create a socket object
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # connect the client
    client.connect((target_host, target_port))
    start = time.time()
    # send some data
    client.send("GET / HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n")

    # receive data
    response = client.recv(4096)
    duration = start - time.time()

if __name__ == '__main__':
    main()
