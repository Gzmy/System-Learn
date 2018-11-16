/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/ipc.h>

struct msgbuf{
	long mytype;
	char mtext[100];
};

int main(int argc, char *argv[])
{
	struct msgbuf mb;
	if (argc != 2){
		fprintf(stderr, "suage : %s type \n", argv[0]);
	}

	int id = msgget(2269, 0);
	if(id == -1) perror("msgget"), exit(1);

	int ret = msgrcv(id, &mb, 100, atoi(argv[1]), 0);
	if(ret == -1) perror("msgrcv"), exit(1);

	printf("%s\n", mb.mtext);
}
