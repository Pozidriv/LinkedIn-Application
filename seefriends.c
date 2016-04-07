#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ------------------------------------------------------------------------


 
// there is going to be a friends.txt created by makefriends.py

// This is a C program called seefriends.c .
// This program generates a webpage that lists all the usernames of friends for the current user. 
// Determine a mechanism by which the user can pick one friend from the list.
// The program then displays the profile for that user.
// The program returns to the see a friend page.


// friends.txt is formatted in the following way: 

// username friend1 friend2 friend3...
// where each token is a username

// so seefriends.c fget each line, tokenize, look for the username
// If it is the good username, list each friend's names radio button cgi
// submit button



// ------------------------------------------------------------------------


int getFriends(char *user){


	FILE *file_ptr;
	char line[2048];
	char *name;
	int i = 0;
	file_ptr = fopen(friends.txt, "rt");
		
		// just in case...

		if (file_ptr==NULL){
			printf("Error. The filename does not exist. Please try again. \n ");
			return EXIT_FAILURE;
		}


	while(!eof(file_ptr)){

		fgets(line, 2047, file_ptr);
	
		name = strtok(line, ",");
	
		if(strcmp(name, user)!=0){
			i++;
			continue;
		}

		else {
			listFriends(user, i);
			fclose(file_ptr);
			return EXIT_SUCCESS;
		}
	}


}


// ------------------------------------------------------------------------

int listFriends(char *user, int i){

	FILE *file_ptr;
        char line[2048];
        char *friend;

        file_ptr = fopen(friends.txt, "rt");

	fgets(line, 2047, file_ptr);

        while(i){

                fgets(line, 2047, file_ptr);
                i--;
        }

	strtok(line,",");
	friend = strok(NULL,",");

	while(friend != NULL){

		printf(" <input type=\"radio\" name=\"friend\" value=\"%s\">%s<br /> ", friend, friend);
	
		friend = strtok(NULL,",");

	}

	prinf(" <input type=\"submit\" value=\" See your friend's page\" ");


}
















	







