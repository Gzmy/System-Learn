/*************************************************************************
	> File Name: test.c
	> Author: zmy_1370711580
	> Mail: 1370711580@qq.com 
	> Created Time: Wed 25 Jul 2018 10:36:23 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main()
{
	int i = 0;
	char buf[102] = {'#'};
	char str[] = "|-/\\";

	for (i = 1; i <= 100; i++)
	{
		buf[i] = '#';
		printf("[%-100s][%d%%][%c]\r", buf, i, str[i%4]);
		fflush(stdout);
		usleep(100000);
	}
}
