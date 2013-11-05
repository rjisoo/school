#!/usr/bin/env python

#Eric Timmerman, Stephanie Ison, Geoffrey Corey

import math
import time
import sys
import random

def algorithm1 (num_list, num_list2):
	start = time.time()
	result = algorithm1_helper(num_list)
	result2 = algorithm1_helper(num_list2)
	end = time.time()
	run = end - start
	#print ("Run time is %f seconds" % run)
	#print ("%f" % run)
	return run
	#print (result)
	#print (result2)
	#total = result[0] - result2[0]
	#print (total)

def algorithm1_helper (num_list):
	min = sys.maxint
	total = 0
	for i in range(len(num_list) - 1, -1, -1):
		total = total + num_list[i]
		if (abs(total) < min):
			min = abs(total)
			left = i
			right = len(num_list)
	results = (min, left, right)
	return results

def algorithm2 (num_list, num_list2):
	start = time.time()
	num_list = algorithm2_helper (num_list)
	num_list2 = algorithm2_helper (num_list2)
	num_list.sort()
	num_list2.sort()
	min = num_list[0] - num_list2[0] 
	stop = time.time()
	run  = stop - start
	#print ("Run time is %f" % run)
	#print (min)
	#print ("%f" % run)
	return run
	

def algorithm2_helper (num_list):
	list = []
	total = 0
	for i in range(len(num_list) - 1, -1, -1):
		total = total + num_list[i]
		list.append(total)
	return list

def generate_list (size):
	num_list = []
	for i in range(size):
		num_list.append(random.randint(-2000, 2000))
	return num_list

def algorithm3 (num_list):
	start = time.time()
	half = len(num_list)
	half = half / 2
	first_half = num_list[: half]
	second_half = num_list[half: ]
	min_left = algorithm34_helper(first_half)
	min_right = algorithm34_helper(second_half)
	second_half.reverse()
	algorithm1 (first_half, second_half)
	stop = time.time()
	run = stop - start
	#print(run)
	return run
#	print("min left %d" %min_left)
#	print ("min right %d" % min_left)

def algorithm4 (num_list):
	start = time.time()
	half = len(num_list)
	half = half / 2
	first_half = num_list[: half]
	second_half = num_list[half: ]
	min_left = algorithm34_helper(first_half)
	min_right = algorithm34_helper(second_half)
	second_half.reverse()
	algorithm2 (first_half, second_half)
	stop = time.time()
	run = stop - start
	#print(run)
	return run
#	print ("min left %d" %min_left) 
#	print ("min right %d" %min_right)

def algorithm34_helper(half):
	if len(half) <= 1:
		return 0
	left = half[ : len(half) / 2]
	right = half[len(half) / 2 : ]
	left_min = algorithm34_helper(left)
	right_min = algorithm34_helper(right)
	cross_min = min(right) + max(left)
	return min(left_min, right_min, cross_min)

if __name__ == "__main__":
#	list1 = generate_list(100)
#	list2 = generate_list(100)
#	algorithm1 (list1, list2)
#	algorithm2 (list1, list2)
#	list3 = generate_list(200)
#	algorithm3 (list3)
	for i in range(0, 10):
		list1 = generate_list(100)
		list2 = generate_list(100)
		print("algorithm one")
		algorithm1(list1, list2)
		print("algorithm two")
		algorithm2(list1, list2)
		list3 = generate_list(200)
		print("algorithm three")
		algorithm3(list3)
		print("algorithm four")
		algorithm4(list3)
		print(list1)
		print(list2)
		print(list3)