#!/usr/bin/env python
import sys
import collections
from tree import *

def semantic_check(values):
  if values[0].data[0] == 'BINOP':
    return check_binop(values)

def check_binop(values):
  if (values[0].data[1] == 'and' or values[0].data[1] == 'not'):
    print values[0].data[1]
    return check_bool(values[1:])

  elif values[0].data[1] == '+':
    return check_plus(values)

  elif values[0].data[1] == '-':
    return check_minus(values)

  elif values[0].data[1] == '*':
    return check_mult(values)

  elif values[0].data[1] == '/':
    return check_div(values)

  elif values[0].data[1] == '%':
    return check_mod(values)

  elif values[0].data[1] == '<' or values[0].data[1] == '<=':
    return check_lt(values)

  elif values[0].data[1] ==  '>' or values[0].data[1] == '>=':
    return check_gt(values)

  elif values[0].data[1] == '=':
    return check_eq(values)

  elif values[0].data[1] == '!=':
    return check_noteq(values)

  else:
    sem_error()

def check_bool(values):
  # first operand is bool
  if values[0].data[0] == 'BOOL':
    print values[0].data[0]

    # second operand is bool
    if values[1].data[0] == 'BOOL':
      print values[1].data[0]
      return True

    # second operand is bool operator
    elif values[1].data[1] == 'and' or values[1].data[1] == 'or':
      print values[1].data[1]
      return check_bool(values[2:])

    else:
      sem_error()

  else:
    sem_error()

def check_or(values):
  if values[1].data[0] == 'BOOL':
    if values[2].data[0] == 'BOOL':
      return True

def check_not(values):
  pass

def check_plus(values):
  pass

def check_minus(values):
  pass

def check_negate(values):
  pass

def check_mult(values):
  pass

def check_div(values):
  pass

def check_mod(values):
  pass

def check_lt(values):
  pass

def check_gt(values):
  pass

def check_eq(values):
  pass

def check_noteq(values):
  pass


def sem_error():
  print 'Semantic error!'
  sys.exit(1)

if __name__ == "__main__":
  Token = collections.namedtuple('Token', ['typ', 'value', 'line', 'column'])
  token1 = Token('BINOP', '+', 1, 5-0)
  token2 = Token('BINOP', '+', 1, 5-0)
  token3 = Token('INTEGER', '2', 1, 5-0)
  token4 = Token('INTEGER', '3', 1, 5-0)
  token5 = Token('INTEGER', '3', 1, 5-0)
  n1 = Node(token1)
  n2 = Node(token2)
  n3 = Node(token3)
  n4 = Node(token4) 
  n5 = Node(token5)
  p = Node()
  p.addChild(n1)
  n1.addChild(n2)
  n2.addChild(n3)
  n2.addChild(n4)
  n1.addChild(n5)
  #p.traverse_pre()

  t = p.build_stack()

  print semantic_check(t)
  