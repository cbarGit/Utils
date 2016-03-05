#! /usr/bin/python
#Script for find every duplicates in a directory.
#It uses MD5sum to check if the data in files is unique.
#Eventually it writes the list of duplicates in a file called "duplicates.txt"
#
#USAGE:
#command [directory path]
#

import os
import sys
import hashlib
import argparse


#some arguments checking
parser = argparse.ArgumentParser(
        prog='findDupl.py')
parser.add_argument('FOLDER',help='a folder to check recursively')
args = parser.parse_args()


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

dir = os.path.dirname(os.path.abspath(__file__))

#function for calculate the md5sum of a file
def md5Checksum(filePath):
    with open(filePath, 'rb') as fh:
        m = hashlib.md5()
        while True:
            data = fh.read(8192)
            if not data:
                break
            m.update(data)
        return m.hexdigest()

md5list = []
files = []

#argument checking
if (os.path.isfile(sys.argv[1])):
    print(color.BOLD + color.RED + "ERROR\n" + color.END + color.BOLD +
            color.UNDERLINE + str(sys.argv[1]) + color.END + color.BOLD + " is not a directory" +
            color.END)
    exit(1)


#walking through names in directory
print(color.BOLD + "The subfolders present in this folder are:" + color.END)
for dirname, dirnames, filenames in os.walk(sys.argv[1]):
    # print path to all subdirectories first.
    for subdirname in dirnames:
        print(color.BLUE + os.path.abspath(os.path.join(dirname, subdirname)) + color.END)

    # print path to all filenames.
    for filename in filenames:
        #print(os.path.join(dirname, filename), ' :: ', (md5Checksum(os.path.join(dirname, filename))))
        md5list.append(md5Checksum(os.path.abspath(os.path.join(dirname, filename))))
        files.append(os.path.abspath(os.path.join(dirname, filename)))

    # editing the 'dirnames' list will stop os.walk() from recursing into there.
    if '.git' in dirnames:
        # don't go into any .git directories.
        dirnames.remove('.git')

#create dict with keys as filename and values as md5sum
md5dict = dict(zip(files, md5list))

#create list with all the different md5sums from each others. If there are duplicates, the list
#length should be smaller than the number of files.
md5temp = list(set([i for i in md5list if md5list.count(i) > 1]))

#create list of files with corrispondent md5sum taken from the list of md5sums. So if there are more files with
#the same md5sum they will be added to the list.
md5final = []
for i in md5temp:
    for k,v in md5dict.items():
        if (i == v):
            print(i, ' - ' ,k)
            md5final.append(k)

#sorting the final list
md5final.sort()

#check if there are any files or directory and print consequently
if len(md5final) > 0:
    print(color.BOLD + "The duplicate files are:" + color.END)
    f = open("duplicates.txt","a")
    for i in md5final:
        f.write(i + "\n")
        print(color.RED + i + color.END)
    f.close()
else:
    print(color.BOLD + "Duplicate files not present" + color.END)

