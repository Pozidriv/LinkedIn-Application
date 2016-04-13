#!/usr/bin/python
import urllib2
import cgitb
import cgi
import sys
cgitb.enable()

# We assume that the method used is POST

print "Content-Type:text/html\n\n"

arguments = cgi.FieldStorage()

# This function will receive as input arguments (as returned by cgi.FieldStorage()
# It will return the list of friends to add to the list
# Tested, works
def getVariables(arguments) :
	listVariables = []
	for name in arguments :
		listVariables.append(name)
	return listVariables

# This function will receive as input a list of names, and a string representing a username. 
# It will add each friend of the list to the friends of the given user.
# Tested, works
def addFriends(listFriends, username) :
	f = open("./friends.txt", 'r+')
	data = f.read(100000)
	username = '$' + username

	print "<br>", data, "<br>"

	# Finding the starting index of the line starting with the username
	index = data.find(username)

	if index == -1 :
		print "Error, username could not be found."
		print "<br>Username was: ", username
		return -1
	else :
		# We are looking for the end of the line starting with the username
		index = data.find('\n', index)

	if index == -1 : # eof has been reached
		f.close()
		f = open("./friends.txt", "a")
		f.append(",".join(listFriends))
		f.close()
	else :
		before = data[:index]
		after = data[index:]
		
		f.close()
		f = open("./friends.txt", "w")
		
		f.write(before)
		f.write(",".join(listFriends))
		f.write(after)
		f.close()
	
	return 0

print "<html>"

# url = urllib2.Request.get_full_url()

# data = fetchGetData(url)
# print url

listVariables = getVariables(arguments)
username = arguments.getvalue("username")
listVariables.remove("username")

addFriends(listVariables, username)

# print arguments
# print listVariables

print "</html>"
