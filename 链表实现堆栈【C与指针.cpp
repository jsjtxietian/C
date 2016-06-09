#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>

#define FALSE 0
#define STACK_TYPE int  
void push(STACK_TYPE value);
void pop(void);
STACK_TYPE top(void);
int is_empty(void);
int is_full(void);
void destory_stack(void);

typedef struct STACK_NODE
{
	STACK_TYPE value;
	struct STACK_NODE *next;
}StackNode;

static StackNode *stack;//��һ���ڵ� 

int main()
{
	system("pause");
	return 0;
}

void destory_stack(void)
{
	while (!is_empty())
	   pop();
}

void push(STACK_TYPE value)
{
	StackNode *new_node;
	new_node=(StackNode*)malloc(sizeof(StackNode));
	assert(new_node!=NULL);
	new_node->value=value;
	new_node->next=stack;
	stack=new_node;
}


void pop(void)
{
	StackNode *first_node;
	
	assert(!is_empty());
	first_node=stack;
	stack=first_node->next;
	free(first_node);
}

STACK_TYPE top(void)
{
	assert(!is_empty());
	return stack->value;
}

int is_empty(void)
{
	return stack==NULL;
}

int is_full(void)
{
	return FALSE;
}

