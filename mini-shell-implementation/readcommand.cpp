#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

char* readcommand()
{
	char *cmdline=NULL;
	size_t len = 0;
	getline(&cmdline, &len, stdin);
	return cmdline;
}
