#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "decd_post.h"

void displayError1() //Error page when fields left blank
{
	FILE *errorMessage;
	errorMessage = fopen("./blankField.html", "r");

	char line[5000];
	while(fgets(line, 5000, errorMessage) != NULL)
		printf("%s", line);
	fclose(errorMessage);
}

void displayError2() //Displays error page if a username is taken
{
	FILE *errorMessage;
	errorMessage = fopen("./nameTaken.html", "r");

	char line[5000];
	while(fgets(line, 5000, errorMessage) != NULL)
		printf("%s", line);
	fclose(errorMessage);
}

void displaySuccess() //displays page upon creation of valid account
{
	FILE *successPage;
	successPage = fopen("./success.html", "r");

	char line[5000];
	while(fgets(line, 5000, successPage) != NULL)
		printf("%s", line);
	fclose(successPage);
}

int usernameTaken(char *username) //checks if username is taken
{
	FILE *fp;
	fp = fopen("./users.txt", "r");

	char nextLine[5000];
	while(fgets(nextLine, 5000, fp) != NULL) //Until end of file
	{
		if(strcmp(username, nextLine) == 0)
		{
			fclose(fp);
			return 1;
		}
		//skips stuff that isn't usernames
		fgets(nextLine, 5000, fp);
		fgets(nextLine, 5000, fp);
		fgets(nextLine, 5000, fp);
	}
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[])
{
	//make the inputs readable
	char input[5000], data[5000];
	char username[5000], psswd[5000], jbdsc[5000], fullnm[5000];
	fgets(input, n+1, stdin);
	unencode(input, input + n, data);
	getVariable(data, "user", username);
	getVariable(data, "passswd", psswd);
	getVariable(data, "fullname", fullnm);
	getVariable(data, "jobdesc", jbdsc);
	
	//checks if any field left blank
	if(username == NULL || psswd == NULL || fullnm == NULL || jbdsc == NULL)
	{
		displayError1();
		return 1;
	}

	//responds to taken usernames
	if(usernameTaken(username))
	{
		displayError2();
		return 2;
	}

	//everything is cool, time to put that in the list!
	FILE *fp;
	fp = fopen("./users.txt", "a");
	
	//adds all variables on different lines
	fprintf(fp, "%s\n%s\n%s\n%s\n", username, psswd, fullnm, jbdsc);
	fclose(fp);
	displaySuccess();
	return 0;
}
