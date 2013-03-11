#!/usr/bin/env python2



import select
import socket
import signal
import sys
import errno

size= 4096

def main():
    """
An echo server that uses select to handle multiple clients at a time.
Entering any line of input at the terminal will exit the server.
"""

    #host = 'localhost'
    #port = 50000
    #backlog = 5
    #size = 1024
    #server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #server.bind((host, port))
    #server.listen(backlog)
    server = setup_server('localhost', 50000, 5)
    input = [server, sys.stdin]
    running = 1
    while running:
        inputready, outputready, exceptready = select.select(input, [], [])

        for s in inputready:

            if s == server:
                # handle the server socket
                client, address = server.accept()
                input.append(client)

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
                    input.remove(s)
    server.close()
    
def setup_server(host, port, nclients):
    
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind((host, port))
        server.listen(nclients)
    except socket.error, (value,message):
        if server:
            server.close()
        print "Could not open socket: " + message
        sys.exit(1)
    return server
    
    

if __name__ == '__main__':
    main()