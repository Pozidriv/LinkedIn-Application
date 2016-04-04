#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//displays the error page
void displayError(void);

int main()
{
	char *username = "thisisausername";
	
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
