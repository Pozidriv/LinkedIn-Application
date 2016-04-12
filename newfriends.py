#!/usr/bin/python
import urllib2
import cgitb
import cgi
import sys
cgitb.enable()

# We assume that the method used is POST

print "Content-Type:text/html\n\n"

listFriends = []

arguments = cgi.FieldStorage()
# This function will receive as input arguments (as returned by cgi.FieldStorage()
# It will return the list of friends to add to the list
# Tested, works
def getFriends(arguments) :
	for name in arguments :
		listFriends.append(name)
	return listFriends

# This function will receive as input a list of names, and a string representing a username. 
# It will add each friend of the list to the friends of the given user.
def addFriends(listFriends, username) :
	return

print "<html>"

# url = urllib2.Request.get_full_url()

# data = fetchGetData(url)
# print url

listFriends = getFriends(arguments)

print listFriends

print "</html>"
