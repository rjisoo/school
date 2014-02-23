#!/usr/bin/env python
import sys
import myreglexer
import getopt
#import myparser

contents = []

def main(argv):
  lexemes = []
  x = 1

  try:
    opts, args = getopt.getopt(argv, "h", ["help"])
  except getopt.GetoptError:
    usage()
    sys.exit(1)

  for opt, arg in opts:
    if opt in ("-h", "--help"):
      usage()
      sys.exit()

  
  for arg in args:
    try:
      with open(arg, 'r') as f:
        contents.append(f.read())

    except IOError:
      print "File %s not found!" % arg
      sys.exit(1)

  tokens = myreglexer.tokenize("".join(contents))

  for token in tokens:
    print token
  #with open(argument, 'r') as f:
  #  contents = f.read()

  #myparser.parse(contents)

def no_args():
  for line in sys.stdin:
    contents.append(line)


def usage():
  print "Usage: driver.py [-h] infile1 infile2 infile3 ..."
  print "Or just take intput from stdin"

if __name__ == "__main__":
  if len(sys.argv) < 2:
    no_args()
    #usage()
    #sys.exit(1)
  main(sys.argv[1:])