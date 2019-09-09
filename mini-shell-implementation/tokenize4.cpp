#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include "functions.h"

#define DELIM " \t\r\n\a"
#define MAX 128


void tokenize(char *cmd)
{
	int i=0,k=0,l=0,iq=0,nc;
	char token[10];
	i=0;
	while(i<10)
	{
		free(argss[i]);
		args[i]=NULL;
		i++;
	}
	i=0;
	while(cmd[i] && k<10)
	{
		if(cmd[i]=='"')
		{
			if(iq==1)
			{
				iq=0;
			}
			else
			{
				iq=1;
			}
		}
		if(cmd[i]==' ' && iq==0)
		{
			token[l]='\0';
			argss[k]=(char *)malloc(128*sizeof(char));
		//	printf("%s %d",cmds[k],k);
			strcpy(argss[k],token);
			k++;
			l=0;
		}
		else
		{
			token[l]=cmd[i];
			l++;
		}
		i++;
	}
	token[l]='\0';
	if(k<10)
	{
		argss[k]=(char *)malloc(128*sizeof(char));
		strcpy(argss[k],token);
	//	printf("%s %d",cmds[k],k);
		k++;
	}
	
	i=0;
	while(argss[i]!=NULL && i<10)
	{
		///printf("cut %s\n",cmds[i]);
		i++;
	}

}
