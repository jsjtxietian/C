//c语言写汉语分词   
//哈希散列表存储字典
//逆向排序搜索+栈的使用（尚未实现） 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//默认没有标点 默认最长的四字短语  
#define ZIDIAN 1000 //字典词数 
#define HASH_LEN  39841//定义散列表大小
#define STACK_LEN 100 //定义栈大小
#define MAX 5 //最大匹配字数

typedef struct hash_node
{
    char *data;
    struct hash_node *next;
}HASH_NODE; //散列表下拉链表结果


typedef struct
{
    int len;
    HASH_NODE *data;
}HASH; //散列表数据结构


typedef struct
{
    int len;
    char *data[STACK_LEN];
}STACK; //栈数据结构

void hash_init(HASH *hash);//初始化 
void hash_list_insert(HASH_NODE *data,char *key); 
void hash_insert(HASH *hash,char *key); //写入 散列表 
void load_data(HASH *hash); //文本读入 
unsigned int hash_fun(char *key);   //修改  计算哈希 
void hash_print(HASH *hash);//打印 
void hash_list_print(HASH_NODE *);
char *hash_get(HASH *hash,char *key);//查找 
char *hash_node_key(HASH_NODE *node,char *key);
int hash_in(HASH *hash,char *key);
int hash_node_in(HASH_NODE *node,char *key);
void stack_init(STACK *stack);
int stack_push(STACK *stack,char *data);
char *stack_pop(STACK *stack);



int main ()
{
    HASH hash[HASH_LEN];
    load_data(hash);
    hash_print(hash); //print出来的都是最后一个字符串 
    
    system("pause");
    return 0;
} 

void hash_print(HASH *hash)
{
    int i;

    for(i=0;i != HASH_LEN;i++)
    {
        if(hash[i].len != 0)
        {
            hash_list_print(hash[i].data);
            printf("\n");
        }
    }
}

void hash_list_print(HASH_NODE *data)
{
    while(data != NULL)
    {
        printf("%s ",data->data);
        data=data->next;
    }
}

char *hash_get(HASH *hash,char *key)
{
	int h=hash_fun(key)%HASH_LEN;
	if(hash[h].len==0)
	  return NULL;
    else
	  return hash_node_key(hash[h].data,key); 
}

void hash_init(HASH *hash)   //哈希初始化 
{
	for(int i=0;i!=HASH_LEN;i++)
	  hash[i].len=0;
} 

char *hash_node_key(HASH_NODE *node,char *key)//查找key 
{
    while(node!=NULL)
    {
        if(strcmp(node->data,key) == 0)
            return node->data;
        
        node=node->next;
    }
    
    return NULL;
}

//从表中搜索关键词
//如若存在则返回1
//否则返回0
int hash_in(HASH *hash,char *key)
{
    int h;

    h=hash_fun(key)%HASH_LEN;
    if(hash[h].len == 0)
        return 0;

    return hash_node_in(hash[h].data,key);
}

//判断数据是否在该表中
int hash_node_in(HASH_NODE *node,char *key)
{
    while(node)
    {
        if(strcmp(node->data,key) == 0)
            return 1;

        node=node->next;
    }

    return 0;
}

//冲突时拉下链表
void hash_list_insert(HASH_NODE *data,char *key)
{
    HASH_NODE *temp;

    while(data->next != NULL)
        data=data->next;

    temp=(HASH_NODE *)malloc(sizeof(HASH_NODE));
    temp->data=key;
    temp->next=NULL;
    data->next=temp;
}


void hash_insert(HASH *hash,char *key)
{
    int h;
    h=hash_fun(key)%HASH_LEN;
    //如果当前表中没有数据则直接插入
    //否则插入链表中
    if(hash[h].len > 0)
        hash_list_insert(hash[h].data,key);
    else
    {
        hash[h].data=(HASH_NODE *)malloc(sizeof(HASH_NODE));//每次都一样  !!!!!!!!!!!!!!!!!!!!!!!
        hash[h].data->data=key;
        hash[h].data->next=NULL;
    }
    //当前表中数据值加1
    ++hash[h].len;
}


void load_data(HASH *hash) //文本读入 
{
	int i=0;
	FILE *fp;
	fp=fopen("D:\\现代汉语常用词表.txt","r");//文件读入 
	if(fp==NULL)
	{
		printf("FAILED\n");
		exit(1);
	}
	else
	{
		char *temp1=(char *)malloc(sizeof(char)*9);  
		char *temp2;
		for(i=0;1<ZIDIAN;i++)
		{
			if(fscanf(fp,"%s",temp1)==1 && temp1!=NULL)
			{
				temp2=(char *)malloc(strlen(temp1)+1);
				strcpy(temp2,temp1);
				free(temp1);
				hash_insert(hash,temp2);
			}
			else
			  break;
		}
	}

	fclose(fp);
} 


unsigned int hash_fun(char *key)   //修改  计算哈希 
{
    unsigned int seed=131;
    unsigned int hash=0;
    while(*key)
    {
        hash=hash*seed+*key;
        ++key;
    }
    return hash&0x7FFFFFFF;
}

//初始化栈
void stack_init(STACK *stack)
{
    int i;

    //栈数据置零
    stack->len=0;
    for(i=0;i != STACK_LEN;++i)
        stack->data[i]=NULL;
}

//压入一个数据到栈中
int stack_push(STACK *stack,char *data)
{
    if(stack->len >= STACK_LEN)
        return 0;

    stack->data[stack->len]=data;
    ++stack->len;
}

//从栈中弹出一个数据
char *stack_pop(STACK *stack)
{
    if(stack->len <= 0)
        return NULL;

    --stack->len;
    return stack->data[stack->len];
}

