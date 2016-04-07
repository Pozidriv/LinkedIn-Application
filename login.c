#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Verifies that the inputed username/password pair is in the database
int isValid(char *usr, char *pwd);

//SEG FAULT IN THIS FUNCTION
void getVariable(char *str, char *nameOfVar, char *dest);

//displays the error page
void displayError(void);

//imported from https://www.cs.tut.fi/~jkorpela/forms/cgic.html
//translates the input into a readable format (with special characters still)
void unencode(char *src, char *last, char *dest);

int main(int argc, char *argv[])
{
	char input[5000], data[5000];
	char inputUsrname[51], inputPasswd[51];
	char *ptr;
	int a,n;

	/*************FOR TESTING ONLY*******************/
	setenv("CONTENT_LENGTH", "18", 1);
	/************************************************/

	if (getenv("CONTENT_LENGTH") != NULL) {
		n = atoi(getenv("CONTENT_LENGTH"));
	}
	else {
		printf("Form data does not exist!\n");
		return;
	}

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<body>%d</body>\n", n);

	//NOTE: we read from INPUT, ie what the user types
	memcpy(input, argv[0], n+1);
	input[n+1] = 0;
	unencode(input, &input[n], data);
	//good up to here

	getVariable(input, "user", inputUsrname);
	printf("we have user\n");
	getVariable(input, "passwd", inputPasswd);
	printf("we have pass\n");
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

void unencode(char *src, char *last, char *dest)
{
 for(; src != last; src++, dest++)
   if(*src == '+')
     *dest = ' ';
   else if(*src == '%') {
     int code;
     if(sscanf(src+1, "%2x", &code) != 1) code = '?';
     *dest = code;
     src +=2; }
   else
     *dest = *src;
 *dest = '\n';
 *++dest = '\0';
}

/*
 * Input: str, a string in cgi encoding format
 * 	  nameOfVar, a string representing the name of the variable
 * 	  dest, the array where the obtained variable value will be stored
 *
 * The function fills dest with the value of the variable whose name is given 
 * in nameOfVar and value contained in str.
 * It does the following: strstr to find the variable name in 
 * str, read the value after the =, copy it to dest.
 * NOTE: if the value name is not in str, it puts a null in dest.
 * IMPORTANT: dest needs to be empty
 *
 ***************************MAKE A LIBRARY***************************
 */
void getVariable(char *str, char *varName, char *dest)
{
	char *ptr, *tmp;
	int sizeVar = strlen(varName) + 1;// +1 for the '=' char
	char var[sizeVar + 1];

	printf("memcpy");
	memcpy(var, varName, sizeVar-2);
	var[sizeVar-1] = '=';
	var[sizeVar] = 0;
	//we now have a string of the form "variable="

	ptr = strstr(str, var) + sizeVar;
	tmp = ptr;
	while (*ptr != '&') {
		strncat(dest, ptr, 1);
	}
	dest[ptr-tmp+1] = 0; //this line might be problematic
}
