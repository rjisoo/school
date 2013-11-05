#!/usr/bin/env python

# Project 1 code for CS325
# Group Mmebers: Eric Timmerman, Stephanie Ison, Geoffrey Corey

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
	return run

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
	print ("It contains the values ")
	for k in range(left, (right + 1)):
		print(num_list[k])
	return run


# This helper function takes the line element from test_case.txt
# and strips and splits it to being the list of usable numbers

def get_list (file):
	num_list = file
	num_list = num_list.split("]")
	num_list = num_list[0]
	num_list = num_list.strip("[")
	num_list = num_list.split(",")
	num_list = map(int, num_list)
	return num_list

def test_enumerate1(runs):
	
	times = []
	for i in range(0, 10):
		numbers = [random.randint(-10000000, 10000000) for x in xrange(runs)]
		times.append(enumeration1(numbers))

	return times

def test_enumerate2(runs):
	
	times = []
	for i in range(0, 10):
		numbers = [random.randint(-10000000, 10000000) for x in xrange(runs)]
		times.append(enumeration2(numbers))

	return times

def average(times):

	return sum(times)/len(times)
	
# this assumes that the test_case.txt file is located in the same directory as
# hw1.py. Also it is hardcoded (bad) to accept only test_case.txt
if __name__ == "__main__":
	with open('test_case.txt') as file:
		for line in file:
			numbers = get_list(line)
			enumeration1(numbers)
			enumeration2(numbers)

	#This was for generating the plot	
	#random.seed()

	# enum1
	#print "Enumeration1"
	#for i in range(0, 9):
	#	times = test_enumerate1((i+1)*100)
	#	print "%d: %f" % ((i+1)*100, average(times))
	#for i in range(0, 9):
	#	times = test_enumerate1((i+1)*1000)
	#	print "%d: %f" % ((i+1)*1000, average(times))

	# enum2
	#print "\n\n\nEnumeration2"
	#for i in range(0, 9):
	#	times = test_enumerate2((i+1)*100)
	#	print "%d: %f" % ((i+1)*100, average(times))
	#for i in range(0, 9):
	#	times = test_enumerate2((i+1)*1000)
	#	print "%d: %f" % ((i+1)*1000, average(times))