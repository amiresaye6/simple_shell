#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

bool check_file_state(char *pathname, struct stat *statbuf);
int _exec(char *args, struct stat *statbuf, char **envp);
void handel_error(pid_t pid);

#endif
