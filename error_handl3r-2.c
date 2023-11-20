#include "main.h"

/**
 * convStrg_to_int - Converts a string into an integer.
 * @s: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int convStrg_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printError_stdout - Prints an error message to the standard output.
 * @info: The struct containing info about parameters & return values.
 * @estr:A string indicating the specified error type.
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printError_stdout(info_r *info, char *estr)
{
	printStrg_input(info->prog_fileName);
	printStrg_input(": ");
	prints_decimal(info->line_count, STDERR_FILENO);
	printStrg_input(": ");
	printStrg_input(info->argv[0]);
	printStrg_input(": ");
	printStrg_input(estr);
}

/**
 * prints_decimal - function prints a decimal (int) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int prints_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = printChar_stderr;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * similar_itoa - Conversion function similar to `itoa`.
 * @numb: number
 * @base: base
 * @flags: Flags associated with an argument.
 *
 * Return: string
 */
char *similar_itoa(long int numb, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flags & CONV_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sign = '-';

	}
	array = flags & CONV_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comments_remover - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void comments_remover(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

