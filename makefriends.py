#!/usr/bin/python

import sys
import os
import cgitb
import cgi

cgitb.enable()

# 1. Read users.txt and takes each users (except himself) and displays them with a check button
#   a) open the file
#   b) look for the username : if it is the current user, next
#   c) prints the username
#   d) go to the full name and prints it (breakpoint)
#   e) c and d are done will printing the html file makefriends.html




print "Content-Type:text/html\n\n"
print

#currentuser = cgi.fieldStorage()


def Catalog():
    
    currentuser  = "aniouche"
    

# open the users.txt file

    try:
        data = open("users.txt", "r")
    
    except IOError:
        print "Please tell it to your litterate grandmas. Code : IOError - makefriends.py - open users.txt"
        sys.exit()

# open the makefriends.html file

    try:
        htmlfile = open("makefriends.html", "r")
    
    except IOError:
        print "Please tell it to your litterate grandmas. Code : IOError - makefriends.py - open makefriends.html"
        sys.exit()

# prints the beggining of the html file, untilbreakpoint
#...

    html = htmlfile.readlines()

    for line in html:

        breakpoint = line.rstrip('\n')
        if breakpoint!="CHECKBOXES":
            print breakpoint

#------------------------------------------------------------------------------------------------------
# prints the checkboxes


# first line of the file

        else:


            line = data.readline()
            line = line.rstrip('\n')


            while line != "":
    
                print line
		print "..."
                # do not want to print his name in the catalog
                if line == currentuser :
                
                # go to the next username
                    for i in range(0,4):
                
                        line = data.readline()
 			               
                        line = line.rstrip('\n')



                else:


                    username = line
                
                    # go to the fullname line, two steps away
                    line = data.readline()
                    line = data.readline()
                
                    fullname = line.rstrip('\n')

                    print " <input type=\"checkbox\" name=friends value=\"", username,
                    print "\">"

                    print username
                    print " - "
                    print fullname
		    print "<br/>"

            # go to the next username, which is two steps away (1. job 2. username)
                    line = data.readline()
                    line = data.readline()


# end of while
            

    data.close()
    htmlfile.close()

    print "end of catalog"


# end of catalog




Catalog()


# youri parts in newfriends.py

# 2. reads with post method and appends each friends to friends.txt
#   a) open the file
#   b) find the user
#   c) keeps this line


#   a) take one friend
#   b) looks if already a friend
#   c) appends the name
#   d) next token

