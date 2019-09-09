#include<stdlib.h>
#include<string.h>
#include <utility>
#include<malloc.h>
#include<sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fcntl.h>
#include<vector>
#include "functions.h"
#define PERMS 0666
#define MAX 128

using namespace std;
void printpr();

char **args=NULL;

int h=0;
vector<string> histv;
pid_t pid = 0;

void writehist(char* cmd)
{
	int hist_fd;
	if((hist_fd=open("/home/nishu/Desktop/codeofshell/hist.txt",O_RDWR | O_APPEND))<0)	
	{
		if ((hist_fd= creat("/home/nishu/Desktop/codeofshell/hist.txt", PERMS)) == -1)
			perror("history");
		if((hist_fd=open("./hist.txt",O_RDWR | O_APPEND ))<0)	
		{
			perror("history");
		}
	}
	char hir[128],hi[128];
	int t,i=0,k=0;
	t=h;
	h++;
	while(t!=0)
	{
		hir[i]=t%10+'0';
		t=t/10;
		i++;
	}
	int j=i-1;
	k=0;
	while(j>=0)
	{
		hi[k]=hir[j];
		k++;
		j--;
	}

	hi[i]=' ';
	i++;
	k=0;
	while(cmd[k])
	{
		hi[i]=cmd[k];
		i++;
		k++;	
	}
	
	if(write(hist_fd,hi,i)<0)
	{
		perror("history");
	}
}

void readhist()
{
	int hist_fd;
	if((hist_fd=open("/home/nishu/Desktop/codeofshell/hist.txt",O_RDWR))<0)	
	{
		perror("history");
	}
	char hi[1024];
	if(read(hist_fd,hi,1024)<0)	
	{
		perror("history");
	}
	char acmd[10];
	char icmd=0;
	int t=0,i=0,k=0;
	while(hi[t]!='\0' && hi[t]!=EOF)
	{
		if(hi[t]==' ' && icmd==0)
		{
			icmd=1;
		}
		else if(hi[t]=='\n')
		{
			icmd=0;
			acmd[k]='\0';
			histv.push_back(acmd);
			h++;
			k=0;
		}
		else if(icmd==1)
		{
			acmd[k]=hi[t];
			k++;
		}
		t++;
	}
	icmd=0;
	acmd[k]='\0';
	k=0;
}



void tokenize(char *cmdline)
{
	args=NULL;
	int i=0,count=0,k=0,l=0,iq=0,is=0,m;
	args=(char **)malloc(MAX * sizeof(char*));
	char *str= NULL;
	str=(char *)malloc(strlen(cmdline) * sizeof(char*));
	char token[100][MAX];
	strcpy(str,cmdline);
	m=0;
	while(i<strlen(str) && m<100)
	{
		if(str[i]==' ' && (iq==0))
		{
			if(is==0)
			{
				token[m][k]='\0';
				args[l]=token[m];
				m++;
				l++;
				k=0;
				is=1;
			}
		}
		else if(str[i]=='"')
		{
			if(is==1)
			{
				is=0;
			}
			if(iq==0)
				iq=1;	
			else
				iq=0;

		}
		else
		{
			if(is==1)
			{
				is=0;
			}
			token[m][k]=str[i];

			k++;
		}
		i++;
	}
	if(token[m][k-1]=='\n')	
		token[m][k-1]='\0';
	token[m][k]='\0';
	if(token[m][0]!='\0')
	{
		args[l]=token[m];
		m++;
		l++;
	}
	args[l]=NULL;
	i=0;
	while(args[i]!=NULL)
	{	
		i++;
	}

}

int ext(char **args){
	cout<<"BYE..";
	exit(0);
}


void execu(char **args)
{

	if(args[0]!=NULL && strcmp("history",args[0])==0)
			{
				int i;
				if(args[1]==NULL)
				{
					for(i=0;i<histv.size();i++)
					{
						cout<<i+1<<" "<<histv[i]<<"\n";
					}
				}
				else 
				{
					int s=0;
					int o=0,p;
					while(args[1][s]>='0' && args[1][s]<='9')
					{
						o=o*10+(args[1][s]-'0');
						s++;
					}
					int us=histv.size()-1;
					if(o>us)
						o=us;
					for(s=o;s>0;s--)
						cout<<us-s+1<<histv[us-s]<<'\n';
				}
			}
	
	else if(args[0]!=NULL && strcmp("cd",args[0])==0)
	{
		if(args[1]==NULL || strcmp("~",args[1])==0)
		{
			if(chdir(getenv("HOME")) != 0)

				perror("cd");

		}
		else if(chdir(args[1]) == 0)
		{
		}
		else
		{
			perror("cd");
		}
	}

	else if (execvp(args[0], args) == -1)
	{
		perror("sh");
	}
	exit(EXIT_FAILURE);
}


