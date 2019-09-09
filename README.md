# mini-shell-UNIX

Implemented a simple command­interpreter, a.k.a. “shell,” for
Unix. The shell implemented is similar to linux shell but it is not have as many features as linux shell have.
The shell should has much of the important functionality:
● Execute all the commands (ls, clear, vi etc)

● Shell builtins (cd, pwd, export)

● Print environment variables and text using echo

● Background and foreground functionality : &, fg ­ Allow the user to execute one or more
programs, from executable files on the file­system, as background or foreground jobs.

● Allow for the piping of several tasks :  Pipes “|” (multiple)

● Input and Output redirection: (<, >)

● Support for history and '!' operator

● Handle Interrupt Signal

Specifications:

● The look and feel of solution is similar to that of other UNIX shells e.g. your
shell should work in an infinite loop. It should produce a prompt, e.g., xsh>, accept input
from the user, and then produce another prompt till an “exit” is entered.

● It is an application program invoked without command­line
parameters or configuration files.

● Parsing the input : For certain characters : &, |, <, and >, your shell should assume that
these meta­characters cannot occur inside strings and have to be handled separately.

● Certain combinations of keystrokes will generate signals to your shell instead of
appearing within stdin. Your shell should respond appropriately to these signals.

    ○ Control­Z generates a SIGSTOP. This should not cause your shell to be suspended. Instead, it causes our shell to suspend the processes in the current foreground job. If there is no foreground job, it should have no effect.

    ○ Control­C generates a SIGINT. This should not kill your shell. Instead it causes our shell to kill the processes in the current foreground job. If there is no foreground job, it should have no effect.
● If the user enters something improper, your shell should produce a meaningful error
message.

● Empty command lines are treated as no­ops and yield a new prompt.
Examples:
1. Commands and Shell Builtins:
bash prompt:~$ ./a.out
My_Shell:/home/user$ ls
shell.cpp main.cpp a.out
My_Shell:/home/user$ fdresdsad
My_Shell: fdresdsad: No command found
My_Shell:/home/user$ cd OS
My_Shell:/home/user/OS$
My_Shell:/home/user/OS$ cd ..
My_Shell:/home/user/$ cd /home/user/work/temp
My_Shell:/home/user/work/temp$
My_Shell:/home/user/OS$ echo $PWD
/home/user/OS
2. I/O redirection and pipes:
My_Shell:/home/user/OS$ echo Hello, this is a line > out
My_Shell:/home/user/OS$ cat out
Hello, this is a line
My_Shell:/home/user/OS$ cat out| wc
1 5 22
My_Shell:/home/user/OS$  ls l | grep "out" | wc | wc | grep "1" | wc
1 3 24
My_Shell:/home/user/OS$  ls R my_folder1/ | grep "abc" >out
3. History:
My_Shell:/home/user/OS$ history
   . . .
   43  man bash
   44  man fc
   45  man bash
   46  fc l 10
   47  history
   48  ls a
   49  vim .bash_history
   50  history
   51  man history
   52  history 10
   53  history
My_Shell:/home/user/OS$ history 5
   50  history
   51  man history
   52  history 10
   53  history
   54  history 5
My_Shell:/home/user/OS$ history | grep cd
   33  cd Pictures/
   37  cd ..
   39  cd Desktop/
   61  cd /usr/bin/
   68  cd
   83  cd /etc/
   86  cd resolvconf/
   90  cd resolv.conf.d/
My_Shell:/home/user/OS$ !51 # displays man page of history for our session
My_Shell:/home/user/OS$ vim file.cpp
My_Shell:/home/user/OS$ echo “hello”
My_Shell:/home/user/OS$  !v #Should execute “vim file.cpp”
My_Shell:/home/user/OS$  !! #Should execute “vim file.cpp”
My_Shell:/home/user/OS$ ls /usr/share/doc/manpages
My_Shell:/home/user/OS$ echo hello
4. Exit:
My_Shell:/home/user/OS$ exit
Bye...
bash prompt:~$
Important functions and system calls:
● int chdir(const char *path)
● int execvp(const char *file, char *const argv[])
● void exit(int status)
● pid_t fork(void)
● char *getcwd(char *buf, size_t size)
● char getenv(const char *name)
● void perror(const char *string)
● int setenv(const char *name, const char *value, int overwrite)
● sig_t signal(int sig, sig_t func)
● pid_t wait(int *status)
● pid_t waitpid(pid_t wpid, int *status, int options)
● sighandler_t signal(int signum, sighandler_t handler);
● int dup2(int oldfd, int newfd);

NOTE:
1. system() has not been used, to explore basic system calls.
2. Did use any data structure or external text file to store the intermediate result in
pipes.
