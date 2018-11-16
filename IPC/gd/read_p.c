/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("my.p", O_RDONLY);
	char buf[2];
	while(1)
	{
		read(fd, buf, 1);
		printf("read: [%c]\n", buf[0]);
		sleep(100000000);
	}

	close(fd);
}
