#include "shell.h"

char *_strchr(char *ss, char cc);
int _strspn(char *ss, char *aaccept);
int _strcmp(char *as1, char *as2);
int _strncmp(const char *as1, const char *as2, size_t n);

/**
 * _strchr - Locates a character in a string.
 * @ss: The string to be searched.
 * @cc: The character to be located.
 *
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */
char *_strchr(char *ss, char cc)
{
	int index;

	for (index = 0; ss[index]; index++)
	{
		if (ss[index] == cc)
			return (ss + index);
	}

	return (NULL);
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @ss: The string to be searched.
 * @aaccept: The prefix to be measured.
 *
 * Return: The number of abytes in s which
 *         consist only of abytes from aaccept.
 */
int _strspn(char *ss, char *aaccept)
{
	int abytes = 0;
	int index;

	while (*ss)
	{
		for (index = 0; aaccept[index]; index++)
		{
			if (*ss == aaccept[index])
			{
				abytes++;
				break;
			}
		}
		ss++;
	}
	return (abytes);
}

/**
 * _strcmp - Compares two strings.
 * @as1: The first string to be compared.
 * @as2: The second string to be compared.
 *
 * Return: Positive byte difference if as1 > as2
 *         0 if as1 = as2
 *         Negative byte difference if as1 < as2
 */
int _strcmp(char *as1, char *as2)
{
	while (*as1 && *as2 && *as1 == *as2)
	{
		as1++;
		as2++;
	}

	if (*as1 != *as2)
		return (*as1 - *as2);

	return (0);
}

/**
 * _strncmp - Compare two strings.
 * @as1: Pointer to a string.
 * @as2: Pointer to a string.
 * @n: The first n abytes of the strings to compare.
 *
 * Return: Less than 0 if as1 is shorter than as2.
 *         0 if as1 and as2 match.
 *         Greater than 0 if as1 is longer than as2.
 */
int _strncmp(const char *as1, const char *as2, size_t n)
{
	size_t i;

	for (i = 0; as1[i] && as2[i] && i < n; i++)
	{
		if (as1[i] > as2[i])
			return (as1[i] - as2[i]);
		else if (as1[i] < as2[i])
			return (as1[i] - as2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
