#include "shell.h"

char *get_args(char *aline, int *aexe_ret);
int call_args(char **args, char **afront, int *aexe_ret);
int run_args(char **args, char **afront, int *aexe_ret);
int handle_args(int *aexe_ret);
int check_args(char **args);

/**
 * get_args - Gets a command from standard input.
 * @aline: A buffer to store the command.
 * @aexe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_args(char *aline, int *aexe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (aline)
		free(aline);

	read = _getline(&aline, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		Ahist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(aline, aexe_ret));
	}

	aline[read - 1] = '\0';
	variable_replacement(&aline, aexe_ret);
	handle_line(&aline, read);

	return (aline);
}

/**
 * call_args - Partitions operators from commands and calls them.
 * @aargs: An array of arguments.
 * @afront: A double pointer to the beginning of aargs.
 * @aexe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_args(char **aargs, char **afront, int *aexe_ret)
{
	int ret, index;

	if (!aargs[0])
		return (*aexe_ret);
	for (index = 0; aargs[index]; index++)
	{
		if (_strncmp(aargs[index], "||", 2) == 0)
		{
			free(aargs[index]);
			aargs[index] = NULL;
			aargs = replace_aliases(aargs);
			ret = run_args(aargs, afront, aexe_ret);
			if (*aexe_ret != 0)
			{
				aargs = &aargs[++index];
				index = 0;
			}
			else
			{
				for (index++; aargs[index]; index++)
					free(aargs[index]);
				return (ret);
			}
		}
		else if (_strncmp(aargs[index], "&&", 2) == 0)
		{
			free(aargs[index]);
			aargs[index] = NULL;
			aargs = replace_aliases(aargs);
			ret = run_args(aargs, afront, aexe_ret);
			if (*aexe_ret == 0)
			{
				aargs = &aargs[++index];
				index = 0;
			}
			else
			{
				for (index++; aargs[index]; index++)
					free(aargs[index]);
				return (ret);
			}
		}
	}
	aargs = replace_aliases(aargs);
	ret = run_args(aargs, afront, aexe_ret);
	return (ret);
}

/**
 * run_args - Calls the execution of a command.
 * @aargs: An array of arguments.
 * @afront: A double pointer to the beginning of aargs.
 * @aexe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **aargs, char **afront, int *aexe_ret)
{
	int ret, i;
	int (*builtin)(char **aargs, char **afront);

	builtin = get_builtin(aargs[0]);

	if (builtin)
	{
		ret = builtin(aargs + 1, afront);
		if (ret != EXIT)
			*aexe_ret = ret;
	}
	else
	{
		*aexe_ret = execute(aargs, afront);
		ret = *aexe_ret;
	}

	Ahist++;

	for (i = 0; aargs[i]; i++)
		free(aargs[i]);

	return (ret);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @aexe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_args(int *aexe_ret)
{
	int ret = 0, index;
	char **aargs, *aline = NULL, **afront;

	aline = get_args(aline, aexe_ret);
	if (!aline)
		return (END_OF_FILE);

	aargs = _strtok(aline, " ");
	free(aline);
	if (!aargs)
		return (ret);
	if (check_args(aargs) != 0)
	{
		*aexe_ret = 2;
		free_args(aargs, aargs);
		return (*aexe_ret);
	}
	afront = aargs;
	for (index = 0; aargs[index]; index++)
	{
		if (_strncmp(aargs[index], ";", 1) == 0)
		{
			free(aargs[index]);
			aargs[index] = NULL;
			ret = call_args(aargs, afront, aexe_ret);
			aargs = &aargs[++index];
			index = 0;
		}
	}
	if (aargs)
		ret = call_args(aargs, afront, aexe_ret);

	free(afront);
	return (ret);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @aargs: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_args(char **aargs)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; aargs[i]; i++)
	{
		cur = aargs[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&aargs[i], 2));
			nex = aargs[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&aargs[i + 1], 2));
		}
	}
	return (0);
}
