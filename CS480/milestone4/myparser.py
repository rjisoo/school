#!/usr/bin/env python
import collections
import myreglexer
import sys
from tree import *

index = 0
ahead1 = 1

stack = []

def parser(stream):
  global stack, index, ahead1
  tokens = list(myreglexer.tokenize(stream))
  index = 0
  ahead1 = 1
  root = Node()
  root.addChild(T(tokens))

  root.traverse()

def T(tokens): # T -> [S]
  global index, stack

  temp = Node()

  if tokens[index][0] == "LBRACE":
    temp.addChild(Node(tokens[index][1]))
    
    nextToken()
    temp.addChild(S(tokens))
    
    nextToken()
    if not tokens[index][0] == "RBRACE":
      error(tokens[index], ']')

    temp.addChild(Node(tokens[index][1]))

    return temp
  else:
    error(tokens[index], '[')

def S(tokens): # S -> expr S_ | []S_ | [S]S_
  global index, ahead1, stack

  temp = Node()

  if (tokens[ahead1][0] == "BINOP" or tokens[ahead1][0] == "UNOP" or
      tokens[ahead1][0] == "MINUS" or tokens[ahead1][0] == "ASSIGN" or
      tokens[ahead1][0] == "STATEMENT" or tokens[index][0] == "NAME" or 
      tokens[index][0] == "BOOL" or tokens[index][0] == "REAL" or
      tokens[index][0] == "INTEGER" or tokens[index][0] == "STRING"):
    # S -> expr S_
    temp.addChild(expr(tokens))

    if not tokens[ahead1][0] == "RBRACE":
      nextToken()
      temp.addChild(S_(tokens))

  elif tokens[index][0] == "LBRACE" and tokens[ahead1][0] == "RBRACE":
    # S -> []S_
    temp.addChild(Node(tokens[index][1])) # [
    nextToken()
    temp.addChild(Node(tokens[index][1])) # ]
    if not tokens[ahead1][0] == "RBRACE":
      nextToken()
      temp.addChild(S_(tokens)) # S_

  elif tokens[index][0] == "LBRACE":
    # S -> [S]S_
    temp.addChild(Node(tokens[index][1])) # [
    nextToken()
    temp.addChild(S(tokens)) # S
    nextToken()

    if not tokens[index][0] == "RBRACE":
      error(tokens[index], ']')

    temp.addChild(Node(tokens[index][1])) # ]

    if not tokens[ahead1][0] == "RBRACE":
      nextToken()
      temp.addChild(S_(tokens)) # S_

  else:
    return None

  return temp

def S_(tokens): # S_ -> SS_ | empty
  global index, ahead1, stack

  temp = Node()

  resultS = S(tokens)

  if resultS:
    temp.addChild(resultS) # S
    # Handle empty case
    if tokens[ahead1][0] == "RBRACE":
      return temp

    nextToken()

    resultS_ = S_(tokens)
    if resultS_:
      temp.addChild(resultS_) # S_

    return temp

  else:  
    return None

  return temp


def expr(tokens): # expr -> oper | stmts
  global index, ahead1

  temp = Node()

  if tokens[ahead1][0] == "STATEMENT":
    temp.addChild(stmts(tokens))
    return temp

  elif (tokens[ahead1][0] == "BINOP" or tokens[ahead1][0] == "UNOP" or
        tokens[ahead1][0] == "MINUS" or tokens[ahead1][0] == "ASSIGN" or
        tokens[index][0] == "NAME" or tokens[index][0] == "BOOL" or
        tokens[index][0] == "REAL" or tokens[index][0] == "INTEGER" or
        tokens[index][0] == "STRING"):
    temp.addChild(oper(tokens))
    return temp

  else:
    error(tokens[index], "statement or oper")
  
  return temp

def oper(tokens): # oper -> [:= name oper] | [binops oper oper] | [unops oper] | constants | name
  global index, ahead1, stack

  temp = Node()

  if (tokens[index][0] == "REAL" or
      tokens[index][0] == "INTEGER" or
      tokens[index][0] == "STRING" or
      tokens[index][0] == "BOOL" or
      tokens[index][0] == "NAME"):
    temp.addChild(Node(tokens[index][1]))
    return temp

  elif tokens[index][0] == "LBRACE":
    temp.addChild(Node(tokens[index][1]))
    nextToken()

    # special case for '-' sign, because it can be binop OR unop
    if tokens[index][0] == "MINUS":
      temp.addChild(Node(tokens[index][1]))
      nextToken()
      temp.addChild(oper(tokens))

      if not tokens[ahead1][0] == "RBRACE":
        #stack.append(tokens[index][1])
        nextToken()
        temp.addChild(oper(tokens))

      #stack.append(tokens[index][1])
      nextToken()
      if not tokens[index][0] == "RBRACE":
        error(tokens[index], ']')

      temp.addChild(Node(tokens[index][1]))
      return temp

      

    if tokens[index][0] == "BINOP":
      # Production: [binops oper oper]
      stack.append(tokens[index][1])
      nextToken()
      oper(tokens)

      stack.append(tokens[index][1])
      nextToken()
      oper(tokens)

    elif tokens[index][0] == "UNOP":
      # Production: [unops oper]
      stack.append(tokens[index][1])
      nextToken()
      oper(tokens)

    elif tokens[index][0] == "ASSIGN":
      # Production: [:= name oper]
      stack.append(tokens[index][1])
      nextToken()

      if not tokens[index][0] == "NAME":
        error(tokens[index], 'NAME')

      stack.append(tokens[index][1])
      nextToken()
      oper(tokens)

    stack.append(tokens[index][1])
    nextToken()
    if not tokens[index][0] == "RBRACE":
      error(tokens[index], ']')

  else:
    error(tokens[index], '[')


  return not None

