#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>

#define MAX 1024

static void usage(const char *proc)
{
	printf("Usage %s [port]\n", proc);
}

static int startup(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
		perror("bind");
		exit(3);
	}

	if(listen(sock, 5) < 0){
		perror("listen");
		exit(4);
	}

	return sock;
}

static int getLine(int sock, char line[], int len)
{
	char c = 'a';
	int i = 0;
	while(c != '\n' && i < len-1){
		ssize_t s = recv(sock, &c, 1, 0);
		if(c == '\r'){
			recv(sock, &c, 1, MSG_PEEK); //窥探功能
			if(c == '\n'){
				recv(sock, &c, 1, 0);
			}else{
				c = '\n';
			}
		}
		//\r\n \r->\n
		line[i++] = c;
	}
	line[i] = '\0';

	return i;
}

static void clearHeaer(int sock) //清理头部
{
	char line[MAX];
	do{
		getLine(sock, line, sizeof(line));
	}while(strcmp("\n", line));
}

static void echoErrMsg(int sock, int status_code)
{
}

void *handlerRequest(void *arg)
{
	int sock = (int)arg;

	int status_code = 200;
	char line[MAX];
	char method[MAX/16];
	char url[MAX];

	getLine(sock, line, sizeof(line));
	printf("%s", line);

	int i = 0;
	int j = 0;
	while(i < sizeof(method)-1 && j < sizeof(line) && !isspace(line[j])){
		method[i++] = line[j++];
	}
	method[i] = '\0';

	while(j < sizeof(line) && isspace(line[j])){
		j++;
	}

	i = 0;
	while(i < sizeof(url)-1 && j < sizeof(line) && !isspace(line[j])){
		url[i++] = line[j++];
	}

	url[i] = '\0';

	printf("method:%s, url:%s\n", method, url);

	if(strcasecmp(method, "GET") == 0){
	}
	else if(strcasecmp(method, "POST") == 0){
	}
	else{ //method error
		status_code = 404;
		clearHeaer(sock); //清理头部
		goto end;
	}

end:
	if(status_code != 200){
		echoErrMsg(sock, status_code);
	}
	close(sock);
}

int main(int argc, char *argv[])
{
	if(argc != 2){
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(atoi(argv[1]));
	for(;;){
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		int sock = accept(listen_sock, (struct sockaddr*)&client, &len);
		if(sock < 0){
			perror("accept");
			continue;
		}

		pthread_t tid;
		pthread_create(&tid, NULL, handlerRequest, (void *)sock);
		pthread_detach(tid);
		//pthread_join(tid, NULL);
	}
}
