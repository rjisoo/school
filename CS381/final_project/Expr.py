#!/usr/bin/env python

'''
Geoffrey Corey
CS 381
'''

'''
Haskell:
   data Expr = N Int
             | Bo Bool
             | Plus Expr Expr
             | If Expr Expr Expr
             | Equal Expr Expr
'''

Int = 0
Bool = 1
Plus = 2
If = 3
Equal = 4

class Expr(object):

  def __init__(self, data_type, data1, data2=None, data3=None):
    if data_type == Int:
      if isinstance(data1, int):
        if not data2 == None and not data3 == None:
          raise TypeError("Invalid operand count for Expr Int")
        else:
          self.is_terminal = True
          self.type = data_type
          self.expr1 = data1

      else:
        raise TypeError("Expr Int requires an integer value")

    elif data_type == Bool:
      if isinstance(data1, bool):
        if not data2 == None and not data3 == None:
          raise TypeError("Invalid operand count for Expr Bool")
        else:
          self.is_terminal = True
          self.type = data_type
          self.expr1 = data1
      
      else:
        raise TypeError("Expr Bool requires an boolean value")

    elif data_type == Plus:
      if isinstance(data1, Expr) and isinstance(data2, Expr) and data3 == None:
        self.is_terminal = False
        self.type = data_type
        self.expr1 = data1
        self.expr2 = data2
      else:
        raise TypeError("Expr Plus requires 2 operands of type Expr")

    elif data_type == If:
      if isinstance(data1, Expr) and isinstance(data2, Expr) and isinstance(data3, Expr):
        self.is_terminal = False
        self.type = data_type
        self.expr1 = data1
        self.expr2 = data2
        self.expr3 = data3
      else:
        raise TypeError("Expr If requires 3 operands of type Expr")

    elif data_type == Equal:
      if isinstance(data1, Expr) and isinstance(data2, Expr) and data3 == None:
        self.is_terminal = False
        self.type = data_type
        self.expr1 = data1
        self.expr2 = data2
      else:
        raise TypeError("Expr If requires 3 operands of type Expr")


def print_Expr(expr):
  stack = []
  print_Expr_rec(expr, stack)

  print ' '.join(stack)

def print_Expr_rec(expr, stack):
  if expr.type == Int:
    print_Int(expr, stack)

  elif expr.type == Bool:
    print_Bool(expr, stack)

  elif expr.type == Plus:
    print_Plus(expr, stack)

  elif expr.type == If:
    print_If(expr, stack)

def print_Int(expr, stack):
  if expr.type == Int:
    stack.append(str(expr.expr1))

  else:
    raise TypeError("Expected Expr Int")

def print_Bool(expr, stack):
  if expr.type == Bool:
    stack.append(str(expr.expr1))
  else:
    raise TypeError("Expected Expr Bool")
  

def print_Plus(expr, stack):
  if expr.type == Plus:
    print_Expr_rec(expr.expr1, stack)
    print_Expr_rec(expr.expr2, stack)
  else:
    raise TypeError("Expected Expr Plus")

def print_If(expr, stack):
  if expr.type == If:
    print_Expr_rec(expr.expr1, stack)
    print_Expr_rec(expr.expr2, stack)
    print_Expr_rec(expr.expr3, stack)

  else:
    raise TypeError("Expected Expr If")

def print_Equal(expr, stack):
  if expr.type == Equal:
    print_Expr_rec(expr.expr1, stack)
    print_Expr_rec(expr.expr2, stack)
  else:
    raise TypeError("Expected Expr Equal")


def semantic(expr):
  if expr.type == Int:
    return expr.expr1

  elif expr.type == Bool:
    return expr.expr1

  elif expr.type == Plus:
    return semantic(expr.expr1) + semantic(expr.expr2)

  elif expr.type == If:
      if semantic(expr.expr1):
        return semantic(expr.expr2)
      else:
        return semantic(expr.expr3)

  elif expr.type == Equal:
    return semantic(expr.expr1) == semantic(expr.expr2)

  else:
    raise TypeError("Invalid type for Expr")

