#!/usr/bin/env python

#Eric Timmerman, Stephanie Ison, Geoffrey Corey

import sys
import math
import time

def changegreedy(coins, amount):
	denoms = sorted(coins) #sanity check
	denoms.reverse() 	#sanity check
	coins = 0
	start = time.time()
	while (amount > 0):
		if (amount >= denoms[0]):
			num = amount / denoms[0]
			amount -= (num * denoms[0])
			coins += num
		denoms = denoms[1:]
	end = time.time()
	return coins
	#return end - start


def changedp (coins, change):
	min_coins = [None for x in range(change + 1)]
	min_coins[0] = []

	start = time.time()
	for i in range(1, change + 1):
		for coin in coins:
			if coin >  i: continue
			elif not min_coins[i] or len(min_coins[i - coin]) + 1 < len(min_coins[i]):
				if min_coins[i - coin] != None:
					min_coins[i] = min_coins[i - coin][:]
					min_coins[i].append(coin)
	end = time.time()

	return len(min_coins[-1])
	#return end - start


if __name__ == "__main__":
	coins = [1, 5, 10, 25, 50]

	for x in range(2000, 2301):
		print ("%d 	%d 	%d" % (x, changegreedy(coins, x), changedp(coins, x)))
		#greedy = []
		#dp = []
		
		#for i in range(0, 10):
		#	greedy.append(changegreedy(coins, x))
		#	dp.append(changedp(coins, x))

		#print ("%d 	%f 	%f" % (x, reduce(lambda x, y: x + y, greedy) / len(greedy), reduce(lambda x, y: x + y, dp) / len(dp)))