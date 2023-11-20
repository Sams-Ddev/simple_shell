#include "main.h"

/**
 * **SplitStrg_in2 - Divides a string into individual words,
 * while repeated delimiters are disregarded.
 * @strg: The string that you want to split into words.
 * @d: The delimiter string that is used to separate or
 * split the input string into words.
 * Return: A reference to an array of strings is returned
 * if successful, and in case of failure, a NULL pointer is provided.
 */

char **SplitStrg_in2(char *strg, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; strg[i] != '\0'; i++)
		if (!chk_Delim(strg[i], d) && (chk_Delim(strg[i + 1], d) || !strg[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (chk_Delim(strg[i], d))
			i++;
		k = 0;
		while (!chk_Delim(strg[i + k], d) && strg[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = strg[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


/**
 * **SplitStrg_words - Divides a string into individual words.
 * @strg: The string that you want to split into words.
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **SplitStrg_words(char *strg, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	for (i = 0; strg[i] != '\0'; i++)
		if ((strg[i] != d && strg[i + 1] == d) ||
		    (strg[i] != d && !strg[i + 1]) || strg[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (strg[i] == d && strg[i] != d)
			i++;
		k = 0;
		while (strg[i + k] != d && strg[i + k] && strg[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = strg[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

