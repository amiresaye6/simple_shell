#include "shell.h"

void free_args(char **Aargs, char **Afront);
char *get_pid(void);
char *get_env_value(char *Abeginning, int Alen);
void variable_replacement(char **Aargs, int *Aexe_ret);

/**
 * free_args - Frees up memory taken by args.
 * @Aargs: A null-terminated double pointer containing commands/arguments.
 * @Afront: A double pointer to the beginning of args.
 */
void free_args(char **Aargs, char **Afront)
{
	size_t i;

	for (i = 0; Aargs[i] || Aargs[i + 1]; i++)
		free(Aargs[i]);

	free(Afront);
}

/**
 * get_pid - Gets the current process ID.
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *Abuffer;
	ssize_t Afile;

	Afile = open("/proc/self/stat", O_RDONLY);
	if (Afile == -1)
	{
		perror("Cant read file ):");
		return (NULL);
	}
	Abuffer = malloc(120);
	if (!Abuffer)
	{
		close(Afile);
		return (NULL);
	}
	read(Afile, Abuffer, 120);
	while (Abuffer[i] != ' ')
		i++;
	Abuffer[i] = '\0';

	close(Afile);
	return (Abuffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @Abeginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *Abeginning, int len)
{
	char **Avar_addr;
	char *Areplacement = NULL, *Atemp, *Avar;

	Avar = malloc(len + 1);
	if (!Avar)
		return (NULL);
	Avar[0] = '\0';
	_strncat(Avar, Abeginning, len);

	Avar_addr = _getenv(Avar);
	free(Avar);
	if (Avar_addr)
	{
		Atemp = *Avar_addr;
		while (*Atemp != '=')
			Atemp++;
		Atemp++;
		Areplacement = malloc(_strlen(Atemp) + 1);
		if (Areplacement)
			_strcpy(Areplacement, Atemp);
	}

	return (Areplacement);
}

/**
 * variable_replacement - Handles variable replacement.
 * @Aline: A double pointer containing the command and arguments.
 * @Aexe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **Aline, int *Aexe_ret)
{
	int j, k = 0, len;
	char *Areplacement = NULL, *Aold_line = NULL, *Anew_line;

	Aold_line = *Aline;
	for (j = 0; Aold_line[j]; j++)
	{
		if (Aold_line[j] == '$' && Aold_line[j + 1] &&
				Aold_line[j + 1] != ' ')
		{
			if (Aold_line[j + 1] == '$')
			{
				Areplacement = get_pid();
				k = j + 2;
			}
			else if (Aold_line[j + 1] == '?')
			{
				Areplacement = _itoa(*Aexe_ret);
				k = j + 2;
			}
			else if (Aold_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; Aold_line[k] &&
						Aold_line[k] != '$' &&
						Aold_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				Areplacement = get_env_value(&Aold_line[j + 1], len);
			}
			Anew_line = malloc(j + _strlen(Areplacement)
					  + _strlen(&Aold_line[k]) + 1);
			if (!Aline)
				return;
			Anew_line[0] = '\0';
			_strncat(Anew_line, Aold_line, j);
			if (Areplacement)
			{
				_strcat(Anew_line, Areplacement);
				free(Areplacement);
				Areplacement = NULL;
			}
			_strcat(Anew_line, &Aold_line[k]);
			free(Aold_line);
			*Aline = Anew_line;
			Aold_line = Anew_line;
			j = -1;
		}
	}
}
