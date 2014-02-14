#!/usr/bin/env python
import string
import sys


# Tokens:
# [ [, ], +, -, *, ^, /, ", >, >=, <, <=, =, !=, :=, if, while, let, not, sin, cos, tan, or, and, stdout, bool, int, float, string]

LB      = 0   # [
RB      = 1   # ]
PLUS    = 2   # +
MINUS   = 3   # -
MULT    = 4   # *
POWER   = 5   # ^
MOD     = 6   # %
DIV     = 7   # /
GT      = 9   # >
GTEQ    = 10  # >=
LT      = 11  # <
LTEQ    = 12  # <=
NEQ     = 13  # !=
EQ      = 14  # =
ASSGN   = 15  # :=
IF      = 16  # if
WHILE   = 17  # while
LET     = 18  # let
NOT     = 19  # not
OR      = 20  # or
AND     = 21  # and
PRINT   = 22  # stdout
TYPE_I  = 23  # literally written bool
TYPE_F  = 22  # literally written float
TYPE_S  = 24  # literally written string
INT     = 25  # [-][0-9]
FLOAT   = 26  # [-][0-9].[0-9] OR [-][0-9]e[-][0-9]
STRING  = 27  # "[alpha-numeric]"
ID      = 28  # [_][alpha][alpha-numeric,_]




def lex(data, line):
  tokens = []
  x = 0
  y = 0

  while (x < len(data)):
    cur = data[x]
    if cur.isdigit():
      x = find_num(tokens, data, x, line)
    elif cur == '-':
      y = find_num(tokens, data, x, line)
      if y == x:
        tokens.append([MINUS, cur])
      else:
        x = y
        
    elif cur == '\n':
      x+=1
    else:
      print "I don't know what I was expecting..."
      sys.exit(1)


  return tokens

def find_string_lit(tokens, data, position, line): # the only way to get in this function is by seeing a "
  y = position
  chars = []

  chars.append(data[y])# the only way to get in this function is by seeing a " before hand
  y+=1

  while(y < len(data) and not data[y] == '"'):
    chars.append(data[y])
    y+=1

  if data[y] == '"':
    chars.append(data[y])
    y+=1
    tokens.append([STRING, ''.join(chars)])
  else:
    print 'Error, invalid string literal, missing ending " (Line %d, Column %d)' % (line, y)
    sys.exit(1)

  return y

def find_num(tokens, data, position, line):
  num = []
  y = position

  if data[y] == '-':
    num.append(data[y])
    y+=1
    if not data[y].isdigit():
      return position

  while data[y].isdigit():
    num.append(data[y])
    y+=1
  if data[y] == 'e' or data[y] == 'E':
    num.append(data[y])
    y+=1
    if data[y] == '+' or data[y] == '-':
      num.append(data[y])
      y+=1
    while data[y].isdigit():
      num.append(data[y])
      y+=1
    if data[y] == '.' or data[y] == 'e' or data[y] == 'E':
      num.append(data[y])
      print "Error! Invalid number: '%s'... (Line %d, Column %d)" % (''.join(num), line, y+1)
      sys.exit(1)
    if float(''.join(num)) == float("infinity") or float(''.join(num)) == float("-infinity"):
      print "Error! Number is infinity."
      sys.exit(1)
    else:
      tokens.append([FLOAT, float(''.join(num))])
  elif data[y] == '.':
    num.append(data[y])
    y+=1
    if not data[y].isdigit(): # if . not followed immediately by digit
      print "Error! Invalid number: '%s'... (Line %d, Column %d)" % (''.join(num), line, y+1)
      sys.exit(1)
    else:
      while data[y].isdigit():
        num.append(data[y])
        y+=1
      if data[y] == 'e' or data[y] == 'E': # can have form of 12.3e45...
        num.append(data[y])
        y+=1
        if data[y] == '-' or data[y] == '+':
          num.append(data[y])
          y+=1
        while data[y].isdigit():
          num.append(data[y])
          y+=1
        if data[y] == '.' or data[y] == 'e' or data[y] == 'E':
          num.append(data[y])
          print "Error! Invalid number: '%s'... (Line %d, Column %d)" % (''.join(num), line, y+1)
          sys.exit(1)
        if float(''.join(num)) == float("infinity") or float(''.join(num)) == float("-infinity"):
          print "Error! Number is infinity."
          sys.exit(1)
    tokens.append([FLOAT, float(''.join(num))])

  else:
    tokens.append([INT, int(''.join(num))])


  return y

if __name__ == "__main__":
  lexemes = []
  x = 1

  with open(sys.argv[1], 'r') as f:
    data = f.readlines()

  for line in data:
    lexemes.append(lex(line, x))
    x+=1

  print lexemes