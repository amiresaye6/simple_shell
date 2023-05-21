#include "shell.h"

char *error_126(char **Aargs);
char *error_127(char **Aargs);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @Aargs: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **Aargs)
{
	char *Aerror, *Ahist_str;
	int len;

	Ahist_str = _itoa(Ahist);
	if (!Ahist_str)
		return (NULL);

	len = _strlen(Aname) + _strlen(Ahist_str) + _strlen(Aargs[0]) + 24;
	Aerror = malloc(sizeof(char) * (len + 1));
	if (!Aerror)
	{
		free(Ahist_str);
		return (NULL);
	}

	_strcpy(Aerror, Aname);
	_strcat(Aerror, ": ");
	_strcat(Aerror, Ahist_str);
	_strcat(Aerror, ": ");
	_strcat(Aerror, Aargs[0]);
	_strcat(Aerror, ": Permission denied\n");

	free(Ahist_str);
	return (Aerror);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @Aargs: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127(char **Aargs)
{
	char *Aerror, *Ahist_str;
	int len;

	Ahist_str = _itoa(Ahist);
	if (!Ahist_str)
		return (NULL);

	len = _strlen(Aname) + _strlen(Ahist_str) + _strlen(Aargs[0]) + 16;
	Aerror = malloc(sizeof(char) * (len + 1));
	if (!Aerror)
	{
		free(Ahist_str);
		return (NULL);
	}

	_strcpy(Aerror, Aname);
	_strcat(Aerror, ": ");
	_strcat(Aerror, Ahist_str);
	_strcat(Aerror, ": ");
	_strcat(Aerror, Aargs[0]);
	_strcat(Aerror, ": not found\n");

	free(Ahist_str);
	return (Aerror);
}
