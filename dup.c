#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
	int fd = open("log.txt", O_WRONLY | O_CREAT, 0664);

	printf("%d\n", fd);
	close(1);
	//fd = dup(fd);
	dup2(fd, 1);
	printf("%d\n", fd);
	printf("hello world!\n");
	printf("hello world!\n");
	printf("hello world!\n");
	printf("hello world!\n");
}
