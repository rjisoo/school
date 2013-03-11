#!/usr/bin/env python2

import sys
import socket
import select
import signal

def signal_handler(signal, frame):
    print "Caught signal number: %d" % signal
    sys.exit(0)
    

def main():
    
    size= 4096
    
    signal.signal(signal.SIGHUP, signal_handler)
    signal.signal(signal.SIGINT, signal_handler)
    server = setup_server(socket.gethostname(), 50000, 5)
    
    input1 = [server, sys.stdin]
    
    running = 1
    
    while running:
        
        inputready, outputready, exceptready = select.select(input1, [], [])
        
        for s in inputready:
            
            if s == server:
                # handle the server socket
                client, address = server.accept()
                input1.append(client)
            
            elif s == sys.stdin:
                # handle standard input
                junk = sys.stdin.readline()
                running = 0
                
            else:
                # handle all other sockets
                data = s.recv(size)
                if data:
                    print >>sys.stderr, 'connection from', address
                    #sys.stdout.write(data)
                    #s.send(data)
                else:
                    s.close()
                    input1.remove(s)
            
    server.close()
    sys.exit(0)

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