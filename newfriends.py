#!/usr/bin/python
import urllib

print "Content-Type:text/html\n\n"

listFriends = []
string = ""


# This function will receive as input a string representing a URL.
# It will output the get request passed in that URL
def fetchGetData(url) :
	getData = ""
	for i in range(len(url)) :
		if url[i] == "?" :
			getData = url[i:len(url)-2]
	return getData

# This function will receive as input a string in get format and will output a dictionnary 
# associating each variable name to its value.
def decode(string) :
	for i in range(len(string)) :
		if string[i] == "+" :
			string[i] = " "
		elif string[i] == "%" :
			return
	return

# This function will receive as input a list of names, and a string representing a username. 
# It will add each friend of the list to the friends of the given user.
def addFriends(listFriends, username) :
	return
	


url = urllib.request.full_url

data = fetchGetData(url)
print url
