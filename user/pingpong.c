//pingpong
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
	int p1[2],p2[2];
	pipe(p1);
	pipe(p2);
	
	if(fork() == 0)
	{
		char buf[1];
		while(1)
		{
			close(p1[1]);
			close(p2[0]);
			if(read(p1[0],buf,sizeof(buf)))
			{
				int pid = getpid();
				printf("<%d>:received ping\n",pid);
				write(p2[1],"A",1);
				close(p1[0]);
				close(p2[1]);
				exit(0);
			}
		}
	}
	else
	{
		char buf1[1];
		close(p1[0]);
		close(p2[1]);
		write(p1[1],"A",1);
		while(1)
		{
	  	if(read(p2[0],buf1,sizeof(buf1)))
			{
				int pid1 = getpid();
				printf("<%d>:received pong\n",pid1);
				close(p1[1]);
				close(p2[0]);
				exit(0);
			}
		}
		
	}
}
