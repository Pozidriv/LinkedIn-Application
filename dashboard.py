#!/usr/bin/python
import cgi
import cgitb
cgitb.enable()

"""Method that returns the 20 most recent statuses made by friends in html format"""
def displayStatuses(friends):
	numberOfStatuses = 0
	statuses = "<p>"
	status = open("status.txt","r")
	for line in reversed(status.readlines()):
		splittedStatus = line.split(' ', 1)
		if splittedStatus[0] in friends and i < 20:
			statuses += "<br />" + splittedStatus[0].replace("$", "") + " said:<br /> " + splittedStatus[1]
			numberOfStatuses++
	statuses += "</p>"
	return statuses

argv = cgi.FieldStorage()
username = argv.getvalue("name")
friends = open("friends.txt","r")

"""Acquires the list of friends of user"""
for line in friends:
	if line.find("$"+username):
		friendList = line.split(",") """Will find way to separate username, come back when idea happens"""
friends.close()
['$' + i for i in friendList] """adds '$' to the beginning of all names"""

"""This is the part that displays the page"""
dashFile = open("dashboard.html","r")
dash = dashFile.readlines()
for line in dash:
	line = line.replace("Name here", username)
	line = line.replace("Statuses here", displayStatuses(friendList))
	print line
