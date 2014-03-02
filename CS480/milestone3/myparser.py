#!/usr/bin/env python
import collections
import myreglexer
import sys
import tree

index = 0
ahead1 = 1
ahead2 = 2

stack = []

def parser(stream):
  global stack, index
  tokens = list(myreglexer.tokenize(stream))
  T(tokens)
  print stack
  print index

def T(tokens): # T -> [S]
  global index, stack

  print "In T"

  if tokens[index][0] == "LBRACE":
    
    stack.append(tokens[index][1])
    nextToken()
    
    S(tokens)

    stack.append(tokens[index][1])
    nextToken()
    if not tokens[index][0] == "RBRACE":
      error(tokens[index])

    stack.append(tokens[index][1])
    nextToken()

    return not None
  else:
    error(tokens[index][2], tokens[index][3])

def S(tokens): # S -> expr S_ | []S_ | [S]S_
  global index, ahead1, stack

  print "In S"

  if (tokens[ahead1][0] == "BINOP" or
      tokens[ahead1][0] == "UNOP" or
      tokens[ahead1][0] == "MINUS" or
      tokens[ahead1][0] == "NAME" or
      tokens[ahead1][0] == "BOOL" or
      tokens[ahead1][0] == "ASSIGN" or
      tokens[ahead1][0] == "STATEMENT" or
      tokens[ahead1][0] == "REAL" or
      tokens[ahead1][0] == "INTEGER" or
      tokens[ahead1][0] == "STRING"):
    # S -> expr S_
    expr(tokens)
    if not tokens[ahead1][0] == "RBRACE":
      stack.append(tokens[index][1])
      nextToken()
      S_(tokens)

  elif tokens[index][0] == "LBRACE" and tokens[ahead1][0] == "RBRACE":
    # S -> []S_
    stack.append(tokens[index][1])
    nextToken()
    if not tokens[ahead1][0] == "RBRACE":
      stack.append(tokens[index][1])
      nextToken()
      S_(tokens)

  elif tokens[index][0] == "LBRACE":
    stack.append(tokens[index][1])
    nextToken()
    S(tokens)
    stack.append(tokens[index][1])
    nextToken()

    if not tokens[index][0] == "RBRACE":
      error(tokens[index])

    if not tokens[ahead1][0] == "RBRACE":
      stack.append(tokens[index][1])
      nextToken()
      S_(tokens)

  else:
    return None

  return not None

def S_(tokens): # S_ -> SS_ | empty
  global index, ahead1, stack

  print "In S_"

  resultS = S(tokens)

  if resultS:
    if tokens[ahead1][0] == "RBRACE":
      return not None

    stack.append(tokens[index][1])
    nextToken()

    resultS_ = S_(tokens)
    if resultS_:
      pass

    return not None

  else:  
    return None


def expr(tokens): # expr -> oper | stmts
  global index, ahead1

  print "In expr"

  if tokens[ahead1][0] == "STATEMENT":
    stmts(tokens)

  elif (tokens[ahead1][0] == "BINOP" or
        tokens[ahead1][0] == "UNOP" or
        tokens[ahead1][0] == "MINUS" or
        tokens[ahead1][0] == "NAME" or
        tokens[ahead1][0] == "BOOL" or
        tokens[ahead1][0] == "ASSIGN" or
        tokens[ahead1][0] == "REAL" or
        tokens[ahead1][0] == "INTEGER" or
        tokens[ahead1][0] == "STRING"):
    oper(tokens)

  else:
    error(tokens[index])
  
  return not None

def oper(tokens): # oper -> [:= name oper] | [binops oper oper] | [unops oper] | constants | name
  global index, ahead1, stack

  print "In oper"

  if (tokens[index][0] == "REAL" or
      tokens[index][0] == "INTEGER" or
      tokens[index][0] == "STRING" or
      tokens[index][0] == "BOOL" or
      tokens[index][0] == "NAME"):
    return not None

  elif tokens[index][0] == "LBRACE":
    stack.append(tokens[index][1])
    nextToken()

    if tokens[index][0] == "BINOP":
      # Production: [binops oper oper]
      stack.append(tokens[index][1])
      nextToken()
      oper(tokens)

      stack.append(tokens[index][1])
      nextToken()
      oper(tokens)

    stack.append(tokens[index][1])
    nextToken()
    if not tokens[index][0] == "RBRACE":
      error(tokens[index])

  else:
    error(tokens[index])


  return not None

def stmts(tokens): # stmts -> ifstmts | whilestmts | letstmts | printsmts
  global index
  
  return None

def ifstmts(tokens): # ifstmts -> [if expr expr expr] | [if expr expr]
  global index

  return None

def whilestmts(tokens): # whilestmts -> [while expr exprlist]
  global index

  return None

def letstmts(tokens): # letstmts -> [let [varlist]]
  global index

  return None

def varlist(tokens): # varlist -> [name type] | [name type] varlist
  global index

  return None

def printstmts(tokens): # printstmts -> [stdout oper]
  global index

  return None

def exprlist(tokens): # exprlist -> expr | expr exprlist
  global index

  return None

def nextToken():
  global index
  global ahead1
  global ahead2

  index += 1
  ahead1 += 1
  ahead2 += 1

def error(token):
  print "Invalid input! Line: %s, colunm: %s" % (token[2], token[3])
  sys.exit(1)

def main(argument):
  with open(argument, 'r') as f:
    contents = f.read()
  parser(contents)

if __name__ == "__main__":
  main(sys.argv[1])
