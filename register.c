#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

void displayError1() //Error page when fields left blank
{
	FILE *errorMessage;
	errorMessage = fopen("blankField.html", "r");

	char line[5000];
	while(fgets(line, 5000, errorMessage) != NULL)
		printf("%s", line);
	fclose(errorMessage);
}

void displayError2()
{
	FILE *errorMessage;
	errorMessage = fopen("nameTaken.html", "r");

	char line[5000];
	while(fgets(line, 5000, errorMessage) != NULL)
		printf("%s", line);
	fclose(errorMessage);
}

void displaySuccess()
{
	FILE *successPage;
	successPage = fopen("success.html", "r");

	char line[5000];
	while(fgets(line, 5000, successPage) != NULL)
		printf("%s", line);
	fclose(successPage);
}

int usernameTaken(char *username)
{
	FILE *fp;
	fp = fopen("users.txt", "r");

	char nextLine[5000];
	while(fgets(nextLine, 5000, fp) != NULL) //Until end of file
	{
		if(strcmp(username, nextLine) == 0)
		{
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		displayError1();
		return 1;
	}

	if(usernameTaken(argv[1]))
	{
		displayError2();
		return 2;
	}

	FILE *fp;
	fp = fopen("users.txt", "a");
	
	fprintf(fp, "%s\n%s\n%s\n%s\n", argv[1], argv[2], argv[3], argv[4]);
	fclose(fp);
	displaySuccess();
	return 0;
}
