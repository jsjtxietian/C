#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DRIVER 1
#define MAX 10001
#define NUM 30

char *BruteSearch(const char *text,const char *string)
{
	int len =strlen(string);
	for(;*text;text++)
	   if(strncmp(text,string,len)==0)
	      return ((char *)text);
    return NULL;
}

#ifdef DRIVER

int main()
{
	char *search_for=(char *)malloc(NUM);
	char *site;
	char *buffer=(char *)calloc(1,MAX);
	
	if(buffer==NULL || search_for==NULL)
	{
		fprintf(stderr,"∑÷≈‰ƒ⁄¥Ê ß∞‹\n");
		exit(1);
	}
	
	printf("Please input the text:\n");
	fgets(buffer,MAX,stdin);
	printf("please input the string that ypu want to search:\n");
	fscanf(stdin,"%s",search_for);
	
	site=BruteSearch(buffer,search_for);
	if(site==NULL)
	  printf("%s NOT FOUND\n",search_for);
	else
	{
		char solution[31];
		strncpy(solution,site,30);
		solution[30]='\0';
		printf("\nFound:\n%s\n",solution);
	}
	
	system("pause");
	return 0;
}
#endif
