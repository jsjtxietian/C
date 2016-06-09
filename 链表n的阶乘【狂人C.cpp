#include<stdio.h>
#include<stdlib.h>

#define ZX 10000000
#define DUAN struct duan
#define MAX 1001 

DUAN {
	    int shuju;
	    DUAN *xiayiduan;
     };

void tuichu(void);
void cheng(DUAN*,int);
void jinwei(DUAN**,int);
void shuchu(DUAN*);
void shifang(DUAN*); 

int main()
{
	puts("Input n:");
	int n;
	scanf("%d",&n);
	if(n<=1||n>=MAX)
	{
		printf("error!\n");
		exit(1);
	}
	else
	{
		DUAN * p_dyd=NULL;
		int i;

		p_dyd=(DUAN*)malloc(sizeof (DUAN));
		if(p_dyd==NULL)  tuichu();
		  
		p_dyd->shuju=1;
		p_dyd->xiayiduan=NULL;
		
		for(i=1;i<=n;i++)
		{
			cheng(p_dyd,i);
			jinwei(&p_dyd,0);
		}
	    shuchu(p_dyd);
	    putchar('\n');
	    shifang(p_dyd);
	    system("pause");
	    return 0;
   } 
}

void shifang(DUAN *p)
{
	if(p->xiayiduan==NULL)
	{
		free(p);
		return;
	}
	shifang(p->xiayiduan);
	free(p);
	return;
}

void tuichu(void)
{
	printf("Sorry,¿Õ¼ä²»¹»\n");
	system("pause");
	exit(1);
}

void cheng(DUAN *p,int n)
{
	if(p==NULL)
	 return ;
	p->shuju *=n;
	cheng(p->xiayiduan,n);
}

void jinwei(DUAN **p_p,int jws)
{
	if(*p_p==NULL)
	{
		if(jws!=0)
		{
			(*p_p)=(DUAN *)malloc(sizeof (DUAN));
			if(*p_p==NULL) tuichu();
			
			(*p_p)->shuju=jws;
			(*p_p)->xiayiduan=NULL;
		}
		return ;
	}
	(*p_p)->shuju +=jws;
	jinwei(&(*p_p)->xiayiduan,(*p_p)->shuju/ZX);
	(*p_p)->shuju %=ZX;
}

void shuchu(DUAN *p)
{
	if(p->xiayiduan==NULL)
	{
		printf("%d",p->shuju);
		return ;
	}
	shuchu(p->xiayiduan);
	printf("%07d",p->shuju);
	return ;
}
