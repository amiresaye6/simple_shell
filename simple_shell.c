#include "shell.h"

/**
 * main - simple shell program runs shell comands (simple)
 *
 * when compiled it writes "$ " to thte terminal and prints an error
 * statment if any error occured
 * @argc: number of parameters
 * @argv: the parameters array
 * @evn: idk
 *
 * Return: always 0
 */

int main(int argc, char *argv[], char **evn)
{
	char *prom = "$ ", *buff = NULL;
	size_t buff_size = 0;
	ssize_t byte;
	/*int wstatus;*/
	int from_pipe = 1;
	pid_t wpid;
	/*struct stat statbuf*/;

	while (1 && from_pipe)
	{
		(void) argc;
		(void) argv;
		(void) evn;

		if (isatty(STDIN_FILENO) == 0)
			from_pipe = 0;
		write(STDOUT_FILENO, prom, 2);
		byte = getline(&buff, &buff_size, stdin);
		if (byte == -1)
		{
			perror("Error (getline)");
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (buff[byte - 1] == '\n')
			buff[byte - 1] = '\0';
		wpid = fork();
		if (wpid == -1)
		{
			perror("Error (fork)");
			exit(EXIT_FAILURE);
		}
		/*if (wpid == 0)
			_execute(buff, &statbuf, env);
		if (waitpid(wpid, &wstatus, 0) == -1)
		{
			perror("Error (wait)");
			exit(EXIT_FAILURE);
		}*/
	}
	free(buff);
	return (0);
}
