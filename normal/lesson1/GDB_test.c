/*hello user*/
#include <stdio.h>
#include <stdlib.h>

static int sum (int value);

struct inout{
	int value;
	int result;
};

int main(int argc, char *argv[])
{
	struct inout *io = (struct inout *)malloc(sizeof(struct inout));

	if(io == NULL)
	{
		printf("内存申请失败\n");
		return -1;
	}

	if(argc != 2)
	{
		printf("参数输入错误\n");
		return -1;
	}

	io->value = *argv[1] - '0';
	io->result = sum(io->value);
	printf("你输入的值是:%d, 计算结果为:%d\n", io->value, io->result);
	return 0;
}

static int sum(int value)
{
	int result = 0;
	int i = 0;

	for(; i < value; i++)
	{
		result += 1;
	}

	return result;
}
