/*hello user*/
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid = vfork();

	if(pid == -1)
	{
		perror("vfork");
		exit(1);
	}

	if(pid == 0)
	{
		sleep(1);
		printf("child here\n");
		sleep(1);
	}
	else
	{
		printf("parent here\n");
	}
}
