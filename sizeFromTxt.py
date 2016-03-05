#! /usr/bin/python

#USAGE:
#command [PATHFILE]
#
#To use in combination with findDupl.py
#


import os
import sys
import argparse

class color:
   PURPLE = '\033[95m'
   CYAN = '\033[96m'
   DARKCYAN = '\033[36m'
   BLUE = '\033[94m'
   GREEN = '\033[92m'
   YELLOW = '\033[93m'
   RED = '\033[91m'
   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   END = '\033[0m'


#some arguments checking
parser = argparse.ArgumentParser(
        prog='sizeFromTxt.py')
parser.add_argument('PATHFILE',help='a file text with one file path in every line')
args = parser.parse_args()


fname = sys.argv[1]

with open(fname) as f:
    content = f.readlines()

totSize = 0

content.sort()

for i in content:
    if i != "\n":
        i = i.replace("\n","")
        fstat = os.stat(i)
        totSize += fstat.st_size
        print(color.BLUE + str(i) + color.END + ": " + str(fstat.st_size))

print("Total size:\n", totSize)


