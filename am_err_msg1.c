#include "shell.h"

char *error_env(char **Aargs);
char *error_1(char **Aargs);
char *error_2_exit(char **Aargs);
char *error_2_cd(char **Aargs);
char *error_2_syntax(char **Aargs);
/**
 * error_env - Creates an error message for shellby_env errors.
 * @Aargs: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_env(char **Aargs)
{
	char *Aerror, *Ahist_str;
	int len;

	Ahist_str = _itoa(Ahist);
	if (!Ahist_str)
		return (NULL);

	Aargs--;
	len = _strlen(Aname) + _strlen(Ahist_str) + _strlen(Aargs[0]) + 45;
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
	_strcat(Aerror, ":( Unable to add/remove from environment\n");

	free(Ahist_str);
	return (Aerror);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @Aargs: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **Aargs)
{
	char *Aerror;
	int len;

	len = _strlen(Aname) + _strlen(Aargs[0]) + 13;
	Aerror = malloc(sizeof(char) * (len + 1));
	if (!Aerror)
		return (NULL);

	_strcpy(Aerror, "alias: ");
	_strcat(Aerror, Aargs[0]);
	_strcat(Aerror, " not found\n");

	return (Aerror);
}

/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @Aargs: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **Aargs)
{
	char *Aerror, *Ahist_str;
	int len;

	Ahist_str = _itoa(Ahist);
	if (!Ahist_str)
		return (NULL);

	len = _strlen(Aname) + _strlen(Ahist_str) + _strlen(Aargs[0]) + 27;
	Aerror = malloc(sizeof(char) * (len + 1));
	if (!Aerror)
	{
		free(Ahist_str);
		return (NULL);
	}

	_strcpy(Aerror, Aname);
	_strcat(Aerror, ": ");
	_strcat(Aerror, Ahist_str);
	_strcat(Aerror, ": exit: Illegal number: ");
	_strcat(Aerror, Aargs[0]);
	_strcat(Aerror, "\n");

	free(Ahist_str);
	return (Aerror);
}

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @Aargs: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_cd(char **Aargs)
{
	char *Aerror, *Ahist_str;
	int len;

	Ahist_str = _itoa(Ahist);
	if (!Ahist_str)
		return (NULL);

	if (Aargs[0][0] == '-')
		Aargs[0][2] = '\0';
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
	if (Aargs[0][0] == '-')
		_strcat(Aerror, ": cd: Illegal option ");
	else
		_strcat(Aerror, ": cd: can't cd to ");
	_strcat(Aerror, Aargs[0]);
	_strcat(Aerror, "\n");

	free(Ahist_str);
	return (Aerror);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @Aargs: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **Aargs)
{
	char *Aerror, *Ahist_str;
	int len;

	Ahist_str = _itoa(Ahist);
	if (!Ahist_str)
		return (NULL);

	len = _strlen(Aname) + _strlen(Ahist_str) + _strlen(Aargs[0]) + 33;
	Aerror = malloc(sizeof(char) * (len + 1));
	if (!Aerror)
	{
		free(Ahist_str);
		return (NULL);
	}

	_strcpy(Aerror, Aname);
	_strcat(Aerror, ": ");
	_strcat(Aerror, Ahist_str);
	_strcat(Aerror, ": Syntax error: \"");
	_strcat(Aerror, Aargs[0]);
	_strcat(Aerror, "\" unexpected\n");

	free(Ahist_str);
	return (Aerror);
}
