#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int g_data = 250;

int main()
{
	pid_t pid = fork();

	if(pid == 0)
	{
		g_data = 520;
		printf("child g_data = %p\n", &g_data);
		printf("child value  = %d\n", g_data);
	}
	else
	{
		sleep(1);
		printf("parent g_data = %p\n", &g_data);
		printf("parent value  = %d\n", g_data);
	}
	return 0;
}
