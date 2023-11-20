#include "main.h"

/**
 * copyStrings - Duplicates a string.
 * @dest: The target location or buffer where the string will be copied to.
 * @src: The string that is being copied or the source from
 * which the data is being duplicated.
 *
 * Return: A reference or pointer to the destination
 * where the string is being copied.
 */
char *copyStrings(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * strgDuplicate - Creates a copy of a string.
 * @strg:The string that is being duplicated or cloned.
 *
 * Return:A reference or pointer to the duplicated string.
 */
char *strgDuplicate(const char *strg)
{
	int length = 0;
	char *ret;

	if (strg == NULL)
		return (NULL);
	while (*strg++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--strg;
	return (ret);
}

/**
 *printsInp_Strg -Outputs or displays an input string.
 *@strg: The string that you want to print or display.
 *
 * Return: Void (nothing)
 */
void printsInp_Strg(char *strg)
{
	int i = 0;

	if (!strg)
		return;
	while (strg[i] != '\0')
	{
		_putchar(strg[i]);
		i++;
	}
}

/**
 * _putchar - Outputs the character 'c' to the stdout.
 * @c: The character that you want to be printed.
 *
 * Return: On success 1.
 * In case of an error, a return value of -1 is provided, and
 * the error status (errno) is adjusted accordingly.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

