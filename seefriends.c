#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ------------------------------------------------------------------------

void getFriends(char *user);
void friendProfile(char *friend);
void listFriends(char *friend);
void errorMessage(int error);


// ------------------------------------------------------------------------

int main(){
printf("Content-Type:text/html\n\n"); 

// Getting input with post

        int n = atoi(getenv("CONTENT_LENGTH"))+1;
	char string[120];
        
	fgets(string, n, stdin);
// Verifying if the input is a username or the friend chosen by the user

	char *input = strtok(string,"=");

	if(strcmp(input,"user")==0){
		input = strtok(NULL,"=");
		int length = strlen(input)+1;
		char user[length];
		int i = 0;
	        while (i<length-1) {
                	if (*(input+i)!='+') {
                    		user[i]=*(input+i);;
                	}
                	else if (*(input+i)=='+'){
                    		user[i]=' ';
                	}
			i++;
		}
		user[length-1] = '\0';
		getFriends(user);
		return EXIT_SUCCESS;
	}
	
	else if(strcmp(input,"friend")==0){


                input = strtok(NULL,"=");
                int length = strlen(input)+1;
                char friend[length];
		int i = 0;
                while (i<length-1) {

                        if (*(input+i)!='+') {
                                friend[i]=*(input+i);;
                        }
                        else if (*(input+i)=='+'){
                                friend[i]=' ';
                        }
                        i++;
                }
		friend[length-1]='\0';
		friendProfile(friend);
                return EXIT_SUCCESS;

	} 

// If neither, just quit bro, just quit.

	else {
		printf(" Invalid input for seefriends.c : user name of friend name \n");
		return EXIT_FAILURE;

	}

    return EXIT_SUCCESS;

}

// ------------------------------------------------------------------------

void getFriends(char *user){


	FILE *file_ptr;
	char line[2048];
	char friends[2048];
	char *name;
	int i = 0;

// The program is not able to open the file, even if i put the full http

	file_ptr = fopen("../LinkedIn-Application/friends.txt", "rt");
		
		// just in case...

		if (file_ptr==NULL){
			errorMessage(1);
			return;
		}


	while(!feof(file_ptr)){
		fgets(line, 2047, file_ptr);
		strcpy(friends, line);
		
		if(line[0]=='\n'){
			i++;
			continue;
		}
	
		else {
			name = strtok(line, ",");
	
		
			if(strcmp(name,user)!=0){
				i++;
				continue;
			}

			else {
				fclose(file_ptr);
				listFriends(friends);
				return;
			}
		}
	}


}


// ------------------------------------------------------------------------

void listFriends(char *friends){

	
    	FILE *html_ptr = fopen("../LinkedIn-Application/seefriends.html", "rt");
	char html_line[2048];
	char *putRadio = "RADIOBUTTONS\n";

	// Not able to open the file

	if(html_ptr==NULL){

		printf("Inside listFriends \n");
		errorMessage(1);
	}




	// First token is the username
	strtok(friends,",");

	// Then we have the friends
	friends = strtok(NULL,",");


	// Printing the html file

	while(!feof(html_ptr)){

        fgets(html_line, 2047, html_ptr);
	        
		if(strcmp(html_line,putRadio)==0){

        		// If the user does not have friend
        		if(friends==NULL){
                		errorMessage(2);
                		fclose(html_ptr);
                		return;
        		}	


        		while(friends != NULL){

                		printf("<input type=\"radio\" name=\"friend\" value=\"%s\">&nbsp;&nbsp;%s<br/>",friends,friends);

                		friends = strtok(NULL,",");
        		}
		}

		else {
			printf("%s\n",html_line);
		}
    	}



    fclose(html_ptr);
	
	return;
}


//---------------------------------------------------------------------------

void friendProfile(char *friend){
    FILE *profile_ptr;
    char line[2048];
    profile_ptr = fopen("../LinkedIn-Application/users.txt", "rt");

    // just in case...

    if (profile_ptr==NULL){
   	printf(" Inside friendProfile \n "); 
    	errorMessage(1);
        return;
    }


   fgets(line, 2047, profile_ptr);
   while(!feof(profile_ptr)){
	
// Creating a string without the training linefeed
	
	int length = strlen(line)-1;
	char text[length];

	int i = 0;
	while(i<length){
		text[i] = line[i];
		i++;
	}
	text[i] = '\0';

// Comparing the pretty string and the username of the friend


	if (strcmp(text, friend) != 0){
		int j = 0;

// If they do not match, go four lines further

		while(j<4){
			fgets(line, 2047, profile_ptr);
			j++;
		}
		continue;
	}

// If they match, prints her/his profile


	else {
 		    FILE *html_ptr;
		    char html_line[2048];
    		    html_ptr = fopen("../LinkedIn-Application/profile.html", "rt");
    		    char *putUSERNAME ="USERNAME\n";
		    char *putFULLNAME ="FULLNAME\n";
		    char *putJOB = "JOB\n";

		// Currently at username : do fgets twice to go to FULLNAME
		fgets(line, 2047, profile_ptr);
		fgets(line, 2047, profile_ptr);

                // To be put in a gorgeous table soon

		while(!feof(html_ptr)){
			
			fgets(html_line, 2047, html_ptr);
			if(strcmp(putUSERNAME, html_line)==0){
				printf("%s", friend);
			}
			
			else if( strcmp(putFULLNAME, html_line)==0){
				printf("%s", line);
			}

			else if( strcmp(putJOB, html_line)==0){
				fgets(line, 2047, profile_ptr);
				printf("%s", line);
			}
			
			else{
				printf("%s", html_line);
			}

		}
            

		fclose(html_ptr);
                fclose(profile_ptr);
                return;
            }
    }
    return;
}


//---------------------------------------------------------------------------

void errorMessage(int error){

	// The file that seefriends.c tried to open does not exist

	if(error == 1){
	        printf("<html>");

                printf("<body style=\"background-color:#72B2AA;\">");

                printf("<font face=\"arial\"><font size=\"18\"><center><b><u></br>See a friend page </u></b></center></font></br></br>");

                printf("<i><h3><font color =\"darkred\">Error. The filename does not exist. Please tell to your litterate grandmas that a mistake occured </h3></i><br/></font>");
                printf("</body>");
                printf("</html>");
		
		return;
	}


	// The user does not have any friend
	else if(error == 2){

                printf("</form>");

                printf("You do not have friends for the moment. You can go back to your dashboard to access makefriends page<br/><br/>>");
                printf("<a href=\"http://www.cgi.cs.mcgill.ca/~djosep13/LinkedIn-Application/dash.html\" target=\"_self\"><br/><br/><font face=\"arial\"><font size=\"5\"> Dashboard</font></a>");

                printf("</body>");
                printf("</html>");

                return;
	}

	return;
}
// ------------------------------------------------------------------------











	









