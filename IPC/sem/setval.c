/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

union semun{
	int val;
};

int main()
{
	int id = semget(1234, 0, 0);
	if(id == -1) perror("semget"), exit(1);

	union semun su;
	su.val = 5;
	semctl(id, 0, SETVAL, su);
}
