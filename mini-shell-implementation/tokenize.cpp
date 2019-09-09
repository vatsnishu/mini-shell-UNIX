#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include "functions.h"


#define DELIM " \t\r\n\a"
#define MAX 128

char** tokenize1(char *cmdline)
{
	int i=0;
	char **arg=NULL;
	arg=(char **)malloc(MAX * sizeof(char*));;
	size_t len = 0;
	char *token;
	token = strtok(cmdline, DELIM);
  	while (token != NULL) 
	{
    		arg[i] = token;
		//printf("k%s\n",arg[i]);
    		i++;
   		token = strtok(NULL, DELIM);
	}
  	arg[i] = NULL;
  	return arg;
}


