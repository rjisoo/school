#!/usr/bin/env python
import collections
from myreglexer import *
import sys
from tree import *

def parser(stream):
  tokens = list(tokenize(stream))
  root = Node()
  root.addChild(T(tokens))
  return root

def T(tokens): # T -> [S]
  temp = Node()

  if tokens[0][0] == "LBRACE":
    
    nextToken(tokens)
    temp.addChild(S(tokens))
    
    nextToken(tokens)
    if not tokens[0][0] == "RBRACE":
      error(tokens[0], ']', 'T')

    return temp
  else:
    error(tokens[0], '[', 'T')

def S(tokens): # S -> expr S_ | []S_ | [S]S_
  temp = Node()

  if (tokens[1][0] == "BINOP" or tokens[1][0] == "UNOP" or
      tokens[1][0] == "MINUS" or tokens[1][0] == "ASSIGN" or
      tokens[1][0] == "STATEMENT" or tokens[0][0] == "NAME" or 
      tokens[0][0] == "BOOL" or tokens[0][0] == "REAL" or
      tokens[0][0] == "INTEGER" or tokens[0][0] == "STRING"):
    # S -> expr S_
    temp.addChild(expr(tokens))

    if not tokens[1][0] == "RBRACE":
      nextToken(tokens)
      temp.addChild(S_(tokens))

  elif tokens[0][0] == "LBRACE" and tokens[1][0] == "RBRACE":
    # S -> []S_
    # [
    nextToken(tokens)
    # ]
    if not tokens[1][0] == "RBRACE":
      nextToken(tokens)
      temp.addChild(S_(tokens)) # S_

  elif tokens[0][0] == "LBRACE":
    # S -> [S]S_
    # [
    nextToken(tokens)
    temp.addChild(S(tokens)) # S
    nextToken(tokens)

    if not tokens[0][0] == "RBRACE":
      error(tokens[0], ']', 'S')

    # ]

    if not tokens[1][0] == "RBRACE":
      nextToken(tokens)
      temp.addChild(S_(tokens)) # S_

  else:
    return None

  return temp

def S_(tokens): # S_ -> SS_ | empty
  temp = Node()

  resultS = S(tokens)

  if resultS:
    temp.addChild(resultS) # S
    # Handle empty case
    if tokens[1][0] == "RBRACE":
      return temp

    nextToken(tokens)

    resultS_ = S_(tokens)
    if resultS_:
      temp.addChild(resultS_) # S_

    return temp

  else:  
    return None

  return temp


def expr(tokens): # expr -> oper | stmts
  temp = Node()

  if tokens[1][0] == "STATEMENT":
    temp.addChild(stmts(tokens))
    return temp

  elif (tokens[1][0] == "BINOP" or tokens[1][0] == "UNOP" or
        tokens[1][0] == "MINUS" or tokens[1][0] == "ASSIGN" or
        tokens[0][0] == "NAME" or tokens[0][0] == "BOOL" or
        tokens[0][0] == "REAL" or tokens[0][0] == "INTEGER" or
        tokens[0][0] == "STRING"):
    temp.addChild(oper(tokens))
    return temp

  else:
    error(tokens[0], "statement or oper", 'expr')
  
  return temp

def oper(tokens): 
# oper -> [:= name oper] | [binops oper oper] | [unops oper] | constants | name
  temp = Node()
  Token = collections.namedtuple('Token', ['typ', 'value', 'line', 'column'])

  if (tokens[0][0] == "REAL" or
      tokens[0][0] == "INTEGER" or
      tokens[0][0] == "STRING" or
      tokens[0][0] == "BOOL" or
      tokens[0][0] == "NAME"):
    temp.setData([tokens[0][0], tokens[0][1]])
    return temp

  elif tokens[0][0] == "LBRACE":

    nextToken(tokens)

    # special case for '-' sign, because it can be binop OR unop
    if tokens[0][0] == "MINUS":
      # Production: [binops oper oper] OR [unops oper]
      temptok1 = ['BINOP', tokens[0][1]]
      temptok2 = ['UNOP', tokens[0][1]]
      #temp.setData(tokens[0])
      
      # oper
      nextToken(tokens)
      temp.addChild(oper(tokens))

      if not tokens[1][0] == "RBRACE":
        # oper ([binops oper oper] production
        nextToken(tokens)
        temp.addChild(oper(tokens))
        temp.setData(temptok1)
      else:
        temp.setData(temptok2)

      nextToken(tokens)
      if not tokens[0][0] == "RBRACE":
        error(tokens[0], ']', 'oper')

      return temp


    if tokens[0][0] == "BINOP":
      # Production: [binops oper oper]
      temp.setData([tokens[0][0], tokens[0][1]])

      # oper
      nextToken(tokens)
      temp.addChild(oper(tokens))

      # oper
      nextToken(tokens)
      temp.addChild(oper(tokens))

    elif tokens[0][0] == "UNOP":
      # Production: [unops oper]
      temp.setData(tokens[0])
      
      # oper
      nextToken(tokens)
      temp.addChild(oper(tokens))

    elif tokens[0][0] == "ASSIGN":
      # Production: [:= name oper]
      temp.setData([tokens[0][0], tokens[0][1]])

      # name
      nextToken(tokens)
      if not tokens[0][0] == "NAME":
        error(tokens[0], 'NAME', 'oper')
      temp.addChild(Node([tokens[0][0], tokens[0][1]]))
      
      # oper
      nextToken(tokens)
      temp.addChild(oper(tokens))
    
    else:
      error(tokens[0], "oper")

    nextToken(tokens)
    if not tokens[0][0] == "RBRACE":
      error(tokens[0], ']', 'oper')

    return temp

  else:
    error(tokens[0], '[', oper)


  return temp

