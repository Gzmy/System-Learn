/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

int main()
{
	int id = semget(1234, 1, IPC_CREAT|0644);
	if(id == -1) perror("semget"), exit(1);

	printf("creat ok\n");
}
