#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
	int p1,p2;
	//printf("This is exp.3\n");
	p1 = fork();
	if (p1==-1) 
		printf("error");
	else if (p1==0)
	{
		//lockf(1,1,0);
		for (int i = 0; i < 50; ++i)
		{
			
			printf("b:%d  father:%d\n",getpid(),getppid());
			
		}
		//lockf(1,0,0);
		
	}
	else 
	{
		p2 = fork();
		if (p2==0)
		{
			//lockf(1,1,0);
			for (int i = 0; i < 50; ++i)
			{

				printf("c:%d  father:%d\n",getpid(),getppid());

			}
			//lockf(1,0,0);
		}
			
		else 
		{
			//lockf(1,1,0);
			for (int i = 0; i < 50; ++i)
			{
				
				printf("a:%d\n",getpid());

			}
			//lockf(1,0,0);
			
		}
	}
}