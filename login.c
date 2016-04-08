#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "decd_post.h"

/************************************************************************/

//Verifies that the inputed username/password pair is in the database
int isValid(char *usr, char *pwd);

//displays the error page
void displayError(void);

/*************************************************************************/


int main(int argc, char *argv[])
{
	char input[5000], data[5000];
	char inputUsrname[51], inputPasswd[51];
	char *ptr;
	int a,n;

	/*************FOR TESTING ONLY*******************/
	//setenv("CONTENT_LENGTH", "18", 1);
	/************************************************/

	if (getenv("CONTENT_LENGTH") != NULL) {
		n = atoi(getenv("CONTENT_LENGTH"));
	}
	else {
		printf("Form data does not exist!\n");
		return;
	}

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<body>%d<br>\n", n);

	fgets(input, n+1, stdin);
	unencode(input, input+n, data);
	data[n] = 0;
	printf("%s<body>\n", data);


	getVariable(data, "user", inputUsrname);
	printf("<br>we have user\n");
	getVariable(data, "passwd", inputPasswd);
	printf("<br>we have pass\n");
	//should be good up to here
	//at this point, we have the inputed password/username.

	if (isValid(inputUsrname, inputPasswd)) {
		printf("user/pass valid\n");
		setenv("usr", inputUsrname, 1);
		system("./cgi-bin/dashboard.cgi $usr");
	}
	else displayError();

	return 0;
}

int isValid(char *usr, char *pwd)
{
	char *ptr;
	char line[100];
	FILE *f;

	f = fopen("./users.txt", "rt");
	fgets(line, 99, f);

	while (line != 0) {
		if (strcmp(line, usr) == 0) return 1;
		else {
			fgets(line, 99, f);
			fgets(line, 99, f);
			fgets(line, 99, f);
			fgets(line, 99, f);
			// user.txt has 4 lines per user :P
		}
	}
	return 0;
}

void displayError(void)
{

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<head>\n<title>Authentification Failed</title>\n");
	printf("<link href=\"http://cs.mcgill.ca/~ytamit/global.css\" rel=\"stylesheet\" type=\"text/css\">\n");
	printf("</head>\n\n<body>\n");
	printf("<h1>Error</h1>\n");
	printf("<p>The credentials you have entered are invalid.<br>\n");
	printf("Please try again by clicking ");
	printf("<a href=\"login.html\">here</a>, or go ");
	printf("back to the <a href=\"index.html\">Home Page</a>\n");
	printf("</body>\n");
}

