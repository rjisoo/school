#!/usr/bin/env python

import math
import time
import sys
import random

# This function takes a list of numbers and goes through each value
# with each value it goes through another loop to add each of the subsequent
# members of the list. This total is then compared with the running minimum to
# find the smallest minimum value, which equates to the closest to zero
# That value is then printed and the members of the list that gave that value are
# printed.
def enumeration1 (num_list):
	min = sys.maxint
	start = time.time()
	for i in range(0, len(num_list)):
		total = 0
		for j in range(i, len(num_list)):
			total = total + num_list[j]
			if (abs(total) < min):
				min = abs(total)
				left = i
				right = j
	end = time.time()
	run = end - start
	print ("Run time is %f seconds" % run)
	print ("Minimum value is %d" % min)
	print ("It contains the values ")
	for k in range(left, (right + 1)):
		print (num_list[k])

# This function takes a list of numbers and goes through each value
# another loop goes up adding the numbers until it gets to the end of the list
# all the while checking agains the minimum value then goes back down the number
# list ensuring every combination only happens once.
	


def enumeration2 (num_list):
	min = sys.maxint
	total = 0
	dir = True
	start = time.time()
	for i in range(0, len(num_list)):
		if (dir == True):
			total = 0
			for j in range(i, len(num_list)):
				total = total + num_list[j]
				if (abs(total) < min):
					min = abs(total)
					left = i
					right = j

		if (dir == False):
			for j in range((len(num_list) - 1), (i - 1), -1):
				total = total - num_list[j]
				if (abs(total) < min):
					min = abs(total)
					left = i
					right = j
		dir = not dir
	end = time.time()
	run = end - start
	print ("Run time is %f seconds" % run)
	print ("Minimum value is %d" % min)
	#print ("It contains the values ")
	#for k in range(left, (right + 1)):
	#	print(num_list[k])


# This helper function takes the line element from test_case.txt
# and strips and splits it to being the list of usable numbers

def get_list (file):
	num_list = file.readline()
	num_list = num_list.split("]")
	num_list = num_list[0]
	num_list = num_list.strip("[")
	num_list = num_list.split(",")
	num_list = map(int, num_list)
	return num_list
	
if __name__ == "__main__":
#	f = open('test_case.txt')
#	numbers = get_list(f)
#	enumeration2(numbers)
#	numbers = get_list(f)
#	enumeration1(numbers)
#	numbers = get_list(f)
#	enumeration2(numbers)
	random.seed()
	#numbers = [random.randint(-10000000, 10000000) for x in xrange(100)]
#	print numbers
	for i in range(0, 10)
		numbers = [random.randint(-10000000, 10000000) for x in xrange(100)]
		enumeration1(numbers)

