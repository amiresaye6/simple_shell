#include "shell.h"

int shellby_env(char **Aargs, char __attribute__((__unused__)) **Afront);
int shellby_setenv(char **Aargs, char __attribute__((__unused__)) **Afront);
int shellby_unsetenv(char **Aargs, char __attribute__((__unused__)) **Afront);

/**
 * shellby_env - Prints the current environment.
 * @Aargs: An array of arguments passed to the shell.
 * @Afront: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 */
int shellby_env(char **Aargs, char __attribute__((__unused__)) **Afront)
{
	int Aindex;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (Aindex = 0; environ[Aindex]; Aindex++)
	{
		write(STDOUT_FILENO, environ[Aindex], _strlen(environ[Aindex]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)Aargs;
	return (0);
}

/**
 * shellby_setenv - Changes or adds an environmental variable to the PATH.
 * @Aargs: An array of arguments passed to the shell.
 * @Afront: A double pointer to the beginning of args.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_setenv(char **Aargs, char __attribute__((__unused__)) **Afront)
{
	char **Aenv_var = NULL, **Anew_environ, *Anew_value;
	size_t Asize;
	int Aindex;

	if (!Aargs[0] || !Aargs[1])
		return (create_error(Aargs, -1));

	Anew_value = malloc(_strlen(Aargs[0]) + 1 + _strlen(Aargs[1]) + 1);
	if (!Anew_value)
		return (create_error(Aargs, -1));
	_strcpy(Anew_value, Aargs[0]);
	_strcat(Anew_value, "=");
	_strcat(Anew_value, Aargs[1]);

	Aenv_var = _getenv(Aargs[0]);
	if (Aenv_var)
	{
		free(*Aenv_var);
		*Aenv_var = Anew_value;
		return (0);
	}
	for (Asize = 0; environ[Asize]; Asize++)
		;

	Anew_environ = malloc(sizeof(char *) * (Asize + 2));
	if (!Anew_environ)
	{
		free(Anew_value);
		return (create_error(Aargs, -1));
	}

	for (Aindex = 0; environ[Aindex]; Aindex++)
		Anew_environ[Aindex] = environ[Aindex];

	free(environ);
	environ = Anew_environ;
	environ[Aindex] = Anew_value;
	environ[Aindex + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @Aargs: An array of arguments passed to the shell.
 * @Afront: A double pointer to the beginning of args.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_unsetenv(char **Aargs, char __attribute__((__unused__)) **Afront)
{
	char **Aenv_var, **Anew_environ;
	size_t Asize;
	int Aindex, Aindex2;

	if (!Aargs[0])
		return (create_error(Aargs, -1));
	Aenv_var = _getenv(Aargs[0]);
	if (!Aenv_var)
		return (0);

	for (Asize = 0; environ[Asize]; Asize++)
		;

	Anew_environ = malloc(sizeof(char *) * Asize);
	if (!Anew_environ)
		return (create_error(Aargs, -1));

	for (Aindex = 0, Aindex2 = 0; environ[Aindex]; Aindex++)
	{
		if (*Aenv_var == environ[Aindex])
		{
			free(*Aenv_var);
			continue;
		}
		Anew_environ[Aindex2] = environ[Aindex];
		Aindex2++;
	}
	free(environ);
	environ = Anew_environ;
	environ[Asize - 1] = NULL;

	return (0);
}
