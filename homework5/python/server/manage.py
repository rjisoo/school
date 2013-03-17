#!/usr/bin/env python2

import select
import socket
import sys
import Queue
import signal

maxrange = 4294967296

def main(argv):
    
    if len(sys.argv) != 3:
        print >>sys.stderr, "Usage: manage.py ip_address port_number\n"
        sys.exit(1)
        
    # Create a TCP/IP socket
    global server
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setblocking(0)
    
    signal.signal(signal.SIGHUP, SigTest)
    signal.signal(signal.SIGINT, SigTest)
    signal.signal(signal.SIGQUIT, SigTest)

    # Bind the socket to the port
    server_address = (sys.argv[1], int(sys.argv[2]))
    print >>sys.stderr, 'starting up on %s port %s' % server_address
    
    try:
        server.bind(server_address)
    except socket.error as e:
        print "Socket error({0}): {1}".format(e.errno, e.strerror)
        print "Unable to start server" 
        sys.exit(1) 
        
    # Listen for incoming connections
    server.listen(5)
    
    # Sockets from which we expect to read
    inputs = [ server ]

    # Sockets to which we expect to write
    outputs = [ ]
    
    # Outgoing message queues (socket:Queue)
    message_queues = {}
    
    while inputs:

        # Wait for at least one of the sockets to be ready for processing
        print >>sys.stderr, '\nwaiting for the next event'
        readable, writable, exceptional = select.select(inputs, outputs, inputs)
        
        # Handle inputs
        for s in readable:

            if s is server:
                # A "readable" server socket is ready to accept a connection
                connection, client_address = s.accept()
                print >>sys.stderr, 'new connection from', client_address
                print >>sys.stderr, "Client id: ", client_address[1]
                connection.setblocking(0)
                inputs.append(connection)

                # Give the connection a queue for data we want to send
                message_queues[connection] = Queue.Queue()
                
            else:
                data = s.recv(1024)
                if data:
                    # A readable client socket has data
                    print >>sys.stderr, 'received "%s" from %s' % (data, s.getpeername())
                    message_queues[s].put(data)
                    # Add output channel for response
                    if s not in outputs:
                        outputs.append(s)

                else:
                    # Interpret empty result as closed connection
                    print >>sys.stderr, 'closing', client_address, 'after reading no data'
                    # Stop listening for input on the connection
                    if s in outputs:
                        outputs.remove(s)
                    inputs.remove(s)
                    s.close()

                    # Remove message queue
                    del message_queues[s]
                    
        # Handle outputs
        for s in writable:
            try:
                next_msg = message_queues[s].get_nowait()
            except Queue.Empty:
                # No messages waiting so stop checking for writability.
                print >>sys.stderr, 'output queue for', s.getpeername(), 'is empty'
                outputs.remove(s)
            else:
                print >>sys.stderr, 'sending "%s" to %s' % (next_msg, s.getpeername())
                s.send(next_msg)
                


        # Handle "exceptional conditions"
        for s in exceptional:
            print >>sys.stderr, 'handling exceptional condition for', s.getpeername()
            # Stop listening for input on the connection
            inputs.remove(s)
            if s in outputs:
                outputs.remove(s)
            s.close()

            # Remove message queue
            del message_queues[s]



def SigTest(SIG, FRM):
#    print "Caught signal: ", SIG
    global server
    server.close()
    sys.exit()
    

def getRangeFromIOPS(minimum, maximum, iops):
    
    i = 0
    value = minimum
    
    while i < 15*iops and value < maximum:
        value += 1
        i += value
    
    #check to make sure that min value increases as min get higher
    if value == minimum:
        value += 1
        
    return value



if __name__ == "__main__":
    main(sys.argv[1:])