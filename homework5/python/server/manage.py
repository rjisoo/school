#!/usr/bin/env python2

"""
An echo server that uses select to handle multiple clients at a time.
Entering any line of input at the terminal will exit the server.
"""

import select
import socket
import sys
import signal

def main(argv):
    
    if len(sys.argv) != 3:
        print 'Usage: manage.py ip_address port'
        sys.exit(1)
       
    
    global server
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setblocking(0)
        
    server_address = (sys.argv[1], int(sys.argv[2]))  
    try:  
        server.bind(server_address)
    except socket.error as e:
        print "Socket error({0}): {1}".format(e.errno, e.strerror)
        print "Unable to start server" 
        sys.exit(1)  
    #print >>sys.stderr, 'starting up on %s port %s' % server_address    
    server.listen(70)
    
    signal.signal(signal.SIGHUP, SigTest)
    signal.signal(signal.SIGINT, SigTest)
    signal.signal(signal.SIGQUIT, SigTest)
    
    size = 1024
    maxrange = 4294967296
    minrange = 1
    perfect_nums = []
    
    clients = []
    inputs = [server]

    running = 1
    
    while running:
        inputready, outputready, exceptready = select.select(inputs, [], inputs)

        for s in inputready:

            if s == server:
                # handle the server socket
                client, address = server.accept()
                #print >>sys.stderr, 'new connection from', address
                clients.append([int(address[1])])
                client.setblocking(0)
                inputs.append(client)

            else:
                # handle all other sockets
                data = str(s.recv(size))
                if data:
                    if data[0] == 'i':
                        #it is IOPS
                        data = data.replace("i", "")
                        #print >>sys.stderr, 'IOPS from ', address[1],': ', int(data)
                        #add IOPS to client
                        for x in clients:
                            if x[0] == int(address[1]):
                                x.append(int(data))
                        #Get range to send to client
                        uplimit = getRangeFromIOPS(minrange, maxrange, int(data)*15)
                        toclient = str(minrange) + ", " + str(uplimit)
                        #print "Sending range: ", toclient
                        s.send(toclient)
                        minrange = uplimit
                        
                    elif data[0] == 'p':
                        #it is a perfect number
                        data = data.replace("p", "")
                        perfect_nums.append(int(data))
                        
                    elif data[0] == 'm':
                        #it's manage, send the information
                        # report perfect found, lower limit tested,
                        # number of processes
                        
                        if len(perfect_nums) == 0:
                            data = "Perfects: 0, Being tested: "+ str(minrange) + ", number of processes: " + str(len(clients) - 1)
                        else:
                            data = "Perfects:" + ''.join(str(e) for e in perfect_nums) +", Being tested: "+ str(minrange) + ", number of processes: " + str(len(clients))
                        s.send(data)
                    
                    else:
                        #we need a new range for the compute
                        temp = s.getpeername()
                        for x in clients:
                            if x[0] == temp[1]:
                                uplimit = getRangeFromIOPS(minrange, maxrange, x[1]*15)                        
                                toclient = str(minrange) + ", " + str(uplimit)
                                #print "Sending range: ", toclient
                                s.send(toclient)
                                minrange = uplimit
                                break
                else:
                    temp = s.getpeername()
                    s.close()
                    #print >>sys.stderr, 'Removing client ', temp[1], 'from list'
                    for x in xrange(len(clients)-1, -1, -1):
                        if clients[x][0] == temp[1]:
                            del clients[x]
                    inputs.remove(s)
                
                    
    server.close()
    
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