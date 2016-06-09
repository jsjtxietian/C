#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

#define  MAXWORD   256
#define  hashnum  1024

typedef struct list //下拉链表 
{
	int count;
	struct list  *next;
	char str[0];
}Hashlist;

typedef struct Hash//哈希表 
{
	int count;
	Hashlist *list;
}Hash_table;


Hash_table hash_table[hashnum];
char buffer[256];//临时数组 
int tail_prob;//结尾 



void initial_buffer()//初始化 
{
	for(tail_prob=0;tail_prob<MAXWORD;tail_prob++)
	{
		buffer[tail_prob]='\0';
	}
	tail_prob=0;
}

void initial_hashtable()//初始化 
{
	int i=0;
	while(i<hashnum)
	{
		hash_table[i].count=0;
		i++;
	}
}

void copybuffer(char character)//写入临时数组 
{
	if(tail_prob>=MAXWORD)
	{
		printf("it is too long,maybe you should cut it into some piece\n");
		exit(1);
	} 
	buffer[tail_prob++]=character;
}

void clear_buffer()//清空临时数组 
{
	while(tail_prob!=0)
	  buffer[tail_prob--]='\0';
}

unsigned int get_key (char *str)//计算哈希值 
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
		printf("%s  出现了%d次\n",list->str,list->count);
		list=list->next;
	}
}


void print_hash()//打印哈希表 
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

void find_match(Hashlist *list)//对下拉链表进行判断 若相等则count++，不想等继续下拉 
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
		printf("分配内存失败，请重新启动尝试\n");
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
			printf("分配内存失败，请重新启动尝试\n");
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
			if(strlen(buffer)==0)//防止一开始有标点符号 
				continue;
			else
			{
				add_to_hash(); 
		     	clear_buffer();
			}
		}
	} 
	
	add_to_hash(); //最后的buffer 
	clear_buffer();
	
	print_hash();
	system("pause");
	return 0; 
} 

