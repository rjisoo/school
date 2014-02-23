#!/usr/bin/env python
import collections
import myreglexer
import sys

def parser(stream):
  tokens = myreglexer.tokenize(stream)
  try:
    top = next(tokens)
    if not top[0] == 'LBRACE':
      print 'Unexpected character %r on line %d, Expected "["' % (top[1], top[2])
      sys.exit(1)
    else:
      S(tokens)
      try:
        top = next(tokens)
      except StopIteration:
        print 'Unexpected end of file on line %d, expected "]"' % top[2]
        sys.exit(1)

  except StopIteration:
    print "Empty set of tokens found"
    sys.exit(1)

def S(tokens):
  try:
    top = next(tokens)
    if top[0] == 'RBRACE':
      print "Error, expected an expression"
      sys.exit(1)
    else:
      pass
  except StopIteration:
    print "Invalid syntax, expected a expression"
    sys.exit(1)

def test(token1, tokens):
  try:
    token2 = next(tokens)
    print token1[0]
    print token2[0]
    test(token2, tokens)
  except StopIteration:
    pass

def main(argument):
  with open(argument, 'r') as f:
    contents = f.read()
  parser(contents)

if __name__ == "__main__":
  main(sys.argv[1])