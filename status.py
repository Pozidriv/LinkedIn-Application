#!/usr/bin/python
import cgi
import cgitb
import sys
import os
cgitb.enable()

print "Content-Type: text/html"
print

argv = cgi.FieldStorage()

#Checks if status is empty. If not, appends it to the status file
if argv.getvalue("status") != None:
	try:
		statusFile = open("./status.txt","a")
	except IOError:
		print "status no open"
		sys.exit()
	statusFile.write(argv.getvalue("user") + " " + argv.getvalue("status") + "\r\n")
	statusFile.close()

#Refreshes the dashboard by sending to a redirecting page
try:
	refreshDashboard = open("./refreshDash.html")
except IOError:
	print "Updates no open"
	sys.exit()
for line in refreshDashboard:
	print line.replace("Name here", argv.getvalue("user"))
# refreshDashboard.close()
