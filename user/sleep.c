//sleep
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int n;
	if(argc == 1)
	{
		printf("failed!\n");
		exit(0);
	}
	else if(argc == 2)
	{
		char *p = argv[1];
		while(*p)
		{
			if(*p < '0' || *p > '9')
			{
					printf("illegal argument\n");
					exit(0);
			}
			p++;
		}
		n = atoi(argv[1]);
		if(sleep(n) == 0)
		{
			printf("OK!\n");
			exit(0);
		}
		else
		{
			printf("failed!\n");
			exit(0);			
		}
	}
	else
	{
		printf("too many parameters!\n");
		exit(1);
	}
}