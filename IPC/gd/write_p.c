/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("my.p", O_WRONLY);
	char buf[2] = {'a'};
	int i = 0;
	while(1)
	{
		write(fd, buf, 1);
		printf("write ok :%d %c\n", i, buf[0]);
		i++;
		buf[0] = 'a' + i%25;
	}

	close(fd);
}
