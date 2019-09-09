#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>


#define DELIM " \t\r\n\a"
#define MAX 128

char** tokenize(char *cmdline)
{
	int i=0,count=0,k=0,l=0,iq=0,is=0,m;
	char **arg=NULL;
	arg=(char **)malloc(MAX * sizeof(char*));
	char *str= NULL;
	str=(char *)malloc(strlen(cmdline) * sizeof(char*));
	char token[10][MAX];
	//char *token[10];
	strcpy(str,cmdline);
	m=0;
	while(i<strlen(str) && m<10)
	{
		if(str[i]==' ' && (iq==0))
		{
			if(is==0)
			{
				token[m][k]='\0';
				arg[l]=token[m];
				printf("k%s%d\n",arg[l],l);
				m++;
				l++;
				k=0;
				is=1;
			}
		}
		else if(str[i]=='"')
		{
			//printf("2%c",str[i]);
			if(is==1)
			{
				//toke
				is=0;
			}
			if(iq==0)
				iq=1;	
			else
				iq=0;
			
		}
		else
		{
			//printf("3%c",str[i]);
			if(is==1)
			{
				//toke
				is=0;
			}
			token[m][k]=str[i];

			k++;
		}
		i++;
	}
	token[m][k]='\0';
	arg[l]=token[m];
	printf("k%s%d\n",arg[l],l);
	m++;
	l++;
	arg[l]=NULL;
	i=0;
	while(arg[i]!=NULL)
		{	
			printf("att[%d] is %s ",i,arg[i]);
			i++;
		}

  	return arg;
}

