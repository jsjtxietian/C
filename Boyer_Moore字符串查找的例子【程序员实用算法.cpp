#define DRIVER 1
//#define DEBUG 1 

#if defined(DEBUG)
#define SHOWCHAR for(uT=1;uT<=PatLen;uT++)\
                   printf(" %c ",String[uT-1])
#define SHOWJUMP for(uT=1;uT<=PatLen;uT++)\
                   printf("%2d ",MatchJump[uT])
#define SHOWA printf("  uA=&u   ",uA)
#define SHOWB printf("  uB=%u",uB)
#define SHOWBACK for(uT=1;uT<=PatLen;uT++)\
                   printf("%2d ",BackUp[uT])
#define NL printf("\n")
unsigned uT;
#else
#define SHOWCHAR 
#define SHOWJUMP 
#define SHOWA 
#define SHOWB 
#define SHOWBACK 
#define NL 
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define AlphabetSize (UCHAR_MAX+1)

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

char *BoyerMoore (const char *String,const char *Text,size_t TextLen)
{
	unsigned CharJump[AlphabetSize];
	unsigned *MatchJump;
	unsigned *BackUp;
	size_t PatLen;
	unsigned u,uText,uPat,uA,uB;
	
	PatLen=strlen(String);
	MatchJump=(unsigned *)malloc(2*sizeof (unsigned)*(PatLen+1));
	BackUp=MatchJump+PatLen+1;
	
	memset(CharJump,0,AlphabetSize*sizeof(unsigned));
	for(u=0;u<PatLen;u++)
	   CharJump[((unsigned char)String[u])]=PatLen-u-1;
	for(u=1;u<=PatLen;u++) 
	   MatchJump[u]=2*PatLen-u;
	SHOWCHAR;NL;
	SHOWJUMP;NL;
	
	u=PatLen;
	uA=PatLen+1;
	while(u>0)
	{
		BackUp[u]=uA;
		while(uA<=PatLen && String[u-1]!=String[uA-1])
		{
			if(MatchJump[uA]>PatLen-u)
			   MatchJump[uA]=PatLen-u;
			uA=BackUp[uA];
		}
		u--;
		uA--;
	}
	
	SHOWJUMP;SHOWA;
	SHOWBACK;NL;
	
	for(u=1;u<=uA;u++)
	{
		if(MatchJump[u]>PatLen+uA-u)
			MatchJump[uA]=PatLen+uA-u;
	}
	
	uB=BackUp[uA];
	SHOWJUMP;SHOWB;NL;
	
	while (uA<=PatLen)
	{
		while(uA<=uB)
		{
			if(MatchJump[uA]>PatLen-uA+uB)
			   MatchJump[uA]=PatLen-uA+uB;
			uA++;
		}
		uB=BackUp[uB];
	}
	
	SHOWJUMP;NL;
	
	uPat=PatLen;
	uText=PatLen-1;
	while(uText<TextLen && uPat!=0)
	{
		if(Text[uText]==String[uPat-1])
	    {
	    	uText--;
	    	uPat--;
		}
	    else
	    {
	    	uA=CharJump[((unsigned char)Text[uText])];
	    	uB=MatchJump[uPat];
	    	uText+=max(uA,uB);
	    	uPat=PatLen;
		}
	} 
	
	if(uPat==0)
	  return ((char *)(Text+(uText +1)));
	else
	  return NULL;  
}
#ifdef DRIVER
#define MAX_TEXT_SIZE 10000u
#define SEARCH_SIZE 10
int main(int argc,char *argv[])
{
	char *SearchFor,*Filename;
	FILE *Fin; 
	char *Buffer;
	char *start,*p;
	int i;
	size_t TextSize;
	unsigned count;
	
    if(argc!=3)
    {
    	puts("Usage is:boyermor search-string filename\n");
    	system("pause"); 
    	exit(1);
	}
	else
	{
		SearchFor=argv[1];
		Filename=argv[2];
	}
	if((Fin=fopen(Filename,"r"))==NULL)
	{
		fprintf(stderr,"Can't open %s",Filename);
		system("pause");
		exit(1);
	}
	
	Buffer=(char *)malloc(MAX_TEXT_SIZE+1);
	if(Buffer==NULL)
	{
		fprintf(stderr,"Can't malloc enough space");
		system("pause");
		exit(1);
	}
	
	TextSize=fread(Buffer,1,MAX_TEXT_SIZE,Fin);
	fclose(Fin);
	
    p=Buffer;
    count=0;
    while(count<TextSize)
    {
    	if(*p=='\n')
    	  *p='\0';
    	p++;
    	count++;
	}
	
	start=BoyerMoore(SearchFor,Buffer,TextSize);
	if(start==NULL)
	  printf("\n%s Not Found.\n",SearchFor);
	else
	  while(start!=NULL)
	  {
	  	for(p=start;;p--)
	  	{
	  		if(*p=='\0')
	  		{
	  			p++;
	  			break;
			}
			else
			{
				if(p==Buffer)
				  break;
			}
			printf("Found:\n%s\n",p);
			for(i=start-p;i>0;i--)
			   fputc(' ',stdout);
			printf("%s\n\n",SearchFor);
		    start=BoyerMoore(SearchFor,start+1,TextSize-(start-Buffer)-1);
		}
	  }
    system("pause");
	return 0;
}
#endif


