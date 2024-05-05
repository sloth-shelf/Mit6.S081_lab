//prime
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int p[])
{
	int buf[33];
	close(p[1]);
	int n = 0,i;
	int *ptr = buf;
	while(1)
	{
		i = read(p[0],ptr,sizeof(int)*33);
		i = i / sizeof(int);
		ptr = ptr+i;
		if(i == 0)
			break;
		else
		{
			n = n+i;
		}
	}
	close(p[0]);
	printf("prime: %d\n",buf[0]);
	

	if(n == 1)
	{
		;
	}
	else
	{
		int a = buf[0];
		int p1[2];
		pipe(p1);
		int pid = fork();
		if(pid == 0)
		{
			prime(p1);
		}
		else
		{
			close(p1[0]);
			for(int i = 1;i<n;i++)
      {
        if(buf[i] % a != 0)
        {
          write(p1[1],buf+i,sizeof(int));
        }
      }
      close(p1[1]);
			wait(0);
		}
	}
}

int main()
{
	int p[2];
	pipe(p);
	if(fork() == 0)
	{
		prime(p);
	}
	else
	{
		close(p[0]);
		for(int i = 2;i<=35;i++)
    {
      //int r;
      write(p[1],&i,sizeof(int));
      //printf("%d\n",r);
    }
    close(p[1]);
		wait(0);
		exit(0);
	}
	exit(0);
}
