//c����д����ִ�   
//��ϣɢ�б�洢�ֵ�
//������������+ջ��ʹ�ã���δʵ�֣� 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Ĭ��û�б�� Ĭ��������ֶ���  
#define ZIDIAN 1000 //�ֵ���� 
#define HASH_LEN  39841//����ɢ�б��С
#define STACK_LEN 100 //����ջ��С
#define MAX 5 //���ƥ������

typedef struct hash_node
{
    char *data;
    struct hash_node *next;
}HASH_NODE; //ɢ�б�����������


typedef struct
{
    int len;
    HASH_NODE *data;
}HASH; //ɢ�б����ݽṹ


typedef struct
{
    int len;
    char *data[STACK_LEN];
}STACK; //ջ���ݽṹ

void hash_init(HASH *hash);//��ʼ�� 
void hash_list_insert(HASH_NODE *data,char *key); 
void hash_insert(HASH *hash,char *key); //д�� ɢ�б� 
void load_data(HASH *hash); //�ı����� 
unsigned int hash_fun(char *key);   //�޸�  �����ϣ 
void hash_print(HASH *hash);//��ӡ 
void hash_list_print(HASH_NODE *);
char *hash_get(HASH *hash,char *key);//���� 
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
    hash_print(hash); //print�����Ķ������һ���ַ��� 
    
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

void hash_init(HASH *hash)   //��ϣ��ʼ�� 
{
	for(int i=0;i!=HASH_LEN;i++)
	  hash[i].len=0;
} 

char *hash_node_key(HASH_NODE *node,char *key)//����key 
{
    while(node!=NULL)
    {
        if(strcmp(node->data,key) == 0)
            return node->data;
        
        node=node->next;
    }
    
    return NULL;
}

//�ӱ��������ؼ���
//���������򷵻�1
//���򷵻�0
int hash_in(HASH *hash,char *key)
{
    int h;

    h=hash_fun(key)%HASH_LEN;
    if(hash[h].len == 0)
        return 0;

    return hash_node_in(hash[h].data,key);
}

//�ж������Ƿ��ڸñ���
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

//��ͻʱ��������
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
    //�����ǰ����û��������ֱ�Ӳ���
    //�������������
    if(hash[h].len > 0)
        hash_list_insert(hash[h].data,key);
    else
    {
        hash[h].data=(HASH_NODE *)malloc(sizeof(HASH_NODE));//ÿ�ζ�һ��  !!!!!!!!!!!!!!!!!!!!!!!
        hash[h].data->data=key;
        hash[h].data->next=NULL;
    }
    //��ǰ��������ֵ��1
    ++hash[h].len;
}


void load_data(HASH *hash) //�ı����� 
{
	int i=0;
	FILE *fp;
	fp=fopen("D:\\�ִ����ﳣ�ôʱ�.txt","r");//�ļ����� 
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


unsigned int hash_fun(char *key)   //�޸�  �����ϣ 
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

//��ʼ��ջ
void stack_init(STACK *stack)
{
    int i;

    //ջ��������
    stack->len=0;
    for(i=0;i != STACK_LEN;++i)
        stack->data[i]=NULL;
}

//ѹ��һ�����ݵ�ջ��
int stack_push(STACK *stack,char *data)
{
    if(stack->len >= STACK_LEN)
        return 0;

    stack->data[stack->len]=data;
    ++stack->len;
}

//��ջ�е���һ������
char *stack_pop(STACK *stack)
{
    if(stack->len <= 0)
        return NULL;

    --stack->len;
    return stack->data[stack->len];
}

