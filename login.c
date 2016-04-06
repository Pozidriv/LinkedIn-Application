#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Verifies that the inputed username/password pair is in the database
int isValid(char *usr, char *pwd);

//displays the error page
void displayError(void);

//imported from https://www.cs.tut.fi/~jkorpela/forms/cgic.html
//translates the input into a readable format (with special characters still)
void unencode(char *src, char *last, char *dest);

int main()
{
	char input[500], data[500];
	char inputUsrname[51], inputPasswd[51];
	char *ptr;
	int a;
	int n = atoi(getenv("CONTENT_LENGTH"));

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<body>%d</body>", n);

	fgets(input, n+1, stdin);
	unencode(input, input+n, data);
	//good

	ptr = 5+strstr(data, "user=");
	for (a=0; *(ptr+a)!='&'; a++) {
		inputUsrname[a] = (char)*(ptr+a);//not sure this will work
	}

	ptr = 7+strstr(data, "passwd=");
	for (a=0; *(ptr+a)!='&'; a++) {
		inputPasswd[a] = (char)*(ptr+a); //not sure this will work
	}
	//at this point, we have the inputed password/username.

	if (isValid(inputUsrname, inputPasswd)) {
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

