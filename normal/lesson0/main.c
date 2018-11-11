/*************************************************************************
	> File Name: main.c
	> Author: zmy_1370711580
	> Mail: 1370711580@qq.com 
	> Created Time: Tue 17 Jul 2018 02:02:40 AM EDT
 ************************************************************************/

#include<stdio.h>
#include"add.h"
#include"sub.h"

int main()
{
	int a = 10;
	int b = 20;
	printf("add(%d, %d) = %d\n", a, b, add(a, b));
	a = 100;
	b = 20;
	printf("sub(%d, %d) = %d\n", a, b, sub(a, b));
	return 0;
}
