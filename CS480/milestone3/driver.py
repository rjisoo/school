#!/usr/bin/env python
import sys
#import mylex

def main(argument):
	lexemes = []
	x = 1

	with open(argument, 'r') as f:
		data = f.readlines() #read the file line by line

	#for line in data:
	#	thing = [line, ' ', ' ']
	#	lexemes.append(lex(''.join(thing), x))
	#	del thing[:]
	#	x+=1
	for line in data:
		print "line :", line

	#print lexemes

if __name__ == "__main__":
  main(sys.argv[1])