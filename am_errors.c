#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **Aargs, int Aerr);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	unsigned int Anum1;
	int len = 1;

	if (num < 0)
	{
		len++;
		Anum1 = num * -1;
	}
	else
	{
		Anum1 = num;
	}
	while (Anum1 > 9)
	{
		len++;
		Anum1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	char *Abuffer;
	int len = num_len(num);
	unsigned int Anum1;

	Abuffer = malloc(sizeof(char) * (len + 1));
	if (!Abuffer)
		return (NULL);

	Abuffer[len] = '\0';

	if (num < 0)
	{
		Anum1 = num * -1;
		Abuffer[0] = '-';
	}
	else
	{
		Anum1 = num;
	}

	len--;
	do {
		Abuffer[len] = (Anum1 % 10) + '0';
		Anum1 /= 10;
		len--;
	} while (Anum1 > 0);

	return (Abuffer);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @Aargs: An array of arguments.
 * @Aerr: The error value.
 *
 * Return: The error value.
 */
int create_error(char **Aargs, int Aerr)
{
	char *Aerror;

	switch (Aerr)
	{
	case -1:
		Aerror = error_env(Aargs);
		break;
	case 1:
		Aerror = error_1(Aargs);
		break;
	case 2:
		if (*(Aargs[0]) == 'e')
			Aerror = error_2_exit(++Aargs);
		else if (Aargs[0][0] == ';' || Aargs[0][0] == '&' || Aargs[0][0] == '|')
			Aerror = error_2_syntax(Aargs);
		else
			Aerror = error_2_cd(Aargs);
		break;
	case 126:
		Aerror = error_126(Aargs);
		break;
	case 127:
		Aerror = error_127(Aargs);
		break;
	}
	write(STDERR_FILENO, Aerror, _strlen(Aerror));

	if (Aerror)
		free(Aerror);
	return (Aerr);

}
