#include "shell.h"
int (*get_builtin(char *Acommand))(char **Aargs, char **Afront);
int shellby_exit(char **Aargs, char **Afront);
int shellby_cd(char **Aargs, char __attribute__((__unused__)) **Afront);
int shellby_help(char **Aargs, char __attribute__((__unused__)) **Afront);

/**
 * get_builtin - Matches a command with a corresponding
 *               shellby builtin function.
 * @Acommand: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *Acommand))(char **Aargs, char **Afront)
{
	builtin_t Afuncs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; Afuncs[i].Aname; i++)
	{
		if (_strcmp(Afuncs[i].Aname, Acommand) == 0)
			break;
	}
	return (Afuncs[i].f);
}

/**
 * shellby_exit - Causes normal process termination
 *                for the shellby shell.
 * @Aargs: An array of arguments containing the exit value.
 * @Afront: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value
 */
int shellby_exit(char **Aargs, char **Afront)
{
	int i, Alen_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (Aargs[0])
	{
		if (Aargs[0][0] == '+')
		{
			i = 1;
			Alen_of_int++;
		}
		for (; Aargs[0][i]; i++)
		{
			if (i <= Alen_of_int && Aargs[0][i] >= '0' && Aargs[0][i] <= '9')
				num = (num * 10) + (Aargs[0][i] - '0');
			else
				return (create_error(--Aargs, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--Aargs, 2));
	Aargs -= 1;
	free_args(Aargs, Afront);
	free_env();
	free_alias_list(Aaliases);
	exit(num);
}

/**
 * shellby_cd - Changes the current directory of the shellby process.
 * @Aargs: An array of arguments.
 * @Afront: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_cd(char **Aargs, char __attribute__((__unused__)) **Afront)
{
	char **Adir_info, *Anew_line = "\n";
	char *Aoldpwd = NULL, *Apwd = NULL;
	struct stat Adir;

	Aoldpwd = getcwd(Aoldpwd, 0);
	if (!Aoldpwd)
		return (-1);

	if (Aargs[0])
	{
		if (*(Aargs[0]) == '-' || _strcmp(Aargs[0], "--") == 0)
		{
			if ((Aargs[0][1] == '-' && Aargs[0][2] == '\0') ||
					Aargs[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(Aoldpwd);
				return (create_error(Aargs, 2));
			}
		}
		else
		{
			if (stat(Aargs[0], &Adir) == 0 && S_ISDIR(Adir.st_mode)
					&& ((Adir.st_mode & S_IXUSR) != 0))
				chdir(Aargs[0]);
			else
			{
				free(Aoldpwd);
				return (create_error(Aargs, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	Apwd = getcwd(Apwd, 0);
	if (!Apwd)
		return (-1);

	Adir_info = malloc(sizeof(char *) * 2);
	if (!Adir_info)
		return (-1);

	Adir_info[0] = "OLDPWD";
	Adir_info[1] = Aoldpwd;
	if (shellby_setenv(Adir_info, Adir_info) == -1)
		return (-1);

	Adir_info[0] = "PWD";
	Adir_info[1] = Apwd;
	if (shellby_setenv(Adir_info, Adir_info) == -1)
		return (-1);
	if (Aargs[0] && Aargs[0][0] == '-' && Aargs[0][1] != '-')
	{
		write(STDOUT_FILENO, Apwd, _strlen(Apwd));
		write(STDOUT_FILENO, Anew_line, 1);
	}
	free(Aoldpwd);
	free(Apwd);
	free(Adir_info);
	return (0);
}

/**
 * shellby_help - Displays information about shellby builtin commands.
 * @Aargs: An array of arguments.
 * @Afront: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_help(char **Aargs, char __attribute__((__unused__)) **Afront)
{
	if (!Aargs[0])
		help_all();
	else if (_strcmp(Aargs[0], "alias") == 0)
		help_alias();
	else if (_strcmp(Aargs[0], "cd") == 0)
		help_cd();
	else if (_strcmp(Aargs[0], "exit") == 0)
		help_exit();
	else if (_strcmp(Aargs[0], "env") == 0)
		help_env();
	else if (_strcmp(Aargs[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(Aargs[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(Aargs[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, Aname, _strlen(Aname));

	return (0);
}
