#!/usr/bin/env python
from sys import *
from myreglexer import *
from getopt import *
from myparser import *
from tree import *
from semantic import *

contents = []

def main(argv):
  try:
    opts, args = getopt(argv, "h", ["help"])
  except GetoptError:
    usage()
    sys.exit(1)

  for opt, arg in opts:
    if opt in ("-h", "--help"):
      usage()
      sys.exit()

  
  for arg in args:
    try:
      with open(arg, 'r') as f:
        readin = f.read()
        tree = parser(readin)
        #tree.traverse_pre()
        #print temp
        semantics(tree)
        #temp = tree.build_stack_post()
        #for i in temp:
        #  print i.data[1]
        #tree.traverse_post()


    except IOError:
      print "File %s not found!" % arg
      sys.exit(1)

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