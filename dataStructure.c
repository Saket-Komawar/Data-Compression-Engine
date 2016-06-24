#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


void init(list *l){
	l->head = NULL;
	l->cnt = 0;
}

void traverse(list *l){
	node *current;
	current = l->head;
	while(current != NULL){
		printf("%c:%d\n", current->letter, current->frequency);
		current = current->next;
	}
}

void append(list *l, char letter){
	node *tmp = (node *)malloc(sizeof(node));
	tmp->letter = letter;
	tmp->frequency = 1;
	tmp->flag = 1;
	tmp->next = NULL;
	tmp->left = tmp->right =NULL;

	node *current;
	current = l->head;

	if(l->cnt == 0){
		l->head = tmp;
	}
	else{
		while(current->next != NULL){
			current = current->next;
		}
		current->next = tmp;
	}
	l->cnt++;
}

void searchAndAdd(list *l, char letter){
	node *search = l->head;
	while(search->letter != letter){
		search = search->next;
		if(search == NULL){
			append(l, letter);
			return;
		}
	}
	search->frequency++;
}