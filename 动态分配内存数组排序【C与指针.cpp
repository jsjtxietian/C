//动态分配内存读取并排序 
#include<stdio.h>
#include<stdlib.h>

int compare_integers(const void *a,void const *b)
{
	register int const *pa=(int *)a;
	register int const *pb=(int *)b;
	return *pa>*pb?1:*pa<*pb?-1:0;
}

int main()
{
	int *array;
	int n_values;
	int i;
	
	printf("How many values are there?");
	if(scanf("%d",&n_values)!=1||n_values<=0)
	{
		printf("Illegal number of values.\n");
		exit(EXIT_FAILURE);
	}
	
	array=(int *)malloc(n_values * sizeof(int));
	if(array==NULL)
	{
		printf("Can't get memory for that many values.\n'");
		exit(EXIT_FAILURE);
	}
	
	for(i=0;i<n_values;i+=1)
	{
		printf("？ "); 
		if(scanf("%d",array+i)!=1)
		{
			printf("Error raeding value #%d\n",i);
			free(array);
			exit(EXIT_FAILURE);
		} 
	}
	
	qsort(array,n_values,sizeof(int),compare_integers);
	
	for(i=0;i<n_values;i++)
	   printf("%d ",array[i]);
	 
    free(array);
    return EXIT_SUCCESS;
} 






