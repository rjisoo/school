#!/usr/bin/env python

"""
An echo server that uses select to handle multiple clients at a time.
Entering any line of input at the terminal will exit the server.
"""

import select
import socket
import sys
import signal

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def main(argv):
    
    signal.signal(signal.SIGHUP, SigTest)
    signal.signal(signal.SIGINT, SigTest)
    signal.signal(signal.SIGQUIT, SigTest)
    
    size = 1024
    initServer(sys.argv[1], int(sys.argv[2]), 70)
    
    clients = []
    inputs = [server,sys.stdin]
    running = 1
    while running:
        inputready,outputready,exceptready = select.select(inputs,[],[])

        for s in inputready:

            if s == server:
                # handle the server socket
                client, address = server.accept()
                print >>sys.stderr, 'new connection from', address
                clients.append(address[1])
                client.setblocking(0)
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
                    print >>sys.stderr, 'Removing client ', address[1], 'from list'
                    inputs.remove(s)
    server.close()
    
def SigTest(SIG, FRM):
#    print "Caught signal: ", SIG
    server.close()
    sys.exit()
    
def initServer(ipaddr, port, num_clients):
    
    server.setblocking(0)
    
    server_address = (ipaddr, port)
    
    print >>sys.stderr, 'starting up on %s port %s' % server_address
    server.bind(server_address)
    
    server.listen(num_clients)
    
    
if __name__ == "__main__":
    main(sys.argv[1:])