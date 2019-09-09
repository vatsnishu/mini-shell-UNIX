#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "functions.h"

int executecmd(char **args)
{
		pid_t pid;
		int status,wpid;
		pid = fork();
		if (pid == 0)
		{
			// Child process
			if (execvp(args[0], args) == -1)
			{
				perror("sh");
			}
			exit(EXIT_FAILURE);
		} else if (pid < 0) 
		{
			// Error forking
			perror("sh");
		} else 
		{
			// Parent process
			do 
			{
			wpid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}

		return 1;
}


