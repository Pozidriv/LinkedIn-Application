#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "decd_post.h"

/************************************************************************/

//Verifies that the inputed username/password pair is in the database
//Tested, works well
int isValid(char *usr, char *pwd);

//displays the error page
void displayError(void);

/*************************************************************************/


int main(int argc, char *argv[])
{
	char input[5000], data[5000];
	char inputUsrname[51], inputPasswd[51];
	char *ptr;
	//char *arr[1];
	int n;

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);

	/*************FOR TESTING ONLY*******************/
	//setenv("CONTENT_LENGTH", "18", 1);
	/************************************************/


	//-----Checking if form data exists-----

	if (getenv("CONTENT_LENGTH") != NULL) {
		n = atoi(getenv("CONTENT_LENGTH"));
	} else {
		displayError();
		return;
	}

	//--------------------------------------


	//--------Retrieving form data----------

	fgets(input, n + 1, stdin);
	unencode(input, input + n, data);

	//--------------------------------------

	//printf("%s\n", data);//debugging

	//------Retrieving variable values------

	getVariable(data, "user", inputUsrname);
	//printf("<br>we have user %s\n", inputUsrname);//debugging
	getVariable(data, "passwd", inputPasswd);
	//printf("<br>we have pass %s\n", inputPasswd);//debugging
	//at this point, we have the inputed password/username.

	//--------------------------------------


	//------Checking user/password pair-----

	printf("usr: %s; pwd: %s", inputUsrname, inputPasswd);//debugging
	if (isValid(inputUsrname, inputPasswd)) {
		//printf("user/pass valid\n");//debugging
		setenv("usr", inputUsrname, 1);
		system("./dashboard.cgi $usr");
		//arr[0] = inputUsrname;
		//execv("./dashboard.cgi", arr);
	} else displayError();

	//--------------------------------------

	//displayError();//debugging

	return 0;
}

/*
 * Compares usr with each username in users.txt
 * If they are the same, it compares the password of that username and pwd,
 * and returns 1 if they are the same, else returns 0.
 * If it is not the same, it continues until it reaches the end of file.
 ****** 
 * ptr is used because getline takes a pointer to string as input.
 ***
 * in the while loop, strncmp is used because getline includes the \n char
 * when copying the line into line. We thus consider only the first strlen(line)-1
 * characters to make sure the actual username is being compared. 
 ***
 * the string length is also compared to make sure the strings really are the same
 */
int isValid(char *usr, char *pwd)
{
	char *ptr;
	char line[100];
	size_t n = 99;
	FILE *f;

	ptr = line;

	f = fopen("../users.txt", "rt");

	while (fgets(ptr, n, f) > 0) {
		//printf("line: %s\n", line);//debugging
                if (strncmp(line, usr, strlen(line)-1) == 0
		  && strlen(line)-1 == strlen(usr)
		) {
			//printf("usr is the same\n");//debugging
			fgets(ptr, n, f);
			if (strncmp(line, pwd, strlen(line)-1) == 0
			  && strlen(line) == strlen(pwd)
			) {
				//printf("pwd is the same");//debugging
                        	fclose(f);
                        	return 1;
			} else {
				fclose(f);
				return 0;
			}
                } else {
                        fgets(ptr, n, f);
                        fgets(ptr, n, f);
                        fgets(ptr, n, f);
                        // user.txt has 4 lines per user :P
                }
        }
        fclose(f);
	return 0;
}

void displayError(void)
{

	//printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<head>\n<title>Authentification Failed</title>\n");
	printf("<link href=\"http://cs.mcgill.ca/~ytamit/global.css\" rel=\"stylesheet\" type=\"text/css\">\n");
	printf("</head>\n\n<body>\n");
	printf("<h1>Error</h1>\n");
	printf("<p>The credentials you have entered are invalid.<br>\n");
	printf("Please try again by clicking ");
	printf("<a href=\"http://cs.mcgill.ca/~ytamit/login.html\">here</a>, or ");
	printf("go back to the <a href=\"../index.html\">Home Page</a>\n");
	printf("</body>\n");
	
	return;
}

