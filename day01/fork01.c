#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	printf("before fork\n");

	pid_t pid = fork();
	
	if (pid == 0)
	{
		printf("child\n");
	}
	else
	{
		printf("parent\n");
	}
	printf("haha\n");
	return 0;
}
