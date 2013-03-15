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

def SigTest(SIG, FRM):
    print "Caught signal: ", SIG
    server.close()
    sys.exit(0)
    
def main():
    signal.signal(signal.SIGINT, SigTest)
    signal.signal(signal.SIGQUIT, SigTest)
    signal.signal(signal.SIGHUP, SigTest)
    #host = ''
    #port = 50000
    backlog = 5
    size = 4096
    server.setblocking(0)
    server_address = (sys.argv[1], int(sys.argv[2]))
    print >>sys.stderr, 'starting up on %s port %s' % server_address
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
                print >>sys.stderr, 'new connection from', address
                inputs.append(client)

            elif s == sys.stdin:
                # handle standard input
                junk = sys.stdin.readline()
                server.close()
                sys.exit(0)
                #running = 0

            else:
                # handle all other sockets
                data = s.recv(size)
                if data:
                    print >>sys.stderr, 'received "%s" from %s' % (data, s.getpeername())
                    s.send(data)
                else:
                    s.close()
                    inputs.remove(s)
    server.close()
    
if __name__ == '__main__':
    main() 