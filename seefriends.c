#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_ERROR 1
#define NOFRIENDS 2

// ------------------------------------------------------------------------------------------ //

void getFriends(char *user);
void friendProfile(char *user, char *friend);
void listFriends(char *user, char *friend);
void errorMessage(int error, char *user);

// ------------------------------------------------------------------------------------------ //



/*---------------------------------------------------------------------------------/
                                    MAIN
 --------------------------------------------------------------------------------
  The main method is receiving the post data and verify if it received
   the user name, in which case it will call methods that will list the friends
   this user, or a friend of the username, in which case it will call            
   the method that will generates the html profile of the friend.
 -------------------------------------------------------------------------------*/



int main(){
    
    printf("Content-Type:text/html\n\n");
    
    // Getting input with post
    
    int n = atoi(getenv("CONTENT_LENGTH"))+1;
    char string[120];
    
    fgets(string, n, stdin);
    
    
    // Verifying if the input is a [user name] or the [friend] chosen by the user
    // According to the input name (friend= or user=)
    
    char *input = strtok(string,"=+");
      
 
    if(strcmp(input,"user")==0){
   
	input = strtok(NULL,"=+");
	int a = strlen(input);
	char *user = malloc(a);
	strcpy(user, input);
        
    // Calling the method that will get the friends of the user
        
        getFriends(user);
        return EXIT_SUCCESS;
    }
    
    
    // Making an array wuth the name of the friend
    
    else if(strcmp(input,"friend")==0){
        
        input = strtok(NULL,"=+");
        int a = strlen(input);
        char *user = malloc(a);
        strcpy(user, input);

	input = strtok(NULL,"=+");
	int b = strlen(input);
	char *friend = malloc(b);
	strcpy(friend, input);


        friendProfile(user, friend);
        return EXIT_SUCCESS;
        
    }
    
    // If neither, just quit bro, just quit.
    
    else {
        printf(" Invalid input for seefriends.c : user name of friend name \n");
        return EXIT_FAILURE;
        
    }
    
    return EXIT_SUCCESS;
    
}



/*---------------------------------------------------------------------------------/
                                  getFriends
 --------------------------------------------------------------------------------
    This method has for input the user username and will find the list of friends
    of the current user, and will then call listFriends.
 -------------------------------------------------------------------------------*/


void getFriends(char *user){
    
    
    FILE *file_ptr;
    char line[2048];
    char friends[2048];
    char *name;
    int i = 0;
    
    
    
    file_ptr = fopen("../friends.txt", "rt");
    
    
    // just in case... Throw an error page
    
    if (file_ptr==NULL){
        errorMessage(FILE_ERROR, user);
        return;
    }
    
    
    // Opens the friends.txt file
    
    while(!feof(file_ptr)){
        fgets(line, 2047, file_ptr);
        
        // friends is untouched by strtok
        strcpy(friends, line);
        
        if(line[0]=='\n'){
            i++;
            continue;
        }
        
        // 1. Take the first entry and verify if it is the username that we are looking for
        else {
            name = strtok(line, "$,\n");
            
            if(strcmp(name,user)!=0){
                i++;
                continue;
            }
            
        // If so, close the file, and call the listFriends with the full line of the friends.txt
            else {
                fclose(file_ptr);
                listFriends(user, friends);
                return;
            }
        }
    }
}




/*---------------------------------------------------------------------------------/
                                listFriends
 --------------------------------------------------------------------------------
    This method has for input the list of friends of the current user and will
    generates the html page seefriends.html that will displays the list of friends
    the user, with radio buttons. The user click and the value get submitted 
    with post method.
 -------------------------------------------------------------------------------*/

void listFriends(char *user, char *friends){
    
    
    FILE *html_ptr = fopen("../seefriends.html", "rt");
    char html_line[2048];
    char *putRadio = "RADIOBUTTONS\n";
    char *putLINK = "value=\"USERNAME\"";
    
    // if not able to open the file
    
    if(html_ptr==NULL){
        
        errorMessage(FILE_ERROR, user);
        fclose(html_ptr);
    }
    

    // First token is the username
    strtok(friends,"$,\n");
    
    // Then we have the friends
    friends = strtok(NULL,"$,\n");
	    
    // If the user does not have friend
    if(friends==NULL){
         errorMessage(NOFRIENDS, user);
         return;
     }

    
    // Printing the html file
    
    while(!feof(html_ptr)){
        
        fgets(html_line, 2047, html_ptr);
        
        if(strcmp(html_line,putRadio)==0){
            
            
            // If the user does not have friend
 //           if(friends==NULL){
   //             errorMessage(NOFRIENDS, user);
     //           return;
       //     }
            
            
            while(friends != NULL){

                
                printf("<input type=\"radio\" name=\"friend\" value=\"%s %s \">&nbsp;&nbsp;%s<br/>\n",user,friends,friends);
                
                friends = strtok(NULL,"$,\n");
            }
        }
 
	else if(strcmp(html_line, putLINK)==0){
		printf("value=\"%s\">\n", user);
	}

       
        else {
            printf("%s\n",html_line);
        }
    }
    
    
    
    fclose(html_ptr);
    
    return;
}


