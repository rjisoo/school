#!/usr/bin/env python

def greedy(amount, coins):
	denoms = sorted(coins) #sanity check
	denoms.reverse() 	#sanity check
	coins = 0
	while (amount > 0):
		if (amount >= denoms[0]):
			num = amount / denoms[0]
			amount -= (num * denoms[0])
			coins += num
		denoms = denoms[1:]
	return coins

coins = [1, 10, 25, 50]

for x in range(2000, 2050):
	print greedy(x, coins)
	#print greedy2(x, coins)

#print greedy(47, coins)
#print greedy(201, coins)