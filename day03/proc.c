/*hello user*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();
	if (pid == 0)
	{
		int count = 5;
		while(count--)
		{
			printf("child, pid: %d, ppid : %d\n", getpid(), getppid());
			printf("hello %d\n", count);
			sleep(1);
		}
		printf("child quit\n");
		exit(13);
	}
	else
	{
		printf("father, pid: %d, ppid : %d\n", getpid(), getppid());
		//pid_t ret = wait(NULL);
		int status;
		pid_t ret = waitpid(pid, &status, 0);
		if(ret > 0)
		{
			printf("sig : %d, exit : %d\n", status&0x7F, (status>>8)&0xFF);
		}
		printf("father quit\n");
		sleep(1);
		printf("ret : %d\n", ret);
	}

	//printf("hello world!\n");
	//sleep(3);
	//exit(1);
}
