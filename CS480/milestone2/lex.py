#!/usr/bin/env python

import sys
import itertools
from collections import namedtuple
import string

LBRACKET = 0
RBRACKET = 1
KEYWORD = 2
SYMBOL = 3
REAL = 4
INTEGER = 5
ID = 6
STRING = 7
TYPE = 8

TOKEN = {LBRACKET: "LBRACKET", RBRACKET: "RBRACKET", KEYWORD: "KEYWORD", SYMBOL: "SYMBOL", 
          REAL: "REAL", INTEGER: "INTEGER", ID: "ID", STRING: "STRING", TYPE: "TYPE"}

symbols = ["+", "-", "*", "/", "%", "^", "=", ">", ">=", "<" "<=", "!=", "[", "]", ":="]
keywords = ["if", "while", "let", "not", "sin", "cos", "tan", "or", "and", "stdout"]
type_ = ["bool", "int", "float", "string"]


def main(argument):

  lexemes = []
  x = 1

  with open(argument, 'r') as f:
    data = f.readlines() #read the file line by line

  for line in data:
    lexemes.append(lex(line, x))
    x+=1

  print lexemes

    #lexemes = lex(data)
    #for thing in lexemes:
    #  print thing
  #lex(data)

def test(line, x):
  print x


def lex(data, line):
  lexemes = []
  chars = []
  num = []
  length = len(data)
  x = 0

  while (x < length):
    cur = data[x]
    if cur == '[':
      lexemes.append([TOKEN[LBRACKET], cur])
      x+=1
    elif cur == ']':
      lexemes.append([TOKEN[RBRACKET], cur])
      x+=1 
    
    elif cur.isdigit(): #start of a number
      y = x
      while data[y].isdigit():
        num.append(data[y])
        y+=1
      #either found a int, or the first half of a real
      if data[y] == '.': #find the rest of the real
        num.append(data[y])
        y+=1
        while data[y].isdigit():
          num.append(data[y])
          y+=1
        if data[y] == '.' or data[y].isalpha():
          num.append(data[y])
          print "Error! Invalid number: '%s'... (Line %d, Column %d)" % (''.join(num), line, x+1)
          sys.exit(0)
        lexemes.append([TOKEN[REAL], float(''.join(num))])
      else:
        lexemes.append([TOKEN[INTEGER], int(''.join(num))])

      x = y
      del num[:]

    elif cur == '+':
      lexemes.append([TOKEN[SYMBOL], cur])
      x+=1

    elif cur == '-':
      #check if next value is number or space
      if data[x+1].isdigit():
        #let the number lexer take care of getting the number
        num.append(cur)
        x+=1
      elif data[x+1].isspace():
        #this is subtraction
        lexemes.append([TOKEN[SYMBOL], cur])
        x+=1
      elif data[x+1].isalpha():
        print "Error! Invalid number or negative/subraction operand: '%s%s'... (Line %d, Column %d)" % (cur, data[x+1], line, x+1)
        sys.exit(0)

    elif cur == ':' or cur == '!':
      if data[x+1] != '=':
        print "Error! Invalid token: '%s%s'... (Line %d, Column %d)" % (cur, data[x+1], line, x+1)
        sys.exit(0)
      else:
        lexemes.append([TOKEN[SYMBOL], ''.join([cur, data[x+1]])])
        x+=2

    elif cur == '<' or cur == '>':
      if data[x+1] != '=':
        lexemes.append([TOKEN[SYMBOL], cur])
        x+=1
      else:
        lexemes.append([TOKEN[SYMBOL], ''.join([cur, data[x+1]])])
        x+=2

    elif (cur == '+' or cur == '*' or cur == '/' or
          cur == '=' or cur == '^' or cur == '%'):
      lexemes.append([TOKEN[SYMBOL], cur])
      x+=1

    elif cur.isalpha() or cur == '_': #parse for known words or symbols
      mystring = None
      while data[x].isalnum() or data[x] == '_':
        chars.append(data[x])
        x+=1
      if not data[x+1] == '\n' or not data[x+1].isspace():
        print "Error, invalid string: %s%s (Line: %d, Column %d)" % (''.join(chars), data[x+1], line, x+1)
        sys.exit(0)
      else: #we have a valid string
        mystring = ''.join(chars)
        del chars[:]
        dict_id = None
        
        if (mystring == "not" or mystring == "and" or mystring == "tan" or
            mystring == "cos" or mystring == "tan" or mystring == "sin" or
            mystring == "if" or mystring == "while" or mystring == "let" or
            mystring == "stdout"
            ):
          dict_id = TOKEN[KEYWORD]
        
        elif (mystring == "bool" or  mystring == "string" or mystring == "int" or
              mystring == "float" or mystring == "true" or mystring == "false"
              ):
          dict_id = TOKEN[TYPE]
        
        else:
          dict_id = TOKEN[STRING]

      lexemes.append([dict_id, mystring])




 
    elif cur == '\n':
      x+=1
    elif cur.isspace():
      x+=1
    else:
      print "I don't know what I was expecting..."
      sys.exit(0)

  return lexemes



  
if __name__ == "__main__":
  main(sys.argv[1])