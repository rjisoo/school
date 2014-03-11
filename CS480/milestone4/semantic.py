#!/usr/bin/env python
import sys
import collections
from tree import *

def semantics(root):
  stack = ''
  temp = root.build_stack_pre()
  semantic_check(temp)
  temp = root.build_stack_pre()

  for i in temp:
    # ** doesn't exist for ints, need to create a function
    if i.data[1] == '**':
      i.data[1] = ': ** 1 SWAP ?DUP IF 0 DO OVER * LOOP THEN NIP ; ' + '**'
      break

  temp = root.build_stack_post()

  for i in temp:
    stack += (' ' +i.data[1])

  print stack

  root.traverse_post()

def semantic_check(values):
  while(1):
    try:
      if values[0].data[0] == 'BINOP':
        check_binop(values)

      elif values[0].data[0] == 'UNOP':
        pass
    except IndexError:
      break

def check_binop(values):
  if (values[0].data[1] == '+' or values[0].data[1] == '-' or
      values[0].data[1] == '/' or values[0].data[1] == '*' or
      values[0].data[1] == '**' or values[0].data[1] == 'mod'):
    return binop_math(values)

  elif values[0].data[1] == 'and' or values[0].data[1] == 'or':
     return binop_bool(values)

def is_binop_math(values):
  if (values[0].data[1] == '+' or values[0].data[1] == '-' or
      values[0].data[1] == '/' or values[0].data[1] == '*' or
      values[0].data[1] == '**' or values[0].data[1] == 'mod'):
    return True

  else:
    sem_error()

def is_binop_bool(values):
  if values[0].data[1] == 'and' or values[0].data[1] == 'or':
    return True

  else:
    sem_error()

def is_binop_bool_math(values):
  if (values[0].data[1] == '=' or values[0].data[1] == '<' or
      values[0].data[1] == '>' or values[0].data[1] == '<=' or
      values[0].data[1] == '>=' or values[0].data[1] == '<>'):
    return True

  else:
    sem_error()

def binop_math(values):
  
  # first operand is int
  if values[1].data[0] == 'INTEGER':
    
    # 2nd operand is int
    if values[2].data[0] == 'INTEGER':
      values.pop(0) # remove binop
      values.pop(0) # remove 1st operand
      values.pop(0) # remove 2nd operand
      return True

    elif values[2].data[0] == 'REAL':
      values[1].data[1] += ' s>f'
      values[0].data[1] = 'f' + values[0].data[1]
      values.pop(0) # remove binop
      values.pop(0) # remove 1st operand
      values.pop(0) # remove 2nd operand
      return False

    else:
      sem_error()

  # first operand is float
  elif values[1].data[0] == 'REAL':
    values[0].data[1] = 'f' + values[0].data[1]

    # 2nd operand is int
    if values[2].data[0] == 'INTEGER':
      values[2].data[1] += ' s>f'
      values.pop(0) # remove binop
      values.pop(0) # remove 1st operand
      values.pop(0) # remove 2nd operand
      return False

    # 2nd operand is float
    elif values[2].data[0] == 'REAL':
      values.pop(0) # remove binop
      values.pop(0) # remove 1st operand
      values.pop(0) # remove 2nd operand
      return False

    else:
      sem_error()

  # first operand is binop
  elif values[1].data[0] == 'BINOP':
    is_binop_math(values[1:])

    # it is a math binop
    temp = values[1:]
    result = binop_math(temp)
    del values[1:]
    for i in temp: # restore values stack
      values.append(i)

    # 1st operand int only binop
    if result: 

      # 2nd operand int
      if values[1].data[0] == 'INTEGER':
        values.pop(0) # remove binop
        values.pop(0) # remove 2nd int operand
        return True

      # 2nd operand float
      elif values[1].data[0] == 'REAL':
        values[1].data[1] = 's>f ' + values[1].data[1]
        values[0].data[1] = 'f' + values[0].data[1]
        values.pop(0) # remove binop
        values.pop(0) # remove 2nd float operand
        return False

      # 2nd operand is binop
      elif values[1].data[0] == 'BINOP':
        is_binop_math(values[1:])
        # it is a math binop
        temp = values[1:]
        result2 = binop_math(temp)
        del values[1:]
        for i in temp: # restore values stack
          values.append(i)

        # 2nd operand int only binop
        if result2:
          values.pop(0) # remove binop
          return True

        # 2nd binop float binop
        else:
          values[0].children[0].data[1] += ' s>f'
          values[0].data[1] = 'f' + values[0].data[1]
          values.pop(0) # remove binop
          return False

    # 1st operand float binop
    else:
      values[0].data[1] = 'f' + values[0].data[1]

      # 2nd operand is int
      if values[1].data[0] == 'INTEGER':
        values[1].data[1] += ' s>f'
        values.pop(0) # remove binop
        values.pop(0) # remove 2nd operand
        return False

      # 2nd operand is float
      elif values[1].data[0] == 'REAL':
        values.pop(0) # remove binop
        values.pop(0) # remove 2nd operand
        return False

      # 2nd operand binop
      elif values[1].data[0] == 'BINOP':
        is_binop_math(values[1:])
        # it is a math binop
        temp = values[1:]
        result2 = binop_math(temp)
        del values[1:]
        for i in temp: # restore values stack
          values.append(i)

        # 2nd operand is int only binop
        if result2:
          values[0].data[1] = ' s>f ' + values[0].data[1]
          values.pop(0) # remove binop
          return False

        # 2nd operand is float binop
        else:
          values.pop(0) # remove binop
          return False
  else:
    sem_error()

def check_unop(values):
  pass

def binop_bool(values):
  
  # first operand is bool
  if values[1].data[0] == 'BOOL':
    
    # 2nd operand is bool
    if values[2].data[0] == 'BOOL':
      values.pop(0) # remove binop
      values.pop(0) # remove 1st operand
      values.pop(0) # remove 2nd operand
      return True

    # 2nd operand is binop
    elif values[2].data[0] == 'BINOP':
      is_binop_bool(values[2:])

      # it is a bool binop
      temp = values[1:]
      binop_bool(temp)
      del values[1:]
      for i in temp: # restore values stack
        values.append(i)
      values.pop(0) # remove binop
      values.pop(0) # remove 1st operand
      return




  # first operand is binop
  elif values[1].data[0] == 'BINOP':
    pass

  else:
    sem_error()
  

def binop_bool_math(values):
  pass

def check_or(values):
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
  #[[+ 2.3 [+ 3.4 6]]]
