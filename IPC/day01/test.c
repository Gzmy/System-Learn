/*hello user*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int fds[2];

	if(pipe(fds) == -1)
		perror("pipe"), exit(1);
	pid_t pid = fork();

	if (pid == -1)
		perror("fork"), exit(1);

	if (pid == 0)
	{//关闭读, 要写
		close(fds[0]);
		
		write(fds[1], "abc", 3);
		close(fds[1]);
		exit(0);
	}
	else
	{//关闭写, 要读
		close(fds[1]);

		char buf[100] = {};
		read(fds[0], buf, 100);
		printf("[%s]\n", buf);

		close(fds[0]);
		exit(0);
	}
}