def tc(expr):
  if expr.type == Int:
    return Int

  elif expr.type == Bool:
    return Bool

  elif expr.type == Plus:
    if tc(expr.expr1) == Int and tc(expr.expr2) == Int:
      return Int
    else:
      raise TypeError("Expr Plus 1st and 2nd operands must be of type Int")

  elif expr.type == If:
    if tc(expr.expr1) == Bool:
      if tc(expr.expr2) == Int and tc(expr.expr3) == Int:
        return Int
      elif tc(expr.expr2) == Bool and tc(expr.expr3) == Bool:
        return Bool
      else:
        raise TypeError("Expr If 2nd and 3rd operands must be of the same type")

  elif expr.type == Equal:
    if tc(expr.expr1) == tc(expr.expr2):
      return Bool

    else:
      raise TypeError("Expr Equal 1st and 2nd operands must be of the same type")

  else:
    raise TypeError("Expr type was not matched.")


def print_tc(expr):

  result = tc(expr)
  if result == Int:
    print 'Int'

  elif result == Bool:
    print 'Bool'

  elif result == If:
    print 'If'

  elif result == Plus:
    print 'Plus'

  elif result == 'Equal':
    print 'Equal'

  else:
    raise TypeError("Incorrect return value.")



if __name__ == '__main__':

  # My tests, ''' denotes block comments
  '''test1 = Expr(Bool, True)
  test2 = Expr(Int, 5)
  print_Expr(test2)
  test3 = Expr(Plus, Expr(Plus, Expr(Int, 5), Expr(Int, 7)), Expr(If, Expr(Bool, True), Expr(Int, 5), Expr(Int, 6)))
  print_Expr(test3)

  test4 = Expr(Plus, Expr(Int, 5), Expr(Int, 7))
  print semantic(test4)

  test5 = Expr(If, test1, test2, test2)
  print semantic(test5)
  print_tc(test5)'''

  e1 = Expr(If, Expr(Int, 3), Expr(Int, 3), Expr(Int, 3))
  print semantic(e1)
  try:
    print_tc(e1)
  except TypeError:
    print 'e1 type checking has TypeError'

  e2 = Expr(Plus, Expr(Int, 2), Expr(If, Expr(Bool, True), Expr(Int, 3), Expr(Int, 5)))
  print semantic(e2)
  try:
    print_tc(e2)
  except TypeError:
    print 'e2 type checking has TypeError'

  e3 = Expr(Plus, Expr(Int, 2), Expr(If, Expr(Bool, True), Expr(Int, 3), Expr(Bool, True)))
  print semantic(e3)
  try:
    print_tc(e3)
  except TypeError:
    print 'e2 type checking has TypeError'

  e4 = Expr(If, Expr(Equal, Expr(Int, 3), Expr(Int, 4)), Expr(Equal, e2, Expr(Int, 7)), Expr(Bool, False))
  print semantic(e4)

  try:
    print_tc(e4)
  except TypeError:
    print 'e4 type checking has TypeError'



'''
Written Answers:
    (a) The language I'm using is Python. It is an interpreted language and has object-oriented design principles.
        Python is a very versatile and general use language and is used in things like web-apps, operating system
        daemons, configuration scripts, etc. The syntax of python makes it very easy to read a program as almost
        a natural language. another strength of python is its list comprehension, making it very easy to manipulate
        lists and do a lot of things with lists.

        Some of the weaknesses of python are speed. While python is written in C and can be profiled and "compiled"
        down into a C type executable, there is still more overhead in the python written function than if written
        natively in C. If you are smart about the way you program in python, this decrease in performance can be
        mainly mitigated.

    (d) The advantage to using Haskell for this is the ease of creating a constructor for a specific data type
        as well as Haskell's pattern matching. Without the pattern matching, type checking and creation require a
        a lot of if/else statements to validate a constructed data type.

        I honestly cannot see a disadvantage for using Haskell when used in this context. Haskell would make this
        data type constructor and type checking much easier and clearer to the user.
        In Python however, because of the extra code required for the constructor as well as the code required
        for type checking, it is easy to get lost in the logic when trying to validate the correctness of the code.

Questions I wrote code for:
    (d)
    (e)
'''