#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_SIZE 100

void push(int value);
int pop();
void stack_init();
bool stack_is_full();
bool stack_is_empty();
