#!/usr/bin/env python
import sys
import collections
from tree import *

def semantic_check(values):
  if values[0].data[0] == 'BINOP':
    return check_binop(values)

  elif values[0].data[0] == 'UNOP':
    pass

'''
def check_binop(values):
  if (values[0].data[1] == 'and' or values[0].data[1] == 'not'):
    print values[0].data[1]
    values.pop(0)
    return check_bool(values)

  elif (values[0].data[1] == '+' or values[0].data[1] == '-' or
        values[0].data[1] == '*' or values[0].data[1] == '/' or
        values[0].data[1] == '%' or values[0].data[1] == '<' or
        values[0].data[1] == '<=' or values[0].data[1] == '>' or
        values[0].data[1] == '>=' or  values[0].data[1] == '='):
    print values[0].data[1]
    return check_math(values)

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
'''

def check_binop(values):
  if (values[0].data[1] == '+' or values[0].data[1] == '-' or
      values[0].data[1] == '/' or values[0].data[1] == '*' or
      values[0].data[1] == '%'):
    return binop_math(values)

  elif values[0].data[1] == 'and' or values[0].data[1] == 'or':
     return binop_bool(values)

def is_binop_math(values):
  if (values[0].data[1] == '+' or values[0].data[1] == '-' or
      values[0].data[1] == '/' or values[0].data[1] == '*' or
      values[0].data[1] == '%'):
    return binop_math(values)

  else:
    sem_error()

def is_binop_bool(values):
  if values[0].data[1] == 'and' or values[0].data[1] == 'or':
    return binop_bool(values)

  else:
    sem_error()

def binop_math(values):
  
  # first operand is int
  if values[1].data[0] == 'INTEGER':
    print values[1].data[1]

    # second operand is int
    if values[2].data[0] == 'INTEGER':
      print values[2].data[1]
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      return True

    # second operand is float
    elif values[2].data[0] == 'REAL':
      print values[2].data[1]
      values[1].data[1] += ' s>f'
      values[0].data[1] = 'f' + values[0].data[1]
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      return False

    else:
      sem_error()

  # first operand is float
  elif values[1].data[0] == 'REAL':
    print values[1].data[1]

    # second operand is float
    if values[2].data[0] == 'REAL':
      print values[2].data[1]
      values[0].data[1] = 'f' + values[0].data[1]
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      return False

    # second operand is int
    elif values[2].data[0] == 'INTEGER':
      print values[2].data[1]
      values[2].data[1] += ' s>f'
      values[0].data[1] = 'f' + values[0].data[1]
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      print 'deleting ' + str(values[0].data[1])
      values.pop(0)
      return False

    else:
      sem_error()

  # first operand is math binop
  elif values[1].data[0] == 'BINOP':
    print values[1].data[1]

    # int only binop
    temp_values = values[1:]
    if is_binop_math(temp_values):
      # this is a nasty hack because I don't truely understand list comp.
      del values[1:]
      for i in temp_values:
        values.append(i)
      # second operand is int
      if values[1].data[0] == 'INTEGER':
        print 'deleting ' + str(values[0].data[1])
        values.pop(0)
        print 'deleting ' + str(values[0].data[1])
        values.pop(0)
        return True

      # second operand is float
      elif values[1].data[0] == 'REAL':
        values[0].data[1] = 'f' + values[0].data[1]
        values[1].data[1] = 's>f ' + values[1].data[1]
        print 'deleting ' + str(values[0].data[1])
        values.pop(0)
        print 'deleting ' + str(values[0].data[1])
        values.pop(0)
        return False

      


  else:
    sem_error()



def check_unop(values):
  pass

def check_bool(values):
  # first operand is bool
  if values[0].data[0] == 'BOOL':
    print values[0].data[1]
    values.pop(0)

    # second operand is bool
    if values[0].data[0] == 'BOOL':
      print values[0].data[1]
      values.pop(0)
      return True

    # second operand is bool operator
    elif values[0].data[1] == 'and' or values[0].data[1] == 'or':
      print values[0].data[1]
      values.pop(0)
      return check_bool(values)

    else:
      sem_error()

  # first operand is bool operator
  elif values[0].data[1] == 'and' or values[0].data[1] == 'or':
    print values[0].data[1]
    values.pop(0)
    check_bool(values)

    # second operand is bool
    if values[0].data[0] == 'BOOL':
      print values[0].data[1]
      values.pop(0)
      return True

    # second operand is bool operator
    elif values[0].data[1] == 'and' or values[0].data[1] == 'or':
      print values[0].data[1]
      values.pop(0)
      return check_bool(values)

    else:
      sem_error()

  else:
    sem_error()

def check_or(values):
  pass

def check_math(values):
  # first operand is int
  if values[1].data[0] == 'INTEGER':
    print values[1].data[1]

    # second operand is int
    if values[2].data[0] == 'INTEGER':
      print values[2].data[1]
      return True

    elif values[2].data[0] == 'REAL':
      # second operand is float
      print values[2].data[1]
      values[1].data[1] = values[1].data[1] + ' s>f'
      values[0].data[1] = 'f' + values[0].data[1]
      return False

  elif values[1].data[0] == 'REAL':
    # first operand is float
    print values[1].data[1]

    if values[2].data[0] == 'REAL':
      print values[2].data[1]
      values.pop(0)
      values.pop(0)
      values.pop(0)
      return False



  else:
    sem_error()

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
  