#include "main.h"

/**
 * interactiveMode - returns true if shell is interactive mode
 * @info: struct specific address
 *
 * Reeturn: returns 1(true) if interactive mode,
 * 0 otherwise.
 */

int interactiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * charDelimCheck -Verifies whether a character is a delimiter.r
 * @c: The character to be checked.
 * @delim: The delimiter string.
 * Return: 1 if true, 0 if false
 */
int charDelimCheck(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *AlphabetCheck - Verifies if the character is alphabetic.
 *@c: The character to be inputted.
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int AlphabetCheck(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *strng2Int - Transforms a string into an integer.
 *@s: The string to undergo conversion.
 *Return: Returns 0 if there are no numbers in the string; otherwise,
 *provides the converted number.
 */

int strng2Int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

