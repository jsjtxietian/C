#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

#define  MAXWORD   256
#define  hashnum  1024

typedef struct list //�������� 
{
	int count;
	struct list  *next;
	char str[0];
}Hashlist;

typedef struct Hash//��ϣ�� 
{
	int count;
	Hashlist *list;
}Hash_table;


Hash_table hash_table[hashnum];
char buffer[256];//��ʱ���� 
int tail_prob;//��β 



void initial_buffer()//��ʼ�� 
{
	for(tail_prob=0;tail_prob<MAXWORD;tail_prob++)
	{
		buffer[tail_prob]='\0';
	}
	tail_prob=0;
}

void initial_hashtable()//��ʼ�� 
{
	int i=0;
	while(i<hashnum)
	{
		hash_table[i].count=0;
		i++;
	}
}

void copybuffer(char character)//д����ʱ���� 
{
	if(tail_prob>=MAXWORD)
	{
		printf("it is too long,maybe you should cut it into some piece\n");
		exit(1);
	} 
	buffer[tail_prob++]=character;
}

void clear_buffer()//�����ʱ���� 
{
	while(tail_prob!=0)
	  buffer[tail_prob--]='\0';
}

unsigned int get_key (char *str)//�����ϣֵ 
{
    unsigned result = 0;
    do
    {
       result = result + (*str);
       str++;
    }while (*str != NULL);//
    result = result % hashnum;
    return result;
}

void print_hash_list(Hashlist * list)
{
   	while(list!=NULL)
	{
		printf("%s  ������%d��\n",list->str,list->count);
		list=list->next;
	}
}


void print_hash()//��ӡ��ϣ�� 
{
	int i;
	for(i=0;i<hashnum;i++)
	{
		if(hash_table[i].count !=0)
		{
			print_hash_list(hash_table[i].list);
		}
		  
	}
} 

void find_match(Hashlist *list)//��������������ж� �������count++������ȼ������� 
{
	while(list!=NULL)
	{
		if(strcmp(buffer,list->str)==0)
	    {
	    	list->count++;
	    	return ;
		}
		list=list->next;
	}
	Hashlist *temp=(Hashlist *)malloc(sizeof(Hashlist)+strlen(buffer));//?
	if(temp==NULL)
	{
		printf("�����ڴ�ʧ�ܣ���������������\n");
		system("pause");
		exit(1);
	}
	temp->next=NULL;
	strcpy(temp->str,buffer);
	temp->count=1;
	list=temp;
}

void add_to_hash()
{
	unsigned int key=get_key(buffer);
	if(hash_table[key].count==0)
	{
		Hashlist *temp=(Hashlist *)malloc(sizeof(Hashlist)+strlen(buffer));//?
		if(temp==NULL)
		{
			printf("�����ڴ�ʧ�ܣ���������������\n");
			system("pause");
			exit(1);
		}
		temp->next=NULL;
		strcpy(temp->str,buffer);
		temp->count=1;
		hash_table[key].list=temp;
	}
	else
	{
		find_match(hash_table[key].list);
	}
	hash_table[key].count++;
}

int main()
{
	initial_buffer();
	initial_hashtable();
	char c;
	printf("Please input your English article:\n"); 
	while((c=getchar())!='\n')
	{
		if(c>='A'&& c<='Z' || c>='a'&&c<='z' || c>='0'&&c<='9')
		{
			copybuffer(c);
		}
		else
		{
			if(strlen(buffer)==0)//��ֹһ��ʼ�б����� 
				continue;
			else
			{
				add_to_hash(); 
		     	clear_buffer();
			}
		}
	} 
	
	add_to_hash(); //����buffer 
	clear_buffer();
	
	print_hash();
	system("pause");
	return 0; 
} 

