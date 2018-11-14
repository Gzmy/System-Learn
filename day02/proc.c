/*hello user*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <stdlib.h>

int main()
{
	int g_blog = 100;

	pid_t pid = vfork();
	
	if(pid == -1)
	{
		perror("fork");
		exit(1);
	}

	if (pid == 0)
	{
		sleep(3);
		g_blog = 200;
		printf("child: %d, %p\n", g_blog, &g_blog);
		exit(0);
	}
	else
	{
		printf("parent: %d, %p\n", g_blog, &g_blog);
	}


	//pid_t pid = fork();

	//if (pid == 0)
	//{
	//	printf("my pid = %d, my parent pid = %d\n", getpid(), getppid());
	//	sleep(5);
	//	exit(1);
	//}
	//else
	//{
	//	while(1)
	//	{
	//		printf("my pid = %d\n", getpid());
	//		sleep(3);
	//	}
	//}
	
	
	return 0;
}
