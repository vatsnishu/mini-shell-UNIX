#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "functions.h"

void newterm()
{
	while(1)
	{
		printf(">");
		char *cmd=readcommand();
		printf("%s",cmd);
	}
}
