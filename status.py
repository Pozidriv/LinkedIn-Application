import sys

if argv[2]!="":
	statusFile = open("status.txt","a")
	statusFile.write(str(sys.argv[1]) + " " + str(sys.argv[2))
	statusFile.close()

"""call dashboard.py"""
