#include<stdio.h>
#include<setjmp.h>
#include<stdlib.h>
jmp_buf buf;

void banana()
{
	printf("in banana()\n");
	longjmp(buf,1);
	printf("你看不见我"); 
} 

int main ()
{
	if(setjmp(buf))
	   printf("back in main\n");
	else
	{
		printf("first time through\n");
		banana();
	}
	system("pause"); 
	return 0;
} 
