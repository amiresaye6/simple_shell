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
	int wstatus;
	int from_pipe = 1;
	pid_t wpid;
	struct stat statbuf;

	while (1 && from_pipe)
	{
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
		if (wpid == 0)
			_exec(buff, &statbuf, evn);
		if (waitpid(wpid, &wstatus, 0) == -1)
		{
			perror("Error (wait)");
			exit(EXIT_FAILURE);
		}
	}
	free(buff);
	return (0);
}

/**
 * _exec - execute function replicate
 *
 * @args: the arguments we want to execute
 * @statbuf: idk
 * @envp: idk
 *
 * Return: idk
 */

int _exec(char *args, struct stat *statbuf, char **envp)
{
	int argc;
	char **argv;
	char *exe;

	argv = split_string(args, " ", &argc);
	if (!check_file_state(argv[0], statbuf))
	{
		perror("Error (file status)");
		exit(EXIT_FAILURE);
	}
	execve(argv[0], argv, envp);

	perror("error (execve)");
	exit(EXIT_FAILURE);
}

/**
 * check_file_state - checks if the file is already exists
 *
 * @pathname: the path name
 * @statbuf: idk
 *
 * Return: 1 || 0
 */

bool check_file_state(char *pathname, struct stat *statbuf)
{
	int stat_return;

	stat_return = stat(pathname, statbuf);

	if (stat_return == 0)
		return (true);
	return (false);
}

/**
 * handel_error - a function to handel errors
 *
 * @pid: idk
 *
 * Return: void
 */

void handel_error(pid_t pid)
{
	if (pid == -1)
	{
		printf("error");
		exit(EXIT_FAILURE);
	}
}
