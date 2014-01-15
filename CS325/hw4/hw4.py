#!/usr/bin/env python

#Eric Timmerman, Stephanie Ison, Geoffrey Corey

from pulp import *
from math import *

def linearFit(x_list, y_list):
	prob = LpProblem("Best fit line", LpMinimize)
	t = LpVariable("t", 0)
	a = LpVariable("a", 0)
	b = LpVariable("b", 0)
	double_list = zip(x_list, y_list)
	prob += t
	for x in double_list:
		prob += a * x[0] + b - x[1] <= t
		prob += -a * x[0] - b + x[1] <= t
	status = prob.solve()
	print LpStatus[status]
	new_a = value(a)
	new_b = value(b)
	print ("The line of best fit is y = %f * x + %f" % (new_a, new_b))

def warmFit(f):
	prob = LpProblem("Warm up fit", LpMinimize)
	t = LpVariable("t", 0)
	x0 = LpVariable("x0", 0)
	x1 = LpVariable("x1", 0)
	x2 = LpVariable("x2", 0)
	x3 = LpVariable("x3", 0)
	x4 = LpVariable("x4", 0)
	x5 = LpVariable("x5", 0)
	prob += t
	for line in f:
		values = parse(line)
		prob += x0 + (x1 * values[0]) + (x2 * cos((2 * pi * values[0]) / 364.25)) + (x3 * sin((2 * pi * values[0]) / 364.25)) + (x4 * cos((2 * pi * values[0]) / (364.25 * 10.7))) + (x5 * sin((2 * pi * values[0]) / (364.25 * 10.7))) - values[1]  <= t
		prob += - x0 - (x1 * values[0]) - (x2 * cos((2 * pi * values[0]) / 364.25)) - (x3 * sin((2 * pi * values[0]) / 364.25)) - (x4 * cos((2 * pi * values[0]) / (364.25 * 10.7))) - (x5 * sin((2 * pi * values[0]) / (364.25 * 10.7))) + values[1] <= t
	status = prob.solve()
	print LpStatus[status]
	solved = []
	solved.append(value(x0))
	solved.append(value(x1))
	solved.append(value(x2))
	solved.append(value(x3))
	solved.append(value(x4))
	solved.append(value(x5))
	print solved

def parse(line):
	new_list = line.strip("\n")
	new_list = line.split(";")
	new_list = new_list[7:]
	new_list.reverse()
	new_list = map(float, new_list)
	return new_list

if __name__ == "__main__":
	x_list = [1, 2, 3, 5, 7, 8, 10]
	y_list = [3, 5, 7, 11, 14, 15, 19]
	linearFit(x_list, y_list)
	f = open("Corvallis.csv")
	warmFit(f)
