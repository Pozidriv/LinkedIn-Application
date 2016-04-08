#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ------------------------------------------------------------------------


void getFriends(char *user);
void gotoFriend(char *friend);
void listFriends(int i);


// ------------------------------------------------------------------------

int main(int argc, char *argv[]){
    
    if(argc==1){
        int length = atoi(getenv("CONTENT_LENGTH"));
        char user[60];
        char friend[60];
        char c;
        int i = 0;
        int f = 0;
        
        int numarg = 1;
        
        while ((c = getchar()) != EOF && i<length) {
            if (i < 200) {
                if (c!='+' && numarg==1) {
                    user[i]=c;
                }
                else if (c=='+' && numarg>1){
                    friend[i]='\0';
                    numarg++;
                }
                
                else if (c!='+' && numarg==2) {
                    user[f]=c;
                    f++;
                }
                else if (c=='+' && numarg==2){
                    friend[f]='\0';
                    numarg++;
                    f++;
                }
                else if(numarg>2){
                    return EXIT_FAILURE;
                }
                
                i++;
            }
        }
        
        friend[f] ='\0';
        
        if(numarg==1){
            getFriends(user);
        }
        
        else if(numarg==2){
            gotoFriend(friend);
        }
        
    }
    
// For testing purpose (on my computer)
    else if(argc==2){
        getFriends(argv[1]);
    }
	
    else if(argc==3){
        gotoFriend(argv[2]);
    }

    return EXIT_SUCCESS;

}

// ------------------------------------------------------------------------

void getFriends(char *user){


	FILE *file_ptr;
	char line[2048];
	char *name;
	int i = 0;
	file_ptr = fopen("friends.txt", "rt");
		
		// just in case...

		if (file_ptr==NULL){
			printf("Content-Type:text/html\n\n");
        		printf("<html>");

			printf("<body>Error. The filename does not exist. Please try again. \n </body>");
			printf("</html>");

			return;
		}


	while(!feof(file_ptr)){

		fgets(line, 2047, file_ptr);
	
		name = strtok(line, ",");
	
		if(strcmp(name, user)!=0){
			i++;
			continue;
		}

		else {	
			fclose(file_ptr);
			listFriends(i);
			return;
		}
	}


}


// ------------------------------------------------------------------------

void listFriends(int i){

	FILE *friend_ptr;
    FILE *html_ptr;
    char friends[2048];
    char html[300];
    char *friend;
    int html_line = 1;

    friend_ptr = fopen("friends.txt", "rt");
    html_ptr = fopen("seefriends.html", "rt");

	fgets(friends, 2047, friend_ptr);

        while(i){

                fgets(friends, 2047, friend_ptr);
                i--;
        }

	strtok(friends,",");
	friend = strtok(NULL,",");


	printf("<font color=\"ligthblue\" \"Content-Type:text/html\n\n </font>");
    
    while(html_line<=14){
        
        fgets(html, 2047, html_ptr);
        printf("%s\n",html);
        html_line++;
    }
    

//	printf("<form name=\"input\" action=\"seefriends.cgi user friend\" method = post> ");


	while(friend != NULL){

		printf("<input type=\"radio\" name=\"friend\" value=\"dahana %s\"><font face=\"arial\"><font size=\"5\"><b>&nbsp;&nbsp;%s</b></font><br/>",friend,friend);
	
		friend = strtok(NULL,",");

	}

    while(html_line<=21 || !feof(html_ptr)){
        
        fgets(html, 2047, html_ptr);
        printf("%s\n",html);
        html_line++;
    }

	fclose(friend_ptr);
    fclose(html_ptr);

}


//---------------------------------------------------------------------------


void gotoFriend(char *friend){
    

    FILE *html_ptr;
    char html_line[300];
    int html_index = 1;
    
    html_ptr = fopen("seefriends.html", "rt");

    printf("<font color=\"ligthblue\" \"Content-Type:text/html\n\n </font>");
    
    while(html_index<=33){
        
        if(html_index<23){
            fgets(html_line, 2047, html_ptr);
            html_index++;
        }
        
        else {
            printf("%s\n",html_line);
            fgets(html_line, 2047, html_ptr);
            html_index++;
        }
    }
    
    printf("<a href=\"http://www.cs.mcgill.ca/~djosep13/%s.html\" target=\"_self\"><br/><br/><font face=\"arial\"><font size=\"5\">See %s's page</font></a>", friend, friend);

    while(!feof(html_ptr)){
        printf("%s\n",html_line);
        fgets(html_line, 2047, html_ptr);
    }
    
    fclose(html_ptr);
    return;
    

}

// ------------------------------------------------------------------------











	







