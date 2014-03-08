#!/usr/bin/env python

class Node(object):

  def __init__(self, data=None):
    self.data = data
    self.children = []

  def traverse_pre(self, depth=0):
    # print prefix notation
    if self.data is not None:
      print ((' '* depth * 2) + self.getData())
    for i in self.children:
      if i.getData() is not None:
        i.traverse_pre(depth+1)
      else:
        i.traverse_pre(depth)

  def traverse_post(self, depth=0):
    # print postfix notation
    for i in self.children:
      if i.getData() is not None:
        i.traverse_post(depth+1)
      else:
        i.traverse_post(depth)
    if self.data is not None:
      print ((' '* depth * 2) + self.getData())

  def traverse_in(self):
    # Not going to implement infix notation
    pass     

  def setData(self, value):
    self.data = value

  def getData(self):
    return self.data

  def addChild(self, node):
    if not isinstance(node, Node):
      raise TypeError("Cannot add type %s to Node" % type(node))
    self.children.append(node)

def test(data):
  n = Node(data[0])
  data.pop(0)
  m = Node(data[0])
  data.pop(0)
  o = Node(data[0])
  data.pop(0)
  p = Node()
  n.addChild(m)
  n.addChild(o)
  p.addChild(m)
  n.traverse()


if __name__ == "__main__":
  things = ['+', '2', '3']
  test(things)
