#include<stdio.h>
#include<signal.h>
#include <unistd.h>
#include "functions.h"

using namespace std;

void signal_handler(int signo)
{
    if (signo == SIGINT)
     {	
	if(main()!=0)
		perror("siint");
	}
    else if (signo == SIGTSTP)
        printf("received SIGTSTP\n");
    else if (signo == SIGSTOP)
        printf("received SIGSTOP\n");
}

