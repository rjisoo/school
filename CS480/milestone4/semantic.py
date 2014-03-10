#!/usr/bin/env python
import sys
import collections
from tree import *

def semantics(root):
  temp = root.build_stack_pre()
  semantic_check(temp)
  temp = root.build_stack_pre()

  for i in temp:
    # ** doesn't exist for ints, need to create a function
    if i.data[1] == '**':
      i.data[1] = ': ** 1 SWAP ?DUP IF 0 DO OVER * LOOP THEN NIP ; ' + '**'
      break

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
      values[0].data[1] == '**'):
    return binop_math(values)

  elif values[0].data[1] == 'and' or values[0].data[1] == 'or':
     return binop_bool(values)

def is_binop_math(values):
  if (values[0].data[1] == '+' or values[0].data[1] == '-' or
      values[0].data[1] == '/' or values[0].data[1] == '*' or
      values[0].data[1] == '**'):
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
      values.pop(0)
      values.pop(0)
      values.pop(0)
      return True

    elif values[2].data[0] == 'REAL':
      values[0].data[1] = 'f' + values[0].data[1]
      values[1].data[1] += ' s>f'
      values.pop(0)
      values.pop(0)
      values.pop(0)
      return False

    # 2nd operand is binop
    elif is_binop_math(values[2:]):

      # is for sure a math binop
      temp = values[2:]
      if binop_math(temp):
        # 2nd operand is int only binop
        del values[2:]
        for i in temp:
          values.append(i)
        values.pop()
        values.pop()
        return True

      else:
        # 2nd operand is binop containing float
        values[0].data[1] = 'f' + values[0].data[1]
        values[1].data[1] += ' s>f'
        values.pop(0)
        values.pop(0)
        return False


  # first operand is float
  elif values[1].data[0] == 'REAL':

    # 2nd operand is int
    if values[2].data[0] == 'INTEGER':
      values[0].data[1] = 'f' + values[0].data[1]
      values[2].data[1] += ' s>f'
      values.pop(0)
      values.pop(0)
      values.pop(0)
      return False

    # 2nd operand is float
    elif values[2].data[0] == 'REAL':
      values[0].data[1] = 'f' + values[0].data[1]
      values.pop(0)
      values.pop(0)
      values.pop(0)
      return False

    # 2nd operand is binop
    elif is_binop_math(values[2:]):

      # is for sure a math binop
      temp = values[2:]
      if binop_math(temp):
        # 2nd operand is int only binop
        del values[2:]
        for i in temp:
          values.append(i)
        values[0].data[1] = 's>f f' + values[0].data[1]
        values.pop()
        values.pop()
        return True

      else:
        # 2nd operand is binop containing float
        values[0].data[1] = 'f' + values[0].data[1]
        values.pop(0)
        values.pop(0)
        return False


  # math binop first operand
  elif is_binop_math(values[1:]):

    placeholder = values[1]

    # is for sure a math binop
    temp = values[1:]
    if binop_math(temp):

      # first operand is int only binop
      del values[1:]
      for i in temp:
        values.append(i)

      if values[1].data[0] == 'INTEGER':

        # 2nd operand is int
        values.pop(0)
        values.pop(0)
        return True

      elif values[1].data[0] == 'REAL':

        # 2nd operand is float
        values[0].data[1] = 'f' + values[0].data[1]
        values[1].data[1] = 's>f ' + values[1].data[1]
        values.pop(0)
        values.pop(0)
        return False

      elif values[1].data[0] == 'BINOP':

        # 2nd operand is binop
        if is_binop_math(values[1:]):

          # is for sure a math binop
          temp = values[1:]
          if binop_math(temp):

            # 2nd operand is int only binop
            del values[1:]
            for i in temp:
              values.append(i)

            values[0].data[1] = 'f' + values[0].data[1]
            values[1].data[1] += ' s>f'
            values.pop(0)
            return False
          else:

            # 2nd operand is float binop
            values[0].data[1] = 'f' + values[0].data[1]
            placeholder.data[1] += ' s>f'
            values.pop(0)
            return False


    else:
      # first operand is float binop
      del values[1:]
      for i in temp:
        values.append(i)

      if values[1].data[0] == 'INTEGER':

        # 2nd operand is int
        values[1].data[1] += ' s>f'
        values[0].data[1] = 'f' + values[0].data[1]
        values.pop(0)
        values.pop(0)
        return False

      elif values[1].data[0] == 'REAL':
        
        # 2nd operand is float
        values[0].data[1] = 'f' + values[0].data[1]
        values.pop(0)
        values.pop(0)
        return False

      elif values[1].data[0] == 'BINOP':

        # 2nd operand is binop
        if is_binop_math(values[1:]):

          # is for sure a math binop
          temp = values[1:]
          if binop_math(temp):

            # 2nd operand is int only binop
            del values[1:]
            for i in temp:
              values.append(i)

            values[0].data[1] = 's>f f' + values[0].data[1]
            values.pop(0)
            return False

          else:

            # 2nd operand is float binop
            values.pop(0)
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
      values.pop(0) # remove op
      values.pop(0) # remove 1st operand
      values.pop(0) # remove 2nd operand
      return True

    # 2nd operand is bool binop
    elif values[2].data[0] == 'BINOP':
      is_binop_bool(values[2:])
      temp = values[2:]
      binop_bool(temp)
      del values[2:]
      for i in temp:
        values.append(i)
      return True

    else:
      sem_error()

  # 1st opernad is bool binop
  elif values[1].data[0] == 'BINOP':
    is_binop_bool(values[1:])
    temp = values[1:]
    binop_bool(temp)
    del values[1:]
    for i in temp:
      values.append(i)

    # 2nd operand is bool
    if values[1].data[0] == 'BOOL':
      values.pop(0) # remove binop
      values.pop(0) # remove 2nd operand
      return True

    # 2nd operand is bool binop
    elif values[1].data[0] == 'BINOP':
      is_binop_bool(values[1:])
      temp = values[1:]
      binop_bool(temp)
      del values[1:]
      for i in temp:
        values.append(i)
      values.pop(0) # remove binop
      return True

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
