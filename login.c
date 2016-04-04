#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//displays the error page
void displayError(void);

//imported from https://www.cs.tut.fi/~jkorpela/forms/cgic.html
//translates the input into a readable format (with special characters still)
void unencode(char *src, char *last, char *dest);

int main()
{
	char input[300], data[300];
	char inputUsrname[51], inputPasswd[51];
	char *ptr;
	int a;
	int n = atoi(getenv("CONTENT_LENGTH"));

	fgets(input, n+1, stdin);
	unencode(input, input+n, data);

	ptr = 5+strstr(data, "user=");
	for (a=0; *(ptr+a)!='&'; a++) {
		inputUsrname[a] = *(ptr+a);//not sure this will work
	}

	ptr = 7+strstr(data, "passwd=");
	for (a=0; *(ptr+a)!='&'; a++) {
		inputPasswd[a] = *(ptr+a); //not sure this will work
	}
	
	if (strcmp(
	displayError();
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

