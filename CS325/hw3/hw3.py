#!/usr/bin/env python

#Eric Timmerman, Stephanie Ison, Geoffrey Corey

import sys
import math
import time

def changegreedy(coins, amount):
	denoms = sorted(coins) #sanity check
	denoms.reverse() 	#sanity check
	result = []
	start = time.time()
	while (amount > 0):
		if (amount >= denoms[0]):
			num = amount / denoms[0]
			amount -= (num * denoms[0])
			result.append([denoms[0], num])
		denoms = denoms[1:]
	print result
	#return result
	

def changedp (coins, change):
	min_coins = [None for x in range(change + 1)]
	min_coins[0] = []

	for i in range(1, change + 1):
		for coin in coins:
			if coin >  i: continue
			elif not min_coins[i] or len(min_coins[i - coin]) + 1 < len(min_coins[i]):
				if min_coins[i - coin] != None:
					min_coins[i] = min_coins[i - coin][:]
					min_coins[i].append(coin)
	print '%d coins: %s' % (len(min_coins[-1]), min_coins[-1])


if __name__ == "__main__":
	# Set the coins here manually
	coins = [1, 10, 25, 50]

	# Set the change desired here manually
	change = 40
	print change

	print coins
	changegreedy(coins, change)
	changedp(coins, change)