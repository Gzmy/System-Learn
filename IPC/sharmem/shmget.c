/*hello user*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

struct stu{
	int id;
	char name[10];
};

int main()
{
	int shmid = shmget(2269, sizeof(struct stu), IPC_CREAT|0644);
	if(shmid == -1) perror("shmget"), exit(1);
	printf("shm is ok : %d\n", shmid);
}
