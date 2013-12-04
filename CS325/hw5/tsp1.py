#!/usr/bin/env python

import sys
import random
import copy
import argparse


class City:
    def __init__(self, name, x, y):
        self.name = name
        self.x = x
        self.y = y
    def __copy__(self):
        return City(self.name,self.x,self.y)
    def __eq__(self,other):
        return self.name == other.name and self.x == other.x and self.y == other.y

class World:
    cities = []
    l = None
    def __init__(self, route = None):
        if route != None:
            self.cities = route[:]

    def load(self, tour_file):
        #openfile = open(file,"r")
        with open(tour_file, 'r') as f:
          for line in f:
            identifier, x, y = line.split()
            city = City(identifier, int(x), int(y))
            self.cities.append(city)        
    
    def __copy__(self):
        return World(self.cities)
    def __lt__(self,other):
        return self.length() < other.length()
        
    def length(self):
        if self.l != None:
            return self.l
        self.l = 0.0
        for i in xrange(-1,len(self.cities)-1):
            cityA = self.cities[i]
            cityB = self.cities[i+1]
            self.l += ( (cityA.x-cityB.x)**2 + (cityA.y-cityB.y)**2 )**0.5
        return self.l
    
def distance(cityA, cityB):
    return ( (cityA.x-cityB.x)**2 + (cityA.y-cityB.y)**2 )**0.5

def crossover(mapA, mapB):
    flagA = True
    flagB = True
    length = len(mapA.cities)
    t = random.choice(mapA.cities)
    x = mapA.cities.index(t)
    y = mapB.cities.index(t)
    child = World([t])
    while flagA == True or flagB == True:
        x = (x - 1) % length
        y = (y + 1) % length
        if flagA == True:
            if mapA.cities[x] not in child.cities:
                child.cities.insert(0,mapA.cities[x])
            else:
                flagA = False
        if flagB == True:
            if mapB.cities[y] not in child.cities:
                child.cities.append(mapB.cities[y])
            else:
                flagB = False
    if len(child.cities) < length:
        rest = []
        for c in mapA.cities:
            if c not in child.cities:
                rest.append(c)
        random.shuffle(rest)
        child.cities += rest
    return child       
         
def mutate(route, p):
    if random.random() < p:
        i = j = 0
        mutated_route = copy.copy(route)
        while i == j:
            i = random.randint(0,len(route.cities)-1)
            j = random.randint(0,len(route.cities)-1)
        if i > j: i,j = j,i
        while i < j:
            mutated_route.cities[i],mutated_route.cities[j] = mutated_route.cities[j],mutated_route.cities[i]
            i+=1
            j-=1
        return mutated_route
    else:
        return route
            
def select(children):
    children.sort();
    p = []
    l = len(children)
    total = 0.0
    for i in xrange(1,l+1): total += i
    for i in xrange(l,0,-1): p.append(i/total)
    r = random.random();
    for rank, po in enumerate(p):
        if r < po:
            return children[rank]
        else:
            r -= po
   
def main(input_file, output_file):
    parentA = World()
    parentA.load(input_file)
    parentB = World(parentA.cities)
    random.shuffle(parentA.cities)

    lim = 8500

    t = 0
    best = parentA.length()
    while t < lim:
        children = []
        #crossover and mutate
        for each in xrange(0,10):
            child = mutate(crossover(parentA, parentB), 0.3)
            children.append(child)
        parentA = select(children)      
        if parentA.length() < best:
            best = parentA.length()
            parentB = parentA
        t += 1
        if (t/float(lim))%0.1 < 0.00001:
            print (t/float(lim))*100,"% completed, the shortest length is",int(best)
    print "100.0 % completed, the shortest length is",int(best)
    outfile = open(output_file,"w")
    print>>outfile, " ".join(c.name for c in parentB.cities),int(parentB.length())
    
if __name__ == "__main__":

  parser = argparse.ArgumentParser()
  parser.add_argument("tour_file", help="The input text file containing the cities to be toured")
  parser.add_argument("results_file", help="Out putput file for the resulting tour")
  args = parser.parse_args()
  main(args.tour_file, args.results_file)