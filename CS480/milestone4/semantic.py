#!/usr/bin/env python
import sys
import collections
from tree import *

OpTypeNone = -1
OpTypeFloat = 0
OpTypeInt = 1
OpTypeName = 2

if_number = 0

def semantics(root):
  stack = []
  parseTreeWithRootNode(root, stack)
  root.data = [' ', 'bye']

  print ' '.join(root.build_stack_post())

def parseTreeWithRootNode(node, stack):

  datatype = OpTypeNone

  for i in node.children:

    if (i.getTag() == 'BINOP' or i.getTag() == 'UNOP' or 
        i.getTag() == 'ASSIGN' or i.getTag() == 'REAL' or
        i.getTag() == 'INTEGER' or i.getTag() == 'BOOL' or
        i.getTag() == 'STRING' or i.getTag() == 'NAME'):
      datatype = parseOper(i, stack)

    elif i.getValue() == 'if':
      parseIf(i, stack)

    elif i.getValue() == 'stdout':
      parse_print(i, stack)

    else:
      parseTreeWithRootNode(i, stack)

  return datatype



def is_trig(node):
  if (node.getValue() == 'sin' or node.getValue() == 'cos' or
    node.getValue() == 'tan'):
    return True
  else:
    return False

def parseOper(node, stack):
  return _parseOper(node, stack)

def _parseOper(node, stack):

  if len(node.children) == 0:
    
    if node.getTag() == 'REAL':
      return OpTypeFloat
    
    elif node.getTag() == 'INTEGER':
      return OpTypeInt
    
    else:
      return OpTypeName

  # [:= name oper] and [binops oper oper]
  if node.getTag() == 'BINOP' or node.getTag() == 'ASSIGN':

    # Check if the production is [binops oper oper]
    if node.getTag() == 'BINOP':

      # [binops oper oper]
      rettype = None

      # Typecheck Oper 2
      oper2 = node.children[1]
      oper2type = _parseOper(oper2, stack)

      #Typecheck Oper 1
      oper1 = node.children[0]
      oper1type = _parseOper(oper1, stack)

      # compare the operands
      if not oper1type == oper2type:
        if oper1type == OpTypeFloat and oper2type == OpTypeInt:

          # Convert oper2 to float
          if ' s>f' in oper2.data[1]:
            pass
          else:
            oper2.data[1] += ' s>f'

        elif oper1type == OpTypeInt and oper2type == OpTypeFloat:

          # Convert oper1 to float
          oper1.data[1] += ' s>f'

        rettype = OpTypeFloat

      # Set return type if not already set
      if not rettype:

        # Need to check both in case one is a name
        if (oper1type == OpTypeFloat or oper2type == OpTypeFloat):
          rettype = OpTypeFloat

        else:
          rettype = OpTypeInt

      if rettype == OpTypeFloat:

        # Change binop to be floating point if necessary
        if (node.getValue() == '-' or node.getValue() == '+' or
            node.getValue() == '*' or node.getValue() == '/' or
            node.getValue() == '>' or node.getValue() == '<' or
            node.getValue() == '<=' or node.getValue() == '>=' or
            node.getValue() == 'mod' or node.getValue() == '**'):
          node.data[1] = 'f' + node.data[1]

      return rettype

    else:

      # [:= name oper]
      rettype = None

      # Typecheck the Oper
      oper2 = node.children[1]
      oper2type = _parseOper(oper2, stack)

      return oper2type

  # [unops oper1]
  if node.getTag() == 'UNOP':

    # Typecheck Oper 1
    oper1 = node.children[0]
    oper1type = _parseOper(oper1, stack)

    if node.getValue() == '-':
      oper1.data[1] = '-' + oper1.data[1]
      node.data[1] = ''

    if is_trig(node):
      if oper1type == OpTypeInt:
        oper1.data[1] += ' s>f '
      node.data[1] = 'f' + node.data[1]
      oper1type = OpTypeFloat

    return oper1type

# [if expr1 expr2]  or  [if expr1 expr2 expr3]
def parseIf(node, stack):
  global if_number

  # [if expr1 expr2]
  expr1 = node.children[0]
  expr2 = node.children[1]

  temp1 = expr1.getLeftMost()
  temp1.data[1] = ': if' + str(if_number) + ' ' + temp1.data[1]

  #temp2 = expr2.getLeftMost()
  expr1.data = [' ', ' ']
  expr1.data[1] = 'if ' + expr1.data[1]

 
  #parseTreeWithRootNode(expr1, stack)
  parseTreeWithRootNode(node, stack)

  #parseTreeWithRootNode(expr2, stack)
  parseTreeWithRootNode(node, stack)

  if len(node.children) == 3:
    expr3 = node.children[2]
    temp3 = expr3.getLeftMost()
    temp3.data[1] = 'else ' + temp3.data[1]
    parseTreeWithRootNode(expr3, stack)

  node.data[1] = 'endif ; ' + 'if' + str(if_number)

  if_number += 1

# [stdout oper]
def parse_print(node, stack):

  oper1 = node.children[0]

  oper1type = parseTreeWithRootNode(oper1, stack)

  if oper1type == OpTypeFloat:
    node.data[1] = 'f.'
  else:
    node.data[1] = '.'

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
