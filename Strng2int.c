#include "main.h"
#include <stdbool.h>

/**
 * interative_chk - returns true(1) if the shell is in interactive mode.
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interative_chk(info_r *info)
{
	return (isatty(STDIN_FILENO) && info->readInput_fd <= 2);
}
/*################################################################*/
/**
 * chk_Delim - checks if the character is a delimeter
 * @c: the char to check
 * @delim: The delimeter string
 * Return: 1 if true, 0 if false
 */

bool chk_Delim(char c, const char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
		{
			return (true); /* Return 1,character matches any delim*/
		}
		delim++; /* Move to the next character in the delimiter string*/
	}
	return (false); /* Character is not a delimiter*/
}
/*###################################################################*/

/*--------other handling functions--------------*/

/**
 *verify_alph - Verifies if a character is alphabetic.
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int verify_alph(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1); /*Char within the ASCII range of uppercase or lowercase*/
	else
		return (0);
}
/*##################################################################*/
/**
 *strg_to_int - Converts a string into an integer.
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int strg_to_int(char *s)
{
	int sign = 1, result = 0;
	int i = 0;

	while (s[i] == ' ' || s[i] == '\t')
	{
		i++; /* Skipping any leading whitespace*/
	}

	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}

	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}

	return (sign * result);
}
/*###########################################################################*/
