import socket
# import threading

bind_ip = "127.0.0.1"
bind_port = 9999

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind((bind_ip, bind_port))
print "[*] Listening from %s:%d" % (bind_ip, bind_port)


def handle_client():

    recv_data, addr = server.recvfrom(1024)

    print "[*] Reveived: %s" % recv_data

    # send back a packet
    server.sendto("Response", addr)

while True:
    # spin up our client thread to handle incoming data
    # client_handler = threading.Thread(target=handle_client)
    # client_handler.start()
    handle_client()