def stmts(tokens): # stmts -> ifstmts | whilestmts | letstmts | printsmts
  temp = Node()

  if tokens[1][1] == "if":
    temp.addChild(ifstmts(tokens))

  elif tokens[1][1] == "while":
    temp.addChild(whilestmts(tokens))

  elif tokens[1][1] == "let":
    temp.addChild(letstmts(tokens))

  elif tokens[1][1] == "stdout":
    temp.addChild(printstmts(tokens))

  else:
    error(tokens[0], 'STATEMENT', 'oper')
  
  return temp

def ifstmts(tokens): # ifstmts -> [if expr expr expr] | [if expr expr]
  temp = Node()

  if tokens[0][0] == "LBRACE":

    nextToken(tokens)
    if not tokens[0][1] == "if":
      error(tokens[0], 'if', 'ifstmt')
    temp.setData([tokens[0][0], tokens[0][1]])

    # expr
    nextToken(tokens)
    temp.addChild(expr(tokens))

    # expr
    nextToken(tokens)
    temp.addChild(expr(tokens))

    # Use lookahead to check if there == a third expression
    if tokens[1][0] == "LBRACE":
      nextToken(tokens)
      temp.addChild(expr(tokens))

    # Fin==h both productions
    nextToken(tokens)
    if not tokens[0][0] == "RBRACE":
      error(tokens[0], ']', 'ifstmt')
    return temp

  else:
    error(tokens[0], '[', 'ifstmt')

  return temp

def whilestmts(tokens): # whilestmts -> [while expr exprlist]
  temp = Node()

  if tokens[0][0] == "LBRACE":

    # while
    nextToken(tokens)
    if not tokens[0][1] == "while":
      error(tokens[0], 'while', 'whilestmt')
    temp.setData([tokens[0][0], tokens[0][1]])
    
    # expr
    nextToken(tokens)
    temp.addChild(expr(tokens))

    # exprlist
    nextToken(tokens)
    temp.addChild(exprlist(tokens))

    nextToken(tokens)
    if not tokens[0][0] == "RBRACE":
      error(tokens[0], ']', 'whilestmt')

    return temp
  
  else:
    error(tokens[0], '[', 'whilestmt')

  return temp

def letstmts(tokens): # letstmts -> [let [varlist]]
  temp = Node()

  if tokens[0][0] == "LBRACE":
    
    # let
    nextToken(tokens)
    if not tokens[0][1] == "let":
      error(tokens[0], 'let', 'letstmt')
    temp.setData([tokens[0][0], tokens[0][1]])

    nextToken(tokens)
    if not tokens[0][0] == "LBRACE":
      error(tokens[0], '[', 'letstmt')

    # varlist
    nextToken(tokens)
    temp.addChild(varlist(tokens))

    # Need 2 closing brackets
    nextToken(tokens)
    if not tokens[0][0] == "RBRACE":
      error(tokens[0], ']', 'letstmt')

    nextToken(tokens)
    if not tokens[0][0] == "RBRACE":
      error(tokens[0], ']', 'letstmt')

    return temp
  
  else:
    error(tokens[0], '[', 'letstmt')

  return temp

def varlist(tokens): # varlist -> [name type] | [name type] varlist
  temp = Node()

  if tokens[0][0] == "LBRACE":
    
    # name
    nextToken(tokens)
    if not tokens[0][0] == "NAME":
      error(tokens[0], 'NAME', 'varlist')
    temp.setData([tokens[0][0], tokens[0][1]])

    # type
    nextToken(tokens)
    if not tokens[0][0] == "TYPES":
      error(tokens[0], 'TYPES', 'varlist')
    temp.addChild(Node([tokens[0][0], tokens[0][1]]))

    nextToken(tokens)
    if not tokens[0][0] == "RBRACE":
      error(tokens[0], ']', 'varlist')

    # Use the lookahead to determine if there's another varlist
    if tokens[1][0] == "LBRACE":
      nextToken(tokens)
      temp.addChild(varlist(tokens))

    return temp
  
  else:
    error(tokens[0], '[', 'varlist')

  return temp

def printstmts(tokens): # printstmts -> [stdout oper]
  temp = Node()

  if tokens[0][0] == "LBRACE":
    
    # stdout
    nextToken(tokens)
    if not tokens[0][1] == "stdout":
      error(tokens[0], 'stdout', 'printstmt')
    temp.setData([tokens[0][0], tokens[0][1]])

    # oper
    nextToken(tokens)
    temp.addChild(oper(tokens))

    # Finish production
    nextToken(tokens)
    if not tokens[0][0] == "RBRACE":
      error(tokens[0], ']', 'printstmt')

    return temp

  else:
    error(tokens[0], '[', 'printstmt')

  return temp

def exprlist(tokens): # exprlist -> expr | expr exprlist
  temp = Node()

  # expr
  temp.addChild(expr(tokens))

  # optional exprlist
  if not tokens[1][0] == "RBRACE":
    nextToken(tokens)
    temp.addChild(exprlist(tokens))

  return temp

def nextToken(tokens):
  tokens.pop(0)

def error(token, expected, production):
  print 'Invalid input: "%s"! Line: %s, colunm: %s' % (token[1], token[2], token[3])
  print 'Expecting: %s' % expected
  print 'In production %s' % production
  sys.exit(1)

def main(argument):
  with open(argument, 'r') as f:
    contents = f.read()
  parser(contents)

if __name__ == "__main__":
  main(sys.argv[1])
