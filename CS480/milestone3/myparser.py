#!/usr/bin/env python
import collections
import myreglexer
import sys
import tree

index = 0
ahead1 = 1
ahead2 = 2

def parser(stream):
  global index
  tokens = list(myreglexer.tokenize(stream))
  T(tokens)

def T(tokens): # T -> [S]
  global index
  global ahead1

  if (tokens[ahead1][0] == "BINOP" or
      tokens[ahead1][0] == "UNOP" or
      tokens[ahead1][0] == "NAME" or
      tokens[ahead1][0] == "REAL" or
      tokens[ahead1][0] == "INTEGER" or
      tokens[ahead1][0] == "STRING" or
      tokens[ahead1][0] == "BOOL" or
      tokens[ahead1][0] == "ASSIGN" or
      tokens[ahead1][0] == "STATEMENT"):
    # S -> expr S_
    nextToken()
    S_(tokens)

  # [
  if tokens[index][0] == "LBRACE":

    # S
    nextToken()
    S(tokens)

    # ]
    nextToken()
    if not tokens[index][0] == "RBRACE":
      error()
    nextToken()
    return
  else:
    error()



def S(tokens): # S -> expr S_ | []S_ | [S]S_
  global index
  global ahead1
  
  if tokens[index][0] == "LBRACE" and tokens[ahead1][0] == "RBRACE":
    # S -> []S_
    nextToken()
    S_(tokens)

  elif tokens[index][0] == "LBRACE":
    # S -> [S]S_
    nextToken()
    S(tokens)
    nextToken()
    if not tokens[index][0] == "RBRACE":
      error()

    S_(tokens)
    nextToken()

  else:
    return

def S_(tokens): # S_ -> SS_ | empty
  global index
  pass

def expr(tokens): # expr -> oper | stmts
  global index
  pass

def oper(tokens): # oper -> [:= name oper] | [binops oper oper] | [unops oper] | constants | name
  global index
  pass

def stmts(tokens): # stmts -> ifstmts | whilestmts | letstmts | printsmts
  global index
  pass

def ifstmts(tokens): # ifstmts -> [if expr expr expr] | [if expr expr]
  global index

  pass

def whilestmts(tokens): # whilestmts -> [while expr exprlist]
  global index
  pass

def letstmts(tokens): # letstmts -> [let [varlist]]
  global index
  pass

def varlist(tokens): # varlist -> [name type] | [name type] varlist
  global index
  pass

def printstmts(tokens): # printstmts -> [stdout oper]
  global index
  pass

def exprlist(tokens): # exprlist -> expr | expr exprlist
  global index
  pass

def nextToken():
  global index
  global ahead1
  global ahead2

  index += 1
  ahead1 += 1
  ahead2 += 1

def error():
  print "Invalid input!"
  sys.exit(1)

def main(argument):
  with open(argument, 'r') as f:
    contents = f.read()
  parser(contents)

if __name__ == "__main__":
  main(sys.argv[1])
