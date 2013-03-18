#!/usr/bin/env python2
"""
An echo client that allows the user to send multiple lines to the server.
Entering a blank line will exit the client.
"""

import socket
import sys

def main(argv):

    host = sys.argv[1]
    port = int(sys.argv[2])
    size = 1024
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        s.connect((host,port))
    except socket.error as e:
        print "Socket error({0}): {1}".format(e.errno, e.strerror)
        print "Unable to start server" 
        sys.exit(1)
        
    s.send('m')
    data = s.recv(size)
    s.close()
    print 'Received:', data
    
if __name__ == "__main__":
    main(sys.argv[1:]) 