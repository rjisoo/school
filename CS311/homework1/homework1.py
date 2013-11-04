'''
Geoffrey Corey
CS311 w13 Section 001
Project 1
Python section


Works with python 2 only.
'''

import sys
import os
import csv
import numpy

def create_dirs():
    course = raw_input("Please enter a course [CS311]: ")
    term = raw_input("Please enter a term [w13]: ")
    path = "~/" + course + "/" + term
    path_2 = path + "/" + "assignments"
    path_3 = path + "/" + "examples"
    path_4 = path + "/" + "exams"
    path_5 = path + "/" + "lecture_notes"
    path_6 = path + "/" + "submissions"
    
    if not os.path.exists(os.path.expanduser("~/" + course)):
        os.makedirs(os.path.expanduser(path))
        os.makedirs(os.path.expanduser(path_2))
        os.makedirs(os.path.expanduser(path_3))
        os.makedirs(os.path.expanduser(path_4))
        os.makedirs(os.path.expanduser(path_5))
        os.makedirs(os.path.expanduser(path_6))
    else:
        # if not os.path.exists(os.path.expanduser(path)):
        #    os.makedirs(os.path.expanduser(path))
        if not os.path.exists(os.path.expanduser(path_2)):
            os.makedirs(os.path.expanduser(path_2))
        if not os.path.exists(os.path.expanduser(path_3)):
            os.makedirs(os.path.expanduser(path_3))
        if not os.path.exists(os.path.expanduser(path_4)):
            os.makedirs(os.path.expanduser(path_4))
        if not os.path.exists(os.path.expanduser(path_5)):
            os.makedirs(os.path.expanduser(path_5))
        if not os.path.exists(os.path.expanduser(path_6)):
            os.makedirs(os.path.expanduser(path_6))
    if not os.path.islink(os.path.expanduser("~/website")):
        os.symlink("/usr/local/classes/eecs/winter2013/cs311/public_html", os.path.expanduser("~/website"))
    if not os.path.islink(os.path.expanduser("~/handin")):
        os.symlink("/usr/local/classes/eecs/winter2013/cs311/handin", os.path.expanduser("~/handin"))

def five_con_sum():
    num = 7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450
    ints = [int(i) for i in str(num)]
    maxVal = 0
    for i in range(1000 - 5):
        product = ints[i] * ints[i + 1] * ints[i + 2] * ints[i + 3] * ints[i + 4]
        if product >= maxVal: maxVal = product
    print maxVal 
    
def name_scores():
    names = open('names.txt').read()
    names = names.strip().split('","')[1:-1]
    names.sort()  
    print "Names sorted."
    pass  # ran out of time to make dictionary and then calculate.  

def triangle_term():
    pass  # ran out of time to implement triangle values.

def ui():
    # User interface part
    while True:
        print "\n1.    Create directories\n"
        print "2.    Find greatest sum of 5 cons. numbers\n"
        print "3.    Find name scores from name file\n"
        print "4.    Find nth triangle term\n"
        print "5.    Exit\n"
        selection = raw_input("Please chose an option: ");

        if selection == "1":
            create_dirs()
        elif selection == "2":
            five_con_sum()
        elif selection == "3":
            name_scores()
        elif selection == "4":
            triangle_term()
        elif selection == "5":
            sys.exit()
        else:
            print "Invalid selection [1-5]\n"

if __name__ == '__main__':
    ui()