def stmts(tokens): # stmts -> ifstmts | whilestmts | letstmts | printsmts
  global index, ahead1

  if tokens[ahead1][1] == "if":
    ifstmts(tokens)

  elif tokens[ahead1][1] == "while":
    whilestmts(tokens)

  elif tokens[ahead1][1] == "let":
    letstmts(tokens)

  elif tokens[ahead1][1] == "stdout":
    printstmts(tokens)

  else:
    error(tokens[index], 'STATEMENT')
  
  return not None

def ifstmts(tokens): # ifstmts -> [if expr expr expr] | [if expr expr]
  global index, ahead1, stack

  if tokens[index][0] == "LBRACE":
    stack.append(tokens[index][1])
    nextToken()

    if not tokens[index][1] == "if":
      error(tokens[index], 'if')
    stack.append(tokens[index][1])
    nextToken()

    expr(tokens)

    stack.append(tokens[index][1])
    nextToken()
    expr(tokens)

    if tokens[ahead1][0] == "LBRACE":
      stack.append(tokens[index][1])
      nextToken()
      expr(tokens)

    stack.append(tokens[index][1])
    nextToken()

    if not tokens[index][0] == "RBRACE":
      error(tokens[index], ']')

    return not None

  else:
    error(tokens[index], '[')

  return None

def whilestmts(tokens): # whilestmts -> [while expr exprlist]
  global index, stack

  if tokens[index][0] == "LBRACE":
    stack.append(tokens[index][1])
    nextToken()

    if not tokens[index][1] == "while":
      error(tokens[index], 'while')

    stack.append(tokens[index][1])
    nextToken()
    expr(tokens)

    stack.append(tokens[index][1])
    nextToken()
    exprlist(tokens)

    stack.append(tokens[index][1])
    nextToken()

    if not tokens[index][0] == "RBRACE":
      error(tokens[index], ']')

    return not None
  else:
    error(tokens[index], '[')

  return None

def letstmts(tokens): # letstmts -> [let [varlist]]
  global index, stack

  if tokens[index][0] == "LBRACE":
    stack.append(tokens[index][1])
    nextToken()
    if not tokens[index][1] == "let":
      error(tokens[index], 'let')

    stack.append(tokens[index][1])
    nextToken()

    if not tokens[index][0] == "LBRACE":
      error(tokens[index], '[')

    stack.append(tokens[index][1])
    nextToken()
    varlist(tokens)

    stack.append(tokens[index][1])
    nextToken()

    if not tokens[index][0] == "RBRACE":
      error(tokens[index], ']')

    stack.append(tokens[index][1])
    nextToken()

    if not tokens[index][0] == "RBRACE":
      error(tokens[index], ']')

    return not None
  else:
    error(tokens[index], '[')

  return None

def varlist(tokens): # varlist -> [name type] | [name type] varlist
  global index, ahead1, stack

  if tokens[index][0] == "LBRACE":
    stack.append(tokens[index][1])
    nextToken()

    if not tokens[index][0] == "NAME":
      error(tokens[index], 'NAME')

    stack.append(tokens[index][1])
    nextToken()
    if not tokens[index][0] == "TYPES":
      error(tokens[index], 'TYPES')

    stack.append(tokens[index][1])
    nextToken()
    if not tokens[index][0] == "RBRACE":
      error(tokens[index], ']')

    # Use the lookahead to determine if there's another varlist
    if tokens[ahead1][0] == "LBRACE":
      stack.append(tokens[index][1])
      nextToken()
      varlist(tokens)

    return not None
  else:
    error(tokens[index], '[')

  return None

def printstmts(tokens): # printstmts -> [stdout oper]
  global index, stack

  if tokens[index][0] == "LBRACE":
    stack.append(tokens[index][1])
    nextToken()
    if not tokens[index][1] == "stdout":
      error(tokens[index], 'stdout')

    stack.append(tokens[index][1])
    nextToken()
    oper(tokens)

    stack.append(tokens[index][1])
    nextToken()
    if not tokens[index][0] == "RBRACE":
      error(tokens[index], ']')

    return not None

  else:
    error(tokens[index], '[')

  return None

def exprlist(tokens): # exprlist -> expr | expr exprlist
  global index, ahead1, stack

  expr(tokens)

  if not tokens[ahead1][0] == "RBRACE":
    stack.append(tokens[index][1])
    nextToken()
    exprlist(tokens)

  return not None

def nextToken():
  global index
  global ahead1

  index += 1
  ahead1 += 1

def error(token, expected):
  print 'Invalid input: "%s"! Line: %s, colunm: %s' % (token[1], token[2], token[3])
  print 'Expecting: %s' % expected
  sys.exit(1)

def main(argument):
  with open(argument, 'r') as f:
    contents = f.read()
  parser(contents)

if __name__ == "__main__":
  main(sys.argv[1])
