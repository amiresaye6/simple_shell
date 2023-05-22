#include "shell.h"

char *fill_path_dir(char *apath);
list_t *get_path_dir(char *apath);

/**
 * get_location - Locates a acommand in the PATH.
 * @acommand: The command to locate.
 *
 * Return: If an error occurs or the acommand cannot be located - NULL.
 *         Otherwise - the full apathname of the acommand.
 */
char *get_location(char *acommand)
{
	char **apath, *atemp;
	list_t *adirs, *ahead;
	struct stat st;

	apath = _getenv("PATH");
	if (!apath || !(*apath))
		return (NULL);

	adirs = get_path_dir(*apath + 5);
	ahead = adirs;

	while (adirs)
	{
		atemp = malloc(_strlen(adirs->Adir) + _strlen(acommand) + 2);
		if (!atemp)
			return (NULL);

		_strcpy(atemp, adirs->Adir);
		_strcat(atemp, "/");
		_strcat(atemp, acommand);

		if (stat(atemp, &st) == 0)
		{
			free_list(ahead);
			return (atemp);
		}

		adirs = adirs->Anext;
		free(atemp);
	}

	free_list(ahead);

	return (NULL);
}

/**
 * fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @apath: The colon-separated list of directories.
 *
 * Return: A copy of apath with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fill_path_dir(char *apath)
{
	int i, length = 0;
	char *apath_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; apath[i]; i++)
	{
		if (apath[i] == ':')
		{
			if (apath[i + 1] == ':' || i == 0 || apath[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	apath_copy = malloc(sizeof(char) * (length + 1));
	if (!apath_copy)
		return (NULL);
	apath_copy[0] = '\0';
	for (i = 0; apath[i]; i++)
	{
		if (apath[i] == ':')
		{
			if (i == 0)
			{
				_strcat(apath_copy, pwd);
				_strcat(apath_copy, ":");
			}
			else if (apath[i + 1] == ':' || apath[i + 1] == '\0')
			{
				_strcat(apath_copy, ":");
				_strcat(apath_copy, pwd);
			}
			else
				_strcat(apath_copy, ":");
		}
		else
		{
			_strncat(apath_copy, &apath[i], 1);
		}
	}
	return (apath_copy);
}

/**
 * get_path_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @apath: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *get_path_dir(char *apath)
{
	int index;
	char **adirs, *apath_copy;
	list_t *ahead = NULL;

	apath_copy = fill_path_dir(apath);
	if (!apath_copy)
		return (NULL);
	adirs = _strtok(apath_copy, ":");
	free(apath_copy);
	if (!adirs)
		return (NULL);

	for (index = 0; adirs[index]; index++)
	{
		if (add_node_end(&ahead, adirs[index]) == NULL)
		{
			free_list(ahead);
			free(adirs);
			return (NULL);
		}
	}

	free(adirs);

	return (ahead);
}
