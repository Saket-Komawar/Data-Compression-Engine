#include "functions.h"
#define MAX 1024


typedef struct stack{
	int i;
	node array[MAX];
}stack;


void stackInit(stack *s);
void push(stack *s, node data);
node* pop(stack *s);
int isStackEmpty(stack *s);
int isStackFull(stack *s);