#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ------------------------------------------------------------------------




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
			listFriends(i);
			fclose(file_ptr);
			return EXIT_SUCCESS;
		}
	}


}


// ------------------------------------------------------------------------

int listFriends(int i){

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

	printf(" <input type=\"submit\" value=\" See your friend's page\" ");


}
















	







