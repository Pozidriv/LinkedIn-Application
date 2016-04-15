#!/usr/bin/python
import sys
import os
import cgi
import cgitb
cgitb.enable()

print "Content-Type: text/html"
print

#Method that returns the 20 most recent statuses made by friends in html format
def displayStatuses(friends):
	try:
		statusFile = open("status.txt","r")
	except IOError:
		print "Didn't work"
		sys.exit()

	i = 0
	statuses = "<p>"
	chronoStatus = reversed(statusFile.readlines())
	for line in chronoStatus:
		splittedStatus = line.split(' ', 1)
		if splittedStatus[0] in friends and i < 20:
			statuses += "<br />" + splittedStatus[0].replace("$", "") + " said:<br /> " + splittedStatus[1]
			i+=1
	statuses += "</p>"
	statusFile.close()
	return statuses

arguments = cgi.FieldStorage()
username = arguments.getvalue("username")
friendList = []

try:
	friendFile = open("friends.txt","r")
except IOError:
	print "Friends no work"
	sys.exit()

friends = friendFile.readlines()

#Acquires the list of friends of user
for line in friends:
	if line.find("$"+username):
		newLine = line.replace(" ", ",", 1)
		newLine = newLine.replace("$", "")
		friendList += newLine.split(",")
friendFile.close()

#This is the part that displays the page
try:
	dashFile = open("dashboard.html","r")
except IOError:
	print "no dash"
	sys.exit()

dash = dashFile.readlines()
for line in dash:
	newLine = line.replace("Name here", username)
	newLine = newLine.replace("Statuses here", displayStatuses(friendList))
	print newLine
