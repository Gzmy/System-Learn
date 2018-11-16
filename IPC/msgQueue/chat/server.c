/*hello user*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>

struct msgbuf{
	long mtype;
	char mtext[1024];
};


int main()
{
	int id = msgget(2269, IPC_CREAT|0644);
	if(id == -1) perror("msgget"), exit(1);

	struct msgbuf mb;
	while(1){
		//读取1号消息
		memset(&mb, 0x00, sizeof(mb));
		msgrcv(id, &mb, 1024, 1, 0);
		//发送给客户端
		mb.mtype = *(int *)(mb.mtext);
		msgsnd(id, &mb, strlen(mb.mtext+sizeof(int))+sizeof(int), 0);
	}
}
