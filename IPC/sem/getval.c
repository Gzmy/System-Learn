/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

int main()
{
	int id = semget(1234, 0, 0);
	if(id == -1) perror("semget"), exit(1);

	int val = semctl(id, 0, GETVAL, 0);
	printf("val = %d\n", val);
}
