#include "shell.h"

void handle_line(char **aline, ssize_t aread);
ssize_t get_new_len(char *aline);
void logical_ops(char *aline, ssize_t *anew_len);

/**
 * handle_line - Partitions a line aread from standard input as needed.
 * @aline: A pointer to a line aread from standard input.
 * @aread: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **aline, ssize_t aread)
{
	char *aold_line, *anew_line;
	char aprevous, acurrent, anext;
	size_t i, j;
	ssize_t anew_len;

	anew_len = get_new_len(*aline);
	if (anew_len == aread - 1)
		return;
	anew_line = malloc(anew_len + 1);
	if (!anew_line)
		return;
	j = 0;
	aold_line = *aline;
	for (i = 0; aold_line[i]; i++)
	{
		acurrent = aold_line[i];
		anext = aold_line[i + 1];
		if (i != 0)
		{
			aprevous = aold_line[i - 1];
			if (acurrent == ';')
			{
				if (anext == ';' && aprevous != ' ' && aprevous != ';')
				{
					anew_line[j++] = ' ';
					anew_line[j++] = ';';
					continue;
				}
				else if (aprevous == ';' && anext != ' ')
				{
					anew_line[j++] = ';';
					anew_line[j++] = ' ';
					continue;
				}
				if (aprevous != ' ')
					anew_line[j++] = ' ';
				anew_line[j++] = ';';
				if (anext != ' ')
					anew_line[j++] = ' ';
				continue;
			}
			else if (acurrent == '&')
			{
				if (anext == '&' && aprevous != ' ')
					anew_line[j++] = ' ';
				else if (aprevous == '&' && anext != ' ')
				{
					anew_line[j++] = '&';
					anew_line[j++] = ' ';
					continue;
				}
			}
			else if (acurrent == '|')
			{
				if (anext == '|' && aprevous != ' ')
					anew_line[j++]  = ' ';
				else if (aprevous == '|' && anext != ' ')
				{
					anew_line[j++] = '|';
					anew_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (acurrent == ';')
		{
			if (i != 0 && aold_line[i - 1] != ' ')
				anew_line[j++] = ' ';
			anew_line[j++] = ';';
			if (anext != ' ' && anext != ';')
				anew_line[j++] = ' ';
			continue;
		}
		anew_line[j++] = aold_line[i];
	}
	anew_line[j] = '\0';

	free(*aline);
	*aline = anew_line;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t anew_len = 0;
	char acurrent, anext;

	for (i = 0; line[i]; i++)
	{
		acurrent = line[i];
		anext = line[i + 1];
		if (acurrent == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (acurrent == ';')
			{
				if (anext == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					anew_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && anext != ' ')
				{
					anew_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					anew_len++;
				if (anext != ' ')
					anew_len++;
			}
			else
				logical_ops(&line[i], &anew_len);
		}
		else if (acurrent == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				anew_len++;
			if (anext != ' ' && anext != ';')
				anew_len++;
		}
		anew_len++;
	}
	return (anew_len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @aline: A pointer to the character to check in the line.
 * @anew_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *aline, ssize_t *anew_len)
{
	char aprevous, acurrent, anext;

	aprevous = *(aline - 1);
	acurrent = *aline;
	anext = *(aline + 1);

	if (acurrent == '&')
	{
		if (anext == '&' && aprevous != ' ')
			(*anew_len)++;
		else if (aprevous == '&' && anext != ' ')
			(*anew_len)++;
	}
	else if (acurrent == '|')
	{
		if (anext == '|' && aprevous != ' ')
			(*anew_len)++;
		else if (aprevous == '|' && anext != ' ')
			(*anew_len)++;
	}
}
