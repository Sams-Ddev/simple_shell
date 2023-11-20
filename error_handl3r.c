#include "main.h"

/**
 *printStrg_input - prints the string thats  inputed
 * @strg: The string to be displayed or printed.
 *
 * Return: Nothing
 */
void printStrg_input(char *strg)
{
	int i;
	/* Check if the input pointer strg is NULL*/
	if (!strg)
		return;

	/* Iterate through the characters in the string using a for loop*/
	for (i = 0; strg[i] != '\0'; i++)
	{
		/* Call the printChar_stderr function to print the current char*/
		printChar_stderr(strg[i]);
	}
}
/*---------------------------------------------------------------------*/

/**
 * printChar_stderr - Writes the character 'c' to the standard error (stderr).
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1The function returns, and errno is set to the appropriate value.
 */

int printChar_stderr(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	/* Continue processing characters until a flush condition is met*/
	while (c != BUFFER_FLUSH && i < WRITE_BUFFER_SIZE)
	{
		/* If the char is not a flush trigger */
		buffer[i++] = c;
	}

	/* Check if a flush condition is met and flush the buffer if needed*/
	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	/* Return 1 to indicate that one character has been processed*/
	return (1);
}

/*---------------------------------------------------------------------------*/
/**
 * printChar_fd - Writes the character 'c' to the
 * specified file descriptor (fd).
 * @c: The character to be printed.
 * @fd: The filedescriptor to be written to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printChar_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];
	int j;

	if (c == BUFFER_FLUSH || i == WRITE_BUFFER_SIZE)
	{
		for (j = 0; j < i; ++j)
		{
			write(fd, &buf[j], 1);
			i = 0;
		}
	}
	if (c != BUFFER_FLUSH)
	{
		buf[i] = c;
		++i;
	}
	return (1);
}
/*---------------------------------------------------------------*/
/**
 *printInp_strg - Prints a given input string.
 * @strg: string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int printInp_strg(char *strg, int fd)
{
	int i = 0;

	/*Iterate through the characters in the string using a for loop*/
	if (!strg)
		return (0);
	for (; *strg; strg++)
		i += printChar_fd(*strg++, fd);

	return (i);
}
/*------------------------------------------------------------------*/
