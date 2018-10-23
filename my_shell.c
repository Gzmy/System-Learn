#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void Pares_cmd(char *buf, char *out_cmd[])
{
	int i = 0;
	int j = 0;
	while(buf[i]){
		while(buf[i] == ' '){
			i++;
		}
		out_cmd[j++] = buf + i;
		while(buf[i] != ' ' && buf[i] != 0){
			i++;
		}
		buf[i++] = '\0';
	}
	out_cmd[j] = NULL;
}

void do_exec(char *out_cmd[])
{
	pid_t pid = fork();
	if(pid < 0){
		perror("fork");
		return;
	}
	else if(pid == 0){
		execvp(out_cmd[0], out_cmd);
		exit(1);
	}
	else{
		wait(NULL);
	}
}

int main()
{
	int i;
	while(1){
		char buf[100] = {0};
		char *out_cmd[100] = {0};
		printf("[zmy@zmy]$ ");
		gets(buf);
		Pares_cmd(buf, out_cmd);
		do_exec(out_cmd);
	}
	return 0;
}
