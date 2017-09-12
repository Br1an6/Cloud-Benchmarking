import socket
import threading

bind_ip = "127.0.0.1"
bind_port = 9999

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((bind_ip, bind_port))
server.listen(5)


def handle_client(client_socket):

    # send something
    client_socket.send("Connected\r\n")

    # print out what the client sends
    request = client_socket.recv(1024)

    # send back a packet
    client_socket.send("ACK!\r\n")

    client_socket.close()

while True:
    client, addr = server.accept()

    # spin up our client thread to handle incoming data
    client_handler = threading.Thread(target=handle_client,args=(client,))
    client_handler.start()
