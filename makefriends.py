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

print "Hey!"



def Catalog():
    
    currentuser  = "aniouche"
    
    print " debug : got in catalog fn"

# open the users.txt file

    try:
        file = open("users.txt", "r")
    
    except IOError:
        print "Please tell it to your litterate grandmas. Code : IOError - makefriends.py - open users.txt"
        sys.exit()

# open the makefriends.html file

    try:
        htmlfile = open("makeafriend.html", "r")
    
    except IOError:
        print "Please tell it to your litterate grandmas. Code : IOError - makefriends.py - open makefriends.html"
        sys.exit()

# prints the beggining of the html file, untilbreakpoint
#...

    html = htmlfile.readlines()

    for line in html:

        breakpoint = line.rstrip()
        if breakpoint!="HERE":
            print breakpoint

#------------------------------------------------------------------------------------------------------
# prints the checkboxes


# first line of the file

        else:


            line = file.readline()
            line = profile.rstrip()

            print "debug : before while"

            while line != "" :
    
                print " debug : in while"
            
                # do not want to print his name in the catalog
                if line == currentuser :
                
                    print " debug : in if line == currentuser"
                
                # go to the next username
                    for i in range(0,4):
                
                        line = file.readline()
                
                        line = file.rstrip()

                else :

                    print " debug : in else not currentuser"

                    username = line
                
                    # go to the fullname line, two steps away
                    line = file.readline()
                    line = file.readline()
                
                    fullname = line.rstrip()

                    print username
                    print " - "
                    print fullname
                    print " <input type=\"checkbox\" name=friends value=\"", username,
                    print "\">"

            # go to the next username, which is two steps away (1. job 2. username)
                    line = file.readline()
                    line = file.readline()


# end of while
        print " debug : end of while txt"
            
    print "debug : end of while html"

    file.close()
    html.close()

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

