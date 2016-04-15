#!/usr/bin/python
import urllib
import cgitb
import cgi
import sys
cgitb.enable()

# We assume that the method used is POST

print "Content-Type:text/html\n\n"

arguments = cgi.FieldStorage()


#--------Functions-------------------------


# This function will receive as input arguments (as returned by cgi.FieldStorage()
# It will return the list of friends to add to the list
# Tested, works
def getVariables(arguments) :
	listVariables = []
	for name in arguments :
		listVariables.append(name)
	return listVariables

#------------------------------------------

# This function receives as input a list of names and a username.
# It removes from the list the names that are in the user's list of friends.
def removeDuplicates(listFriends, username) :
	string = ""
	duplicates = []
	f = open("./friends.txt", "r")
	data = f.readlines()
	
	for line in data :
		n = len(username)
		if line[:n+1] == ('$' + username) :
			for friend in listFriends :
				if line.find(friend, 0) >= 0 :
					duplicates.append(friend)
			# end of for friend loop
			for friend in duplicates :
				listFriends.remove(friend)
			return listFriends
	# end of for line loop

	return listFriends

# end of removeDuplicates
	

# This function will receive as input a list of names, and a string representing a username. 
# It will add each friend of the list to the friends of the given user.
# Tested, works
def addFriends(listFriends, username) :
	f = open("./friends.txt", 'r+')
	data = f.read()
	username = '$' + username

	#print "<br>", data, "<br>"

	# Finding the starting index of the line starting with the username
	index = data.find(username)

	if index == -1 :
		print "Error, username could not be found."
		print "<br>Username was: ", username
		sys.exit()
	else :
		# We are looking for the end of the line starting with the username
		index = data.find('\n', index)

	if index == -1 : # eof has been reached
		f.close()
		f = open("./friends.txt", "a")
		f.append("," + ",".join(listFriends))
		f.close()
	else :
		before = data[:index]
		after = data[index:]
		
		f.close()
		f = open("./friends.txt", "w")
		
		f.write(before)
		f.write("," + ",".join(listFriends))
		f.write(after)
		f.close()
	
	return 0

#----------------------------------------------

# Retrieving the variables from the form
listVariables = getVariables(arguments)

# Removing the username from listVariables (since we won't be adding it)
username = arguments.getvalue("username")
listVariables.remove("username")

# Removing duplicates
listVariables = removeDuplicates(listVariables, username)

# Adding friends
if listVariables : 
	addFriends(listVariables, username)

	data = urllib.urlopen("http;//cs.mcgill.ca/~sgrego15/success_addfriends.html").read()

	index = data.find("$")
	before = data[:index]
	after = data[index+1:]
	output = before + username + after
	
	print output
else :
	data = urllib.urlopen("http://cs.mcgill.ca/~sgrego15/error_noUserSel.html").read()

	index = data.find("$")
	before = data[:index]
	after = data[index+1:]
	output = before + username + after
	
	print output
