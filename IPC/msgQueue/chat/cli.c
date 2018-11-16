/*hello user*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msgbuf{
	long mtype;
	char mtext[1024];
};


int main()
{
	int id = msgget(2269, 0);
	if(id == -1) perror("msgget"), exit(1);

	struct msgbuf mb;
	while(1){
		memset(&mb, 0x00, sizeof(int));
		mb.mtype = 1;
		*(int *)(mb.mtext) = getpid();
		//读取键盘
		char *p = fgets(mb.mtext+sizeof(int), 1024 - sizeof(int), stdin);
		if(p == NULL) break;

		//发送消息
		msgsnd(id, &mb, strlen(mb.mtext+sizeof(int))+sizeof(int), 0);
		//读取服务器
		memset(&mb, 0x00, sizeof(int));
		msgrcv(id, &mb, 1024, getpid(), 0);
		//显示到屏幕
		printf(" :%s\n", mb.mtext+sizeof(int));
	}
}
