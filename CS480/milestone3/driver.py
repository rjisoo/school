#!/usr/bin/env python
import sys
import myreglexer

def main(argument):
  lexemes = []
  x = 1

  with open(argument, 'r') as f:
    contents = f.read()
    
  for token in myreglexer.tokenize(contents):
    lexemes.append(token)

  for thing in lexemes:
    print thing


if __name__ == "__main__":
  main(sys.argv[1])