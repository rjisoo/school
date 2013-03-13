"""
An echo client that allows the user to send multiple lines to the server.
Entering a blank line will exit the client.
"""

import socket
import sys

host = 'localhost'
port = 50001
size = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host,port))

if sys.argv[1] == "-v":
    s.send(sys.argv[1])
    data = s.recv(size)
    sys.stdout.write(data)
    sys.stdout.write("\n")
    s.close