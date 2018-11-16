/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf{
	long mytype;
	char mtext[100];
};

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("suage:%s type \n", argv[0]);
	}

	int id = msgget(2269, 0);
	if(id == -1) perror("msgget"), exit(1);

	struct msgbuf mb;
	mb.mytype = atoi(argv[1]);
	printf("msg :");
	fgets(mb.mtext, 99, stdin);
	int r = msgsnd(id, &mb, strlen(mb.mtext), 0);
	if(r == -1) perror("msgsnd"), exit(1);
}
