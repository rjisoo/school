#!/usr/bin/env python

"""
An echo server that uses select to handle multiple clients at a time.
Entering any line of input at the terminal will exit the server.
"""

import select
import socket
import sys

def main(argv):
    
    backlog = 5
    size = 1024
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (sys.argv[1], int(sys.argv[2]))
    server.bind(server_address)
    server.listen(backlog)
    inputs = [server,sys.stdin]
    running = 1
    while running:
        inputready,outputready,exceptready = select.select(inputs,[],[])

        for s in inputready:

            if s == server:
                # handle the server socket
                client, address = server.accept()
                inputs.append(client)

            elif s == sys.stdin:
                # handle standard input
                junk = sys.stdin.readline()
                running = 0

            else:
                # handle all other sockets
                data = s.recv(size)
                if data:
                    s.send(data)
                else:
                    s.close()
                    inputs.remove(s)
    server.close()
    
if __name__ == "__main__":
    main(sys.argv[1:])