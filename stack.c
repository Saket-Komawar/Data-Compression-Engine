#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void stackInit(stack *s){
	s->i = 0;
}

void push(stack *s, node data){
	s->array[s->i] = data;
	s->i++;
}

node* pop(stack *s){
	node* tmp;
	tmp = &(s->array[(s->i) - 1]);
	s->i--;
	return tmp;
}

int isStackEmpty(stack *s){
	return (s->i) == 0;
}

int isStackFull(stack *s){
	return (s->i) == MAX;
}