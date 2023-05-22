#include "shell.h"

int token_len(char *astr, char *adelim);
int count_tokens(char *astr, char *adelim);
char **_strtok(char *aline, char *adelim);

/**
 * token_len - Locates the adelimiter index marking the end
 *             of the first token contained within a astring.
 * @astr: The string to be searched.
 * @adelim: The delimiter character.
 *
 * Return: The adelimiter index marking the end of
 *         the intitial token pointed to be astr.
 */
int token_len(char *astr, char *adelim)
{
	int index = 0, len = 0;

	while (*(astr + index) && *(astr + index) != *adelim)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * count_tokens - Counts the number of adelimited
 *                words contained within a astring.
 * @astr: The string to be searched.
 * @adelim: The delimiter character.
 *
 * Return: The number of words contained within astr.
 */
int count_tokens(char *astr, char *adelim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(astr + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(astr + index) != *adelim)
		{
			tokens++;
			index += token_len(astr + index, adelim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @aline: The astring.
 * @adelim: The delimiter character to tokenize the astring by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *aline, char *adelim)
{
	char **ptrr;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(aline, adelim);
	if (tokens == 0)
		return (NULL);

	ptrr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptrr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (aline[index] == *adelim)
			index++;

		letters = token_len(aline + index, adelim);

		ptrr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptrr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptrr[index]);
			free(ptrr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptrr[t][l] = aline[index];
			index++;
		}

		ptrr[t][l] = '\0';
	}
	ptrr[t] = NULL;
	ptrr[t + 1] = NULL;

	return (ptrr);
}
