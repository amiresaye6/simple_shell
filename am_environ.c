#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *Avar);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **Anew_environ;
	size_t Asize;
	int Aindex;

	for (Asize = 0; environ[Asize]; Asize++)
		;

	Anew_environ = malloc(sizeof(char *) * (Asize + 1));
	if (!Anew_environ)
		return (NULL);

	for (Aindex = 0; environ[Aindex]; Aindex++)
	{
		Anew_environ[Aindex] = malloc(_strlen(environ[Aindex]) + 1);

		if (!Anew_environ[Aindex])
		{
			for (Aindex--; Aindex >= 0; Aindex--)
				free(Anew_environ[Aindex]);
			free(Anew_environ);
			return (NULL);
		}
		_strcpy(Anew_environ[Aindex], environ[Aindex]);
	}
	Anew_environ[Aindex] = NULL;

	return (Anew_environ);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int Aindex;

	for (Aindex = 0; environ[Aindex]; Aindex++)
		free(environ[Aindex]);
	free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @Avar: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *Avar)
{
	int Aindex, len;

	len = _strlen(Avar);
	for (Aindex = 0; environ[Aindex]; Aindex++)
	{
		if (_strncmp(Avar, environ[Aindex], len) == 0)
			return (&environ[Aindex]);
	}

	return (NULL);
}