/*---------------------------------------------------------------------------------/
                                friendsProfile
 --------------------------------------------------------------------------------
    This method take as input the name of the chosen friend and generate
    the html page with the profile informations.
 -------------------------------------------------------------------------------*/

void friendProfile(char *user, char *friend){
    FILE *profile_ptr;
    char line[2048];
    profile_ptr = fopen("../users.txt", "rt");
    
    // just in case...
    
    if (profile_ptr==NULL){
        
        errorMessage(FILE_ERROR, user);
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
            html_ptr = fopen("../profile.html", "rt");
            char *putUSERNAME ="USERNAME\n";
            char *putFULLNAME ="FULLNAME\n";
            char *putJOB = "JOB\n";
	    char *putLINK = "value=\"USERNAME\">\n";
                
            
            // if the file cannot be open
            
            if(html_ptr==NULL){
                errorMessage(FILE_ERROR, user);
                return;
            }
            
            // Currently at username : do fgets twice to go to FULLNAME
            fgets(line, 2047, profile_ptr);
            fgets(line, 2047, profile_ptr);
            
            
            // generate the profile.html for the friend chosen
            // If put some "breakpoints" in the profile.html file
            // such that we can insert the changing values
            
            while(!feof(html_ptr)){
                
                fgets(html_line, 2047, html_ptr);
   	
		if(strcmp(putLINK, html_line)==0){
			printf("value=\"%s\">\n",user);
		}
             
                else if(strcmp(putUSERNAME, html_line)==0){
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




/*---------------------------------------------------------------------------------/
                                    errorMessage
 --------------------------------------------------------------------------------
    This method has for input an error code and generates and html page
    the displays the appropriate message error.
 -------------------------------------------------------------------------------*/


void errorMessage(int error, char *user){
    
    // The file that seefriends.c tried to open does not exist
    
    if(error == FILE_ERROR){
        
        printf("<html>");
        
        printf("<body style=\"background-color:#72B2AA;\">");
        
        printf("<font face=\"arial\"><font size=\"18\"><center><b><u></br>See a friend page </u></b></center></font></br></br>");
        
        printf("<i><h3><font color =\"darkred\">Error. The filename does not exist. Please tell to your litterate grandmas that a mistake occured </h3></i><br/></font>");
        printf("</body>");
        printf("</html>");
        
        return;
    }
    
    
    // The user does not have any friend
    else if(error == NOFRIENDS){
        
        printf("<html> \n  <head> \n");
	printf("<title> See friends </title> \n");
	printf("<link href=\"http://cgi.cs.mcgill.ca/~djosep13/global.css\" rel=\"stylesheet\" type=\"text/css\"> \n");     
	printf("</head> \n <body> \n");



	printf("<table id=\"titletable\"> \n");
	printf("<tr><th id=\"header\">SEE YOUR FRIENDS PAGE</th></tr>\n");
	printf("<tr><td id=\"subtitle\">Want to learn more about your friends?</td></tr>\n");
	printf("</table><br/><br/><br/>\n");
	printf("<h1 id=\"instr\">:(</h1>\n");
	printf("<hr width=\"60%\", color=\"black\"><br/>\n");



        printf("You do not have friends for the moment. You can go back to your dashboard to access makefriends page<br/><br/>\n");
        printf("<form name=\"welcome page\" action=\"http://cs.mcgill.ca/~ytamit/index.html\">\n");
	printf("<input type=\"submit\" value=\"Back to Welcome Page\"> </form>\n");
	printf("<form name=\"dashboard\" action=\"http://cs.mcgill.ca/~djosep13/dashboard.py\" method=\"post\">\n");
	printf("<input type=\"hidden\" name=\"username\" value=\"%s\">\n", user);
	printf(" <input type=\"submit\" value=\"Back to my Dashboard\"></form>\n");
        printf("</body>\n");
        printf("</html>\n");
        
        return;
    }
    
    return;
}

// ------------------------------------------------------------------------------------------ //
//                                       THE END!
// ------------------------------------------------------------------------------------------ //





















