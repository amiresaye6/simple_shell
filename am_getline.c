#include "shell.h"

void *_realloc(void *Aptr, unsigned int Aold_size, unsigned int Anew_size);
void assign_lineptr(char **Alineptr, size_t *n, char *Abuffer, size_t b);
ssize_t _getline(char **Alineptr, size_t *n, FILE *Astream);

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @Aptr: A pointer to the memory previously allocated.
 * @Aold_size: The size in bytes of the allocated space for ptr.
 * @Anew_size: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *Aptr, unsigned int Aold_size, unsigned int Anew_size)
{
	void *Amem;
	char *Aptr_copy, *Afiller;
	unsigned int Aindex;

	if (Anew_size == Aold_size)
		return (Aptr);

	if (Aptr == NULL)
	{
		Amem = malloc(Anew_size);
		if (Amem == NULL)
			return (NULL);

		return (Amem);
	}

	if (Anew_size == 0 && Aptr != NULL)
	{
		free(Aptr);
		return (NULL);
	}

	Aptr_copy = Aptr;
	Amem = malloc(sizeof(*Aptr_copy) * Anew_size);
	if (Amem == NULL)
	{
		free(Aptr);
		return (NULL);
	}

	Afiller = Amem;

	for (Aindex = 0; Aindex < Aold_size && Aindex < Anew_size; Aindex++)
		Afiller[Aindex] = *Aptr_copy++;

	free(Aptr);
	return (Amem);
}

/**
 * assign_lineptr - Reassigns the lineptr variable for _getline.
 * @Alineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @Abuffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void assign_lineptr(char **Alineptr, size_t *n, char *Abuffer, size_t b)
{
	if (*Alineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*Alineptr = Abuffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*Alineptr = Abuffer;
	}
	else
	{
		_strcpy(*Alineptr, Abuffer);
		free(Abuffer);
	}
}

/**
 * _getline - Reads input from a stream.
 * @Alineptr: A buffer to store the input.
 * @n: The size of lineptr.
 * @Astream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **Alineptr, size_t *n, FILE *Astream)
{
	static ssize_t Ainput;
	ssize_t Aret;
	char c = 'x', *Abuffer;
	int r;

	if (Ainput == 0)
		fflush(Astream);
	else
		return (-1);
	Ainput = 0;

	Abuffer = malloc(sizeof(char) * 120);
	if (!Abuffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && Ainput == 0))
		{
			free(Abuffer);
			return (-1);
		}
		if (r == 0 && Ainput != 0)
		{
			Ainput++;
			break;
		}

		if (Ainput >= 120)
			Abuffer = _realloc(Abuffer, Ainput, Ainput + 1);

		Abuffer[Ainput] = c;
		Ainput++;
	}
	Abuffer[Ainput] = '\0';

	assign_lineptr(Alineptr, n, Abuffer, Ainput);

	Aret = Ainput;
	if (r != 0)
		Ainput = 0;
	return (Aret);
}
