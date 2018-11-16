/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fds[2];
	pipe(fds);

	pid_t pid = fork();
	if(pid == 0)
	{
		close(1);
		dup(fds[1]);
		close(fds[1]);
		close(fds[0]);
		execlp("ls", "ls", "-l", NULL);
		exit(1);
	}else
	{
		close(0);
		dup(fds[0]);
		close(fds[0]);
		close(fds[1]);
		execlp("wc", "wc", "-l", NULL);
		exit(1);
	}
}
