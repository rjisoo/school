import string
import sys


# Tokens:
# [ [, ], +, -, *, ^, /, ", >, >=, <, <=, =, !=, :=, if, while, let, not, sin, cos, tan, or, and, stdout, bool, int, float, string]

LB 			= 0 	# [
RB 			=	1 	# ]
PLUS 		=	2 	# +
MINUS 	= 3 	# -
MULT 		=	4 	# *
POWER 	= 5 	# ^
MOD 		= 6 	# %
DIV 		= 7 	# /
GT 			=	9 	# >
GTEQ 		=	10 	# >=
LT 			=	11 	# <
LTEQ 		=	12 	# <=
NEQ 		=	13 	# !=
EQ 			=	14 	# =
ASSGN 	= 15 	# :=
IF 			=	16 	# if
WHILE 	= 17 	# while
LET 		=	18 	# let
NOT 		=	19 	# not
OR 			=	20 	# or
AND 		=	21 	# and
PRINT 	= 22 	# stdout
TYPE_I 	= 23 	# literally written bool
TYPE_F 	= 22 	# literally written float
TYPE_S 	= 24 	# literally written string
INT 		= 25 	# [-][0-9]
FLOAT 	= 26 	# [-][0-9].[0-9] OR [-][0-9]e[-][0-9]
STRING 	= 27 	# "[alpha-numeric]"
ID 			= 28 	# [_][alpha][alpha-numeric,_]




def lex(data, line):
	lexemes = []
  chars = []
  num = []
  length = len(data)
  x = 0

  while x < length:
  	cur = data[x]
  	if cur == '[':
  		lexemes.append([LB, cur])
  		x+=1
  	
  	elif cur == ']':
  		lexemes.append([RB, cur])
  		x+=1

  	elif cur.isdigit(): # go find a num
  		y = x
  		num.append(data[y])
  		y+=1
  		while data[y].isdigit(): # read nums until not num
  			num.append(data[y])
  			y+=1
  		if daya[y] == '.': # found potential first half of real with .
  			num.append(data[y])
  			y+=1
  			while data[y].isdigit(): # find all the nums
  				num.append(data[y])
  				y+=1
  			if data[y] == '.' or data[y].isalpha():
  				num.append(data[y])
  				print "Error! Invalid number: '%s'... (Line %d, Column %d)" % (''.join(num), line, x+1)
  				sys.exit(1)
  		if data[y] == 'e' or data[y] == 'E': #first half of real with e
  			num.append(data[y])
  			y+=1
  			if data[y] == '-' or data[y] == '+': #nume[+,-]num
  				num.append(data[y])
  				y+=1
  			while data[y].isdigit():
  				num.append(data[y])
  				y+=1
  			if data[y] == '.' or data[y].isalpha():
  				num.append(data[y])
  				print "Error! Invalid number: '%s'... (Line %d, Column %d)" % (''.join(num), line, x+1)
  				sys.exit(1)
  			lexemes.append([FLOAT, float(''.join(num))])
  		else:
  			lexemes.append([INT, int(''.join(num))])
  		x = y
  		del num[:]
  	elif cure == '\n':
  		x+=1
  	elif cur.isspace():
  		x+=1
  	else:
  		print "I don't know what I was expecting..."
  		sys.exit(1)

  return lexemes