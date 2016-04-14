<<<<<<< HEAD
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
=======
#!/usr/bin/python
import cgitb
import cgi
import sys
cgitb.enable()

print "Content-Type:text/html\n\n"

arguments = cgi.FieldStorage()

#----------Functions---------------------------------

# This function will read and print dashboard.html until it reaches the next occurence
# of USERNAME after the given index.
# It then prints the inputted username and returns the index where USERNAME was found 
# returns -1 if username was not found
def replaceUsername(user, index) :
	data = open("./dashboard.html", "r").read()
	
	index = data.find("USERNAME", index)

	if index < 0 :
		return -1
	print data[:index]
	print username
	return index + 8
# end of replaceUsername

# Retrieves all the friends of a given user and returns them as a list
def getFriends(user) :
	data = open("./friends.txt", "r").read()
	ouput = []
	string = ""

	index = data.find('$' + user)
	index = index + len(user) + 2
	
	while (data[index] != '\n') :
		if (data[index] != ',') :
			string = string + data[index]
		else :
			ouput.append(string)
			string = ""
	# end of while

	return output
# end of getFriends

# This function prints the statuses of the given user.
# Calls getFriends to get the list of friends of the user
# For each line in status.txt, if the username
def displayStatuses(user) :
	f = open("./status.txt", "r")
	friends = getFriends(user)
	counter = 0 # counter for number of statuses displayed
	string = ""
	line = ""

	line = f.readline()
	while (line && counter <= 20) :
		string = getUser(line)
		if (string in friends) :
			counter = counter + 1
			print line[len(string):]
			print "<br>"
		
		line = f.readline()

	return
# end of desplayStatuses
		
		
	
>>>>>>> 55a92dad2de3d6a6a96cbda96d7887162f054bd9

