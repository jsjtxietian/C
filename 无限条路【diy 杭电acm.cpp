#include<stdio.h>
#include<stdlib.h>
#include<math.h>
 
 //¾«¶È£¿£¿£¿£¿ 
 
double jisuan(int a1,int b1,int a2,int b2);

int main()
{
	int  a1,a2,b1,b2;
	xt:scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
	if((a1+b1)>(a2+b2))
	{
		int i,j;
		i=a1;
		j=b1;
		a1=a2;
		b1=b2;
		a2=i;
		b2=j;
	}
	printf("%f\n",jisuan(a1,b1,a2,b2));
	goto xt;
	return 0;
} 

double jisuan(int a1,int b1,int a2,int b2)
{
	if((a1+b1)==(a2+b2))
    	return sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2));
    else
        return sqrt(b1*b1+b1*b1) + sqrt((a1+b1+1)*(a1+b1+1)+(a1+b1)*(a1*b1)) + jisuan(0,a1+b1+1,a2,b2);  
}
