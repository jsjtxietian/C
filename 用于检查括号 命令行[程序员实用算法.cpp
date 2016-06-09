//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack【程序员实用算法.cpp" 

int main(int argc,char *argv[])
{
	FILE *fin;//将要读取的文件 
	char buffer[128];
	
	int line_count;
	struct StkElement *stk_el;
	Stack *stk;
	char ch;
	int i;
	
	if(argc!=2)
	{
		fprintf(stderr,"Usage:braces filename.ext\n");
		exit(1);
	}
	
	fin=fopen(argv[1],"rt");
	if(fin==NULL)
	{
		fprintf(stderr,"Cannot open/find %s\n",argv[1]);
		exit(1);
	}
	
	stk=CreateStack(40);
	if(stk==NULL)
	{
		fprintf(stderr,"Insufficient memory\n");
		exit(1);
	}
	
	stk_el=(struct StkElement *)malloc(sizeof(struct StkElement));
	if(stk_el==NULL)
	{
		fprintf(stderr,"Insufficient memory\n");
		exit(1);
	}
	
	line_count=0;
	
	while(!feof(fin))
	{
		if(fgets(buffer,127,fin)==NULL)
		  break;
		line_count+=1;
		
		for(i=0;buffer[i]!='\0';i++)
		{
			switch (ch=buffer[i])
			{
				case '(': 
				case '[':
				case '{':
				  stk_el->opener=ch;
				  stk_el->line_no=line_count;
				  if(!PushElement(stk,stk_el))
				  {
				  	fprintf(stderr,"Out of the stack place\n");
				  	exit(EXIT_FAILURE);
				  }
				  break;
				case ')': 
				case ']':
				case '}':
				  if(!PopElement(stk,stk_el))
				    fprintf(stderr,"Stray %c at line %d\n",ch,line_count);
				  else
				    if((ch=='(' && stk_el->opener!= '(') || 
					  (ch==']' && stk_el->opener!= '[')||
					  (ch=='}' && stk_el->opener!= '{')) 
					  fprintf(stderr,"%c at line %d not matck by %c at line %d\n",
					        ch,line_count,stk_el->opener,stk_el->line_no);
					        break;
				default:
				    continue;
			} 
		}
	}
	
	if(ViewElement(stk,0)!=NULL)
	  while(PopElement(stk,stk_el)!=0)
	     fprintf(stderr,"%c from line %d unmatched\n",stk_el->opener,stk_el->line_no);
	fprintf(stderr,"Error checking complete\n");   
	fclose(fin);
	return (EXIT_SUCCESS);
}
