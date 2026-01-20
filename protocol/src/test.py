import socket
import sys

def send(message, sockname):
    sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    sock.connect(sockname)
    sock.sendall(message.encode())
    sock.close()

if __name__=="__main__":
    send(sys.argv[2], sys.argv[1])