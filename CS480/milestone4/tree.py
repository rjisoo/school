#!/usr/bin/env python
import collections

class Node(object):

  def __init__(self, data=None):
    self.data = data
    self.children = []

  def traverse_pre(self, depth=0):
    # print prefix notation
    if self.data is not None:
      print (('    '*depth) + self.data[1])
    for i in self.children:
      if i.data is not None:
        i.traverse_pre(depth+1)
      else:
        i.traverse_pre(depth)

  def traverse_post(self, depth=0):
    # print postfix notation
    for i in self.children:
      if i.data is not None:
        i.traverse_post(depth+1)
      else:
        i.traverse_post(depth)
    if self.data is not None:
      print (('    '*depth) + self.data[1])

  def build_stack_pre(self):
    tree = []
    self.build_stack_recurse_pre(tree)
    return tree

  def build_stack_recurse_pre(self, stack):
    if self.data is not None:
      stack.append(self)
    for i in self.children:
      i.build_stack_recurse_pre(stack)

  def build_stack_post(self):
    tree = []
    self.build_stack_recurse_post(tree)
    return tree

  def build_stack_recurse_post(self, stack):
    for i in self.children:
      i.build_stack_recurse_post(stack)
    if self.data is not None:
      stack.append(self)



  def setData(self, value):
    self.data = value

  def getData(self):
    return self.data

  def addChild(self, node):
    if not isinstance(node, Node):
      raise TypeError("Cannot add type %s to Node" % type(node))
    self.children.append(node)

def is_number(s):
  try:
    float(s)
    return True
  except ValueError:
    return False

def test():
  Token = collections.namedtuple('Token', ['typ', 'value', 'line', 'column'])
  token1 = Token('BINOP', '+', 1, 5-0)
  token2 = Token('INTEGER', '2', 1, 5-0)
  token3 = Token('INTEGER', '3', 1, 5-0)
  n = Node(token1)
  m = Node(token2)
  o = Node(token3)
  p = Node()
  p.addChild(n)
  n.addChild(m)
  n.addChild(o)
  p.traverse_post()
  p.traverse_pre()

  t = p.build_stack()

  for i in t:
    print i.data

if __name__ == "__main__":
  test()
