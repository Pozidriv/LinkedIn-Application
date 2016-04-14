/* Header file for decd_post */

/*
 * Translates the input into a readable format, from the address pointed to 
 * by src to the address pointed by last, and stores the result into dest.
 * (keeps the '&' and '=')
 *
 * Imported from https://www.cs.tut.fi/~jkorpela/forms/cgic.html
 */
void unencode(char *src, char *last, char *dest);

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
void getVariable(char *str, char *nameOfVar, char *dest);

