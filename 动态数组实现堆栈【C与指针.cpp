#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>

#define STACK_TYPE int
void push(STACK_TYPE value);
void pop(void);
STACK_TYPE top(void);
int is_empty(void);
int is_full(void);
void create_stack(size_t size);
void destory_stack(void);

static STACK_TYPE *stack;
static size_t stack_size;
static int top_element=-1;

int main()
{
	system("pause");
	return 0;
}

void create_stack(size_t size)
{
	assert(stack_size==0);
	stack_size =size;
	stack=(STACK_TYPE *)malloc(stack_size*sizeof(STACK_TYPE));
	assert(stack!=NULL);
}

void destory_stack(void)
{
	assert(stack_size>0);
	stack_size=0;
	free(stack);
	stack=NULL;
}

void push(STACK_TYPE value)
{
	assert(!is_full());
	top_element+=1;
	stack[top_element]=value;
}

void pop(void)
{
	assert(!is_empty());
	top_element-=1;
}

STACK_TYPE top(void)
{
	assert(!is_empty());
	return stack[top_element];
}

int is_empty(void)
{
	assert(stack_size>0);
	return top_element==-1;
}

int is_full(void)
{
	assert(stack_size>0);
	return top_element==stack_size-1;
}

