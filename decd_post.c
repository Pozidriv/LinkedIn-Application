#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/***************************************************************/

void getVariable(char *str, char *nameOfVar, char *dest);

void unencode(char *src, char *last, char *dest);

/***************************************************************/

/*
 * Input: str, a string in cgi encoding format
 *        nameOfVar, a string representing the name of the variable
 *        dest, the array where the obtained variable value will be stored
 *
 * The function fills dest with the value of the variable whose name is given 
 * in nameOfVar and value contained in str.
 * It does the following: strstr to find the variable name in 
 * str, read the value after the =, copy it to dest.
 * NOTE: if the value name is not in str, it puts a null in dest.
 * IMPORTANT: dest needs to be empty
 *
 * TESTED, works well.
 */
void getVariable(char *str, char *varName, char *dest)
{
        char *ptr, *tmp;
        int sizeVar = strlen(varName)+1;// +1 for the '=' char
        char var[sizeVar + 2];

        strncpy(var, varName, sizeVar);
        strncat(var, "=", 1);
        var[sizeVar+1] = 0;
        //we now have a string of the form "variable="

        if (strstr(str, var) == 0) return;

        ptr = strstr(str, var) + sizeVar;
        tmp = ptr;

        while (*ptr != '&' && *ptr != 0){
                strncat(dest, ptr, 1);
                ptr++; //AGAIN DO NOT FORGET THIS LINE
        }
        dest[ptr-tmp+1] = 0;
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
     src +=2;
   }
   else
     *dest = *src;
 *dest = '\n';
 *++dest = '\0';
}

