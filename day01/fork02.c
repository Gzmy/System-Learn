#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//
//int main()
//{
//	printf("before fork:%d\n", getpid());
//
//	pid_t pid = fork();
//	if(pid == 0)
//	{
//		printf("myid = %d, myparentid = %d\n", getpid(), getppid());
//	}
//	else
//	{
//		printf("myid = %d\n", getpid());
//	}
//
//	pid = fork();
//	if(pid == 0)
//	{
//		printf("myid = %d, myparentid = %d\n", getpid(), getppid());
//	}
//	else
//	{
//		printf("myid = %d\n", getpid());
//	}
//
//	printf("haha\n");
//
//
//	sleep(3);
//	return 0;
//}
//

int main()
{

	printf("brfore fork%d\n", getpid());

	pid_t pid = fork();
	if(pid == 0)
	{
		printf("myid = %d, myparid = %d\n", getpid(), getppid());
	}
	else
	{
		printf("myid = %d, mychildid = %d\n", getpid(), pid);
		pid_t pid2 = fork();

		if(pid2 == 0)
		{
			printf("myid = %d, myparid = %d\n", getpid(), getppid());
		}
		else
		{
			printf("parent creat 2 pid = %d, mychildid = %d\n", getpid(), pid);
		}
		sleep(1);
	}

	printf("进程终止\n");
	return 0;
}



