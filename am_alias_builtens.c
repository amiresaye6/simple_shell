#include "shell.h"

int shellby_alias(char **Aargs, char __attribute__((__unused__)) **Afront);
void set_alias(char *Avar_name, char *Avalue);
void print_alias(alias_t *Aalias);

/**
 * shellby_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @Aargs: An array of arguments.
 * @Afront: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_alias(char **Aargs, char __attribute__((__unused__)) **Afront)
{
	alias_t *Atemp = Aaliases;
	int i, Aret = 0;
	char *Avalue;

	if (!Aargs[0])
	{
		while (Atemp)
		{
			print_alias(Atemp);
			Atemp = Atemp->Anext;
		}
		return (Aret);
	}
	for (i = 0; Aargs[i]; i++)
	{
		Atemp = Aaliases;
		Avalue = _strchr(Aargs[i], '=');
		if (!Avalue)
		{
			while (Atemp)
			{
				if (_strcmp(Aargs[i], Atemp->Aname) == 0)
				{
					print_alias(Atemp);
					break;
				}
				Atemp = Atemp->Anext;
			}
			if (!Atemp)
				Aret = create_error(Aargs + i, 1);
		}
		else
			set_alias(Aargs[i], Avalue);
	}
	return (Aret); }

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @Avar_name: Name of the alias.
 * @Avalue: Value of the alias. First character is a '='.
 */
void set_alias(char *Avar_name, char *Avalue)
{
	alias_t *Atemp = Aaliases;
	int len, j, k;
	char *Anew_value;

	*Avalue = '\0';
	Avalue++;
	len = _strlen(Avalue) - _strspn(Avalue, "'\"");
	Anew_value = malloc(sizeof(char) * (len + 1));
	if (!Anew_value)
		return;
	for (j = 0, k = 0; Avalue[j]; j++)
	{
		if (Avalue[j] != '\'' && Avalue[j] != '"')
			Anew_value[k++] = Avalue[j];
	}
	Anew_value[k] = '\0';
	while (Atemp)
	{
		if (_strcmp(Avar_name, Atemp->Aname) == 0)
		{
			free(Atemp->Avalue);
			Atemp->Avalue = Anew_value;
			break;
		}
		Atemp = Atemp->Anext;
	}
	if (!Atemp)
		add_alias_end(&Aaliases, Avar_name, Anew_value);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 * @Aalias: Pointer to an alias.
 */
void print_alias(alias_t *Aalias)
{
	char *Aalias_string;
	int len = _strlen(Aalias->Aname) + _strlen(Aalias->Avalue) + 4;

	Aalias_string = malloc(sizeof(char) * (len + 1));
	if (!Aalias_string)
		return;
	_strcpy(Aalias_string, Aalias->Aname);
	_strcat(Aalias_string, "='");
	_strcat(Aalias_string, Aalias->Avalue);
	_strcat(Aalias_string, "'\n");

	write(STDOUT_FILENO, Aalias_string, len);
	free(Aalias_string);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @Aargs: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **Aargs)
{
	alias_t *Atemp;
	int i;
	char *Anew_value;

	if (_strcmp(Aargs[0], "alias") == 0)
		return (Aargs);
	for (i = 0; Aargs[i]; i++)
	{
		Atemp = Aaliases;
		while (Atemp)
		{
			if (_strcmp(Aargs[i], Atemp->Aname) == 0)
			{
				Anew_value = malloc(sizeof(char) * (_strlen(Atemp->Avalue) + 1));
				if (!Anew_value)
				{
					free_args(Aargs, Aargs);
					return (NULL);
				}
				_strcpy(Anew_value, Atemp->Avalue);
				free(Aargs[i]);
				Aargs[i] = Anew_value;
				i--;
				break;
			}
			Atemp = Atemp->Anext;
		}
	}

	return (Aargs);
}
