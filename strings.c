#include "main.h"

/**
 * strLen - Provides the length of a string.
 * @s: The string for which you want to determine the length.
 *
 * Return:The numeric value representing the length of the string.
 */
int strLen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * lex_StrgCmp - Performs a lexicographic comparison of two strings..
 * @s1:The first string to be compared lexicographically.
 * @s2:The 2nd string to be compared lexicographically.
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int lex_StrgCmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * ChkStart_haystk - Verifies whether the "needle" starts with the "haystack."
 * @haystack: The string you want to search, often referred to as the "needle."
 * @needle: The substring you are looking to locate or find,
 * typically referred to as the "needle."
 *
 * Return: The address of the next character in the "haystack," or
 * NULL if there are no more chars left to search for in the "needle."
 */
char *ChkStart_haystk(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * Cat_2Strgs - Combines or joins two strings together.
 * @dest: The buffer where the combined strgs will be stored.
 * @src:The buffer or string that is being appended or
 * concatenated to the destination buffer.
 *
 * Return:A reference or pointer to the destination buffer
 * where the strings are being concatenated.
 */
char *Cat_2Strgs(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

