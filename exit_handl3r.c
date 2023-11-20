#include "main.h"

/**
 **copyG_strg - Copies a given string.
 *@dest: The string to which the contents will be copied.
 *@src:The original string from which the contents will be copied.
 *@n: The number of characters to be copied.
 *Return: The string obtained by combining or concat two or more strings.
 */
char *copyG_strg(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **Strg2cat -Concatenates two strings..
 *@dest: The initial or first string.
 *@src: The subsequent or second string.
 *@n: The maximum number of bytes to be utilized.
 *Return: the concatenated string
 */
char *Strg2cat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **findChar_inStrg -Finds a character within a string.
 *@s:The string intended for parsing.
 *@c: The specific character being searched for.
 *Return: (s) a pointer to the memory area s
 */
char *findChar_inStrg(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

