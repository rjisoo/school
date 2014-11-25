#!/usr/bin/env python

from itertools import *
from hashlib import *
import numpy
import smtplib

fromaddr = 'yourapanzy91@gmail.com'
toaddr = 'yourapanzy91+crypto@gmail.com'
username = 'yourapanzy91'

alpha = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]

test = list(combinations(alpha, 7))

server = smtplib.SMTP('smtp.gmail.com:587')
server.starttls()  
server.login(username,password) 

for x in xrange(0, len(test)):
	for i in xrange(0, len(test)/2):
		m1 = new("md5")
		m2 = new("md5")
		str1 = ''.join(test[x])
		str2 = ''.join(test[x+i+1])
		m1.update(str1)
		m2.update(str2)
		hash1 = m1.hexdigest()
		hash2 = m2.hexdigest()
		if hash1[0:4] == hash2[0:4]:
			if hash1[28:32] == hash2[28:32]:
				msg = "Found partial collision, value1: %s, \tvaue2: %s" % ('abc', 'def')
				server.sendmail(fromaddr, toaddrs, msg)
				print "String1: %s \tHash1: %s" % (str1, hash1)
				print "String2: %s \tHash2: %s" % (str2, hash2)

server.quit()
