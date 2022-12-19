###################################
## John Margaronis               ##
## CS-210 Programming Languages  ##
## Corner Grocer                 ##
## 12/11/2022                    ##
###################################

import re
import string
import collections

def generateList():
    with open('CornerGrocer.txt') as grocerList:
        counts = collections.Counter(line.strip() for line in grocerList) 
    for k in counts:
        print('  --> %s: %d' % (k, counts[k]))

def displayFrequency(item):
    item = item.capitalize()
    with open('CornerGrocer.txt') as grocerList:
        data = grocerList.read()
        frequency = data.count(item)
        return frequency

def writeItems():
    with open('frequency.dat', "w") as grocerListOut:
        with open('CornerGrocer.txt') as grocerList:
            counts = collections.Counter(line.strip() for line in grocerList)
        for k in counts:
            grocerListOut.write('%s: %d\n' % (k, counts[k]))