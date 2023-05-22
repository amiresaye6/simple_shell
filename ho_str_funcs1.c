#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *adest, const char *asrc);
char *_strcat(char *adest, const char *asrc);
char *_strncat(char *adest, const char *asrc, size_t n);

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length of the character string.
 */
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - Copies the string pointed to by asrc, including the
 *           terminating null byte, to the buffer pointed by des.
 * @adest: Pointer to the destination of copied string.
 * @asrc: Pointer to the src of the source string.
 *
 * Return: Pointer to adest.
 */
char *_strcpy(char *adest, const char *asrc)
{
	size_t i;

	for (i = 0; asrc[i] != '\0'; i++)
		adest[i] = asrc[i];
	adest[i] = '\0';
	return (adest);
}

/**
 * _strcat - Concantenates two strings.
 * @adest: Pointer to destination string.
 * @asrc: Pointer to source string.
 *
 * Return: Pointer to adestination string.
 */
char *_strcat(char *adest, const char *asrc)
{
	char *adestTemp;
	const char *asrcTemp;

	adestTemp = adest;
	asrcTemp =  asrc;

	while (*adestTemp != '\0')
		adestTemp++;

	while (*asrcTemp != '\0')
		*adestTemp++ = *asrcTemp++;
	*adestTemp = '\0';
	return (adest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @adest: Pointer to destination string.
 * @asrc: Pointer to source string.
 * @n: n bytes to copy from asrc.
 *
 * Return: Pointer to adestination string.
 */
char *_strncat(char *adest, const char *asrc, size_t n)
{
	size_t adest_len = _strlen(adest);
	size_t i;

	for (i = 0; i < n && asrc[i] != '\0'; i++)
		adest[adest_len + i] = asrc[i];
	adest[adest_len + i] = '\0';

	return (adest);
}
