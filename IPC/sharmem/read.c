/*hello user*/
#include <stdio.h>
#include <sys/ipc.h>
#include <string.h>
#include <assert.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

struct stu{
	int id;
	char name[10];
	
};

int main()
{
	int shmid = shmget(2269, 0, 0);
	if(shmid == -1) perror("shmget"), exit(1);

	struct stu *p = (struct stu *)shmat(shmid, NULL, 0);
	assert(p != NULL);

	printf("i = %d,", p->id);
	printf("i = %s", p->name);

}
