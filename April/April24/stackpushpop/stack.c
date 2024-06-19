#include"stack.h"
#include <stdbool.h>

int stack[MAX_SIZE];
int top = -1;

void push(int value)
{
	if(top >= MAX_SIZE - 1)
	{
		printf("Stack overflow\n");
		return;
	}
	top++;
	stack[top]=value;
}

int pop()
{
	if(top<0)
	{
		printf("Stack underflow\n");
		return -1;
	}
	int value = stack[top];
	top--;
	return value;
}

void stack_init()
{
	top =-1;
}

bool stack_is_full()
{
	return top >= MAX_SIZE -1;
}

bool stack_is_empty()
{
	return top < 0;
}

