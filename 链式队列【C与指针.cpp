#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define QUEUE_TYPE int 

typedef struct QUEUE_NODE
{
	QUEUE_TYPE value;
	struct QUEUE_NODE *next;
}QueueNode;

static QueueNode *front;
static QueueNode *rear;

void insert(QUEUE_TYPE value);
void delete_(void);
QUEUE_TYPE first(void);
int is_empty(void);
void destory(void);


int main()
{
	system("pause");
	return 0;
}
 
void destory(void)
{
	while(is_empty())
	  delete_();
} 

void insert(QUEUE_TYPE value)
{
	QueueNode *new_node;
	new_node=(QueueNode *)malloc(sizeof(QueueNode));
	assert(new_node!=NULL);
	new_node->value=value;
	new_node->next=NULL;
	if(rear==NULL)
	  front=new_node;
	else
	  rear->next=new_node;
	rear=new_node;
}

void delete_(void)
{
	QueueNode *next_node;
	assert(!is_empty());
	next_node=front->next;
	free(front);
	front=next_node;
	if(front==NULL)
	   rear =NULL;
}


QUEUE_TYPE first(void)
{
	assert(!is_empty());
	return front->value;
}

int is_empty(void)
{
	return front==NULL;
}









