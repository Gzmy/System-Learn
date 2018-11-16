/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 1024
#define MAXARG  8
#define MAXPIPE 8

char cmdline[MAXLINE+1];
char avline[MAXLINE+1];

struct cmd{
	char *argv[MAXARG];
	int infd;
	int outfd;
};

struct cmd command[MAXPIPE];
int pipenum; //管道符个数
int lastpid;

void init()
{
	int i;
	memset(cmdline, 0x00, sizeof(cmdline));
	memset(avline, 0x00, sizeof(avline));
	pipenum = 0;//管道符
	for (i = 0; i < MAXPIPE; i++){
		command[i].infd = 0;
		command[i].outfd = 1;
	}
}

int cmd_read()
{
	printf("sshell>");
	return fgets(cmdline, MAXLINE, stdin) == NULL ? 0 : 1;
}


void cmd_parse()
{
	int i;//控制第几个命令
	int j;//控制命令里面的参数
	char *p = cmdline;
	char *q = avline;

	for(i = 0; i < MAXPIPE && *p != '\0'; i++){
		for(j = 0; *p != '\0'; j++){
			while (*p != '\0' && (*p == ' ' || *p == '\t' || *p == '\n')) //过滤空白字符
				p++;
			command[i].argv[j] = q;
	
			while(*p != '\0' && *p != ' ' && *p != '\t' && *p != '\n' && *p != '|'){
				*q++ = *p++;
			}
			*q++ = '\0';
	
			if(*p == '|'){
				command[i].argv[j] = NULL;
				pipenum++;
				p++;
				break;
			}
			if(*p == '\n'){
				command[i].argv[j+1] = NULL;
				return;
			}
		}
	} 
}

void cmd_print()
{
	int i;
	int j;
	
	for(i = 0; i <= pipenum; i++){
		printf("pipe = %d\n", i);
		for(j = 0; command[i].argv[j] != NULL; j++)
			printf("\t%s\n", command[i].argv[j]);
	}
}

void cmd_execute()
{
	int i;
	int fds[2];

	for(i = 0; i <= pipenum; i++){
		if(i < pipenum){
			pipe(fds);//创建匿名管道
			command[i].outfd = fds[1];//命令输出至管道
			command[i+1].infd = fds[0];//从管道读取命令
		}
		pid_t pid = fork();

		if(pid == 0){
			if(command[i].outfd != 1){//命令不是输出至标准输出,则输出至管道
				close(1);
				dup(command[i].outfd);
				close(command[i].outfd);
			}
			if(command[i].infd != 0){//命令不是从标准输入读,则从管道读
				close(0);//关闭读
				dup(command[i].infd);//从管道读
				close(command[i].infd);//善后,关闭新打开的文件描述符
			}
			execvp(command[i].argv[0], command[i].argv);
			exit(1);
		}
		else{
			if(command[i].infd != 0)
				close(command[i].infd);
			if(command[i].outfd != 1)
				close(command[i].outfd);
			lastpid = pid;
		}
	}

	while(wait(NULL) != lastpid)
		;
}

int main()
{
	do{
		init();
		if(cmd_read() == 0)
			break;
		cmd_parse();
		cmd_print();
		cmd_execute();
	}while(1);
}
