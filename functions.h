char* readcommand();
char** tokenize1(char *cmdline);
int executecmd(char **args);
void signal_handler(int signo);
int main();
