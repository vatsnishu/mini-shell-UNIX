#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char term[]="gnome-terminal -x ./hellomake";
	execl("/bin/sh", "sh", "-c", term, (char *) NULL);
	return 0;
}