void printpr()
{
	char *cwd=(char *)malloc(sizeof(char) *(50)); 
	cwd=getcwd(cwd,50);
	char *prompt = (char *)malloc(sizeof(char) *(53)); 
	prompt=strcat(cwd,"=>");
	printf("%s",prompt);
}
void stopfork( int signo )
{
	if (pid) 
	{
		kill( pid, SIGTSTP );

		printf( "\n[1]+ Stopped\n" );
		pid = 0;

		main();
	}
}
void killfork( int signo )
{
	if (pid) 
	{
		kill( pid, SIGINT );

		printf( "\n[1]+ killed\n" );
		pid = 0;

		main();
	}
}


int main()
{
	readhist();
	int maxh=0;

	if (signal(SIGINT, killfork) == SIG_ERR)
		printf("\nCould not catch SIGINT\n"); 
	if (signal(SIGTSTP, stopfork) == SIG_ERR )
		printf("\nCould not catch SIGTSTP\n"); 

	while(1)
	{
		int pd[2];

		int pd0[30];

		int i,k,iq=0,nc;
		for(i=0;i<30;i++)
		{
			pd0[i]=-1;
		}
		printpr();
		char *cmd=readcommand();
		if(cmd!=NULL && cmd[0]=='!')
		{
			int s=histv.size()-1;
			if(cmd[1]=='!')
			{
				int s=histv.size()-1;
				if(s>=0)
				{
					cmd=(char*)histv[s].c_str();
				}

			}
			else if(cmd[1]=='-')
			{
				s=2;
				int o=0,p;
				while(cmd[s]>='0' && cmd[s]<='9')
				{
					o=o*10+(cmd[s]-'0');
					s++;
				}
				if((s-o)>=0)
					cmd=(char*)histv[s-o].c_str();
			}
			else if(cmd[1]==' ')
			{
				int o=2,p,nuu=0;
				while(strlen(cmd)>=3 && cmd[o]!='\0' && cmd[o]!='\0')
				{
					if(cmd[o]>='0' && cmd[o]<='9')
					{
						nuu=nuu*10+(cmd[o]-'0');
					}
					o++;
				}
				if(nuu>0 && nuu<histv.size()+1)
					cmd=(char*)histv[nuu-1].c_str();
			}

		}
		if(cmd!=NULL && cmd[0]!='!' || (cmd[1]!='!' && cmd[1]!='-' && cmd[1]!=' '))
		{
			char tep[100];
			int g=0;
			while(cmd[g]!='\0' && cmd[g]!='\n')
			{
				tep[g]=cmd[g];
				g++;
			}
			tep[g]='\0';
			if(g>0)
			{
				histv.push_back(tep);
				writehist(cmd);
			}
		}
		char *cmds[10];
		for(i=0;i<10;i++)
		{
			cmds[i]=NULL;
		}
		i=0;
		k=0;
		cmds[k]=cmd;
		k++;
		while(cmd[i])
		{
			if(cmd[i]=='"')
			{
				if(iq==1)
					iq=0;
				else
					iq=1;
			}
			if(cmd[i]=='|' && iq==0)
			{
				cmd[i]='\0';
				cmds[k]=cmd+i+1;
				k++;
			}
			i++;
		}
		i=0;
		while(cmds[i]!=NULL)
		{
			i++;
		}
		nc=i;
		i=0;
		int status,wpid;

		i=0;
		while(i<nc-1)
		{
			if(pipe(pd)==-1)
			{
				perror("pipe");
			}
			pd0[(i+1)*2]= pd[0];
			pd0[(i*2)+1]=pd[1];
			i++;

		}
		i=0;

		while(nc!=0 && i<nc)
		{
			int ifileflag=0,fi=0,a;
			char ifile[100];
			a=0;
			while(cmds[i][a]!='\0')
			{
				if(cmds[i][a]=='>' && ifileflag==0)
				{
					ifileflag=1;
					cmds[i][a]='\0';
				}
				else if(ifileflag==1)
				{

					ifile[fi]=cmds[i][a];

					fi++;

				}
				a++;
			}
			if(ifile[fi-1]=='\n');
			ifile[fi-1]='\0';
			ifile[fi]='\0';

			int ofileflag=0,fo=0;
			char ofile[100];
			a=0;
			while(cmds[i][a]!='\0')
			{
				if(cmds[i][a]=='<' && ofileflag==0)
				{
					ofileflag=1;
					cmds[i][a]='\0';
				}
				else if(ofileflag==1)
				{

					ofile[fo]=cmds[i][a];

					fo++;

				}
				a++;
			}
			if(ofile[fo-1]=='\n');
			ofile[fo-1]='\0';
			ofile[fo]='\0';
			if(cmds[i][0]=='e' && cmds[i][1]=='c')
				tokenize(cmds[i]);
			else if(cmds[i][0]=='g' && cmds[i][1]=='r')
				tokenize(cmds[i]);
			else
				args=tokenize1(cmds[i]);
			if(nc==1 && args[0]!=NULL && strcmp("cd",args[0])==0)
			{
				if(args[1]==NULL || strcmp("~",args[1])==0)
				{
					if(chdir(getenv("HOME")) != 0)

						perror("cd");

				}
				else if(chdir(args[1]) == 0)
				{
				}
				else
				{
					perror("cd");
				}
			}

			else if(args[0]!=NULL && strcmp("export",args[0])==0)
			{
				if(args[1]==NULL)
				{
					printf("No argument given\n");
				}
				else 
				{
					int y=0,na=0,va=0;
					char name[10],value[20];
					while(args[1][y]!='\0' && args[1][y]!='=')
					{
						name[na]=args[1][y];
						y++;
						na++;
					}
					if(name[na-1]=='\n')
						name[na-1]='\0';
					name[na]='\0';
					if(args[1][y]=='=')
					{
						y++;
						while(args[1][y]!='\0' )
						{
							value[va]=args[1][y];
							y++;
							va++;
						}
						if(value[va-1]=='\n')
							value[va-1]='\0';
						value[va]='\0';
					}
					else
					{
						value[va]='\0';
					}
					if((setenv(name, value, 1))<0)
					{
						perror("setnv");
					}
				}
			}
			else if(args[0]!=NULL && strcmp("pwd",args[0])==0)
			{
				char *cwd=(char *)malloc(sizeof(char) *(50)); 
				cwd=getcwd(cwd,50);
				printf("%s\n",cwd);
			}
			else if(args[0]!=NULL && strcmp("exit",args[0])==0)
			{
				if(ext(args) == -1)
					perror("exit");
			}
			else
			{
				pid = fork();
				if (pid == 0)
				{
					if(ifileflag==1)
					{
						int fdi;
						if((fdi=open(ifile, O_RDWR|O_CREAT|O_TRUNC, 0666))<0)
						{

							perror("fd");
						}

						dup2(fdi,1);
					}

					if(ofileflag==1)
					{
						int fdo;
						if((fdo=open(ofile, O_RDWR))<0)
						{

							perror("fd");
						}
						dup2(fdo,0);
					}
					if(nc>1)
					{
						if(i!=nc-1)   
						{
							close(1);
							dup2(pd0[(i*2)+1],1);

						}

						if(i!=0)  
						{
							close(0);
							dup2(pd0[i*2],0);
						}
					}
					if(args[0]!=NULL && strcmp(args[0],"echo")==0)
					{
						if(args[1][0]=='$')
						{
							args[1]=getenv(args[1]+1);
						}
					}
					execu(args);
				} 
				else if (pid < 0) 
				{
					perror("sh");
				} 
				else 
				{
					do 
					{
						wpid = waitpid(pid, &status, WUNTRACED);
					} while (!WIFEXITED(status) && !WIFSIGNALED(status));
					close(pd0[i*2+1]);
					if(i>0)
						close(pd0[i*2]);
				}
			}
			i++;
		}
	}
}
