import sys
import re

username = sys.argv[1]
friends = open("friends.txt","r")

"""Acquires the list of friends of user"""
for line in friends:
	if re.match(username,line):
		freindList = line.split()
friends.close()

status = open("status.txt","r")

