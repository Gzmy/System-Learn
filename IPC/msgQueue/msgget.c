/*hello user*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main()
{
	int msgid = msgget(2269, IPC_CREAT | 0644);
	if(msgid == -1) perror("msgid"), exit(1);
	printf("msgget creat ok : %d \n", msgid);
}
