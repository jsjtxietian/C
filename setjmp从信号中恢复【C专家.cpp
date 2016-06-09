#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>
#include<signal.h>

jmp_buf buf;
void handler(int s)
{
	if(s==SIGINT)//sigint   ctrl+c
	  printf("now get a SIGNIT signal\n");
	longjmp(buf,1);
}

int main()
{
	signal(SIGINT,handler);
	if(setjmp(buf))
	{
		printf("back in main\n");
		system("pause");
		return 0;
	}
	else 
	{
		printf("first time through\n");
	}
	loop:
		goto loop;
}
