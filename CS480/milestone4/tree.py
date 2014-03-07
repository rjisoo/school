#!/usr/bin/env python

class Node(object):
  def __init__(self, data=None):
    self.data = data
    self.children = []

  def traverse(self):
    for i in self.children:
      i.traverse()
    if not self.data == None:
      print self.data

  def setData(self, value):
    self.data = value

  def getData(self):
    return self.data

  def addChild(self, node):
    ''' A post order traversal of the tree '''
    if not isinstance(node, Node):
      raise TypeError("Invalid type adding to Node")
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
