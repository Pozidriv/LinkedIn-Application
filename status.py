#!/usr/bin/python
import cgi
import cgitb
cgitb.enable()

argv = cgi.FieldStorage()

"""Checks if status is empty"""
if argv.getvalue("status") != "":
	statusFile = open("status.txt","a")
	statusFile.write(argv.getvalue("user") + " " + argv.getvalue("status"))
	statusFile.close()

"""refreshes the dashboard by sending to a redirecting page"""
refreshDashboard = open("refreshDash.html")
for line in refreshDashboard:
	print line
