#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"


void bubbleSort(list *l){
	int i, j, cnt = l->cnt;
	for(i = 0; i < cnt - 1; i++){
		node *current = l->head, *previous = current, *superPrevious = NULL;
		current = current->next;
		for(j = 0; j < (cnt - i - 1); j++){
			if(previous->frequency > current->frequency){
				previous->next = current->next;
				current->next = previous;
				if(j == 0)
					l->head = current;
				else
					superPrevious->next = current;
				superPrevious = current;
				current = previous->next;
			}
			else{
				superPrevious = previous;
				previous = current;
				current = current->next;
			}
		}
	}
}

void preOrder(node *t){
	if(t){
		if(t->flag)
			printf("%c :- %d---------->%s\n", t->letter, t->frequency, t->path);
		preOrder(t->left);
		preOrder(t->right);
	}
}

list* huffmanTree(list *l){
	int i, cnt = l->cnt;
	list *huffList = (list *)malloc(sizeof(list));
	init(huffList);
	huffList->head = l->head;
	huffList->cnt = l->cnt;
	node *second, *first;
	for(i = 0; i < (cnt - 1); i++){
		first = huffList->head;
		second = first;
		first = first->next;
		node *tmp = (node *)malloc(sizeof(node));
		tmp->frequency = first->frequency + second->frequency;
		tmp->next = first->next;
		tmp->flag = 0;
		tmp->left = second;
		tmp->right = first;
		huffList->head = tmp;
		huffList->cnt--;
		bubbleSort(huffList);
	}
	huffList->cnt = l->cnt;
	return huffList;
}

void appendPath(char *array, char c){
	int i = 0;
	while(array[i] != '\0')
		i++;
	array[i++] = c;
	array[i] = '\0';
}

void assignPath(list *l){
	stack *s = (stack *)malloc(sizeof(stack));
	stackInit(s);

	char *charArray = (char *)malloc(2 * MAX * sizeof(char));
	charArray[0] = '\0';
	node *root = l->head;

	while(1){
		while(root){
			strcpy(root->path, charArray);
			push(s, *root);
			root = root->left;
			if(root)
				appendPath(charArray, '0');
		}
		if(isStackEmpty(s) == 1)
			break;
		root = pop(s);
		strcpy(charArray, root->path);
		root = root->right;
		if(root)
			appendPath(charArray, '1');
	}
}

void storePath(node *t, path *paths){
	int i = 0;
	stack *s = (stack *)malloc(sizeof(stack));
	stackInit(s);

	node *root = t;

	while(1){
		while(root){
			if(root->flag){
				paths[i].c = root->letter;
				strcpy(paths[i].path, root->path);
				i++;
			}
			push(s, *root);
			root = root->left;
		}
		if(isStackEmpty(s) == 1)
			break;
		root = pop(s);
		root = root->right;
	}
}

void storeHuffList(char *huffList, path *paths, int cnt){
	int SIZE = 1024, i, j, position = 0, dflag = 253;//11111101
	for(i = 0; i < cnt; i++){
		if(paths[i].c == '0' || paths[i].c == '1')
			huffList[position++] = (char)dflag;
		huffList[position++] = paths[i].c;
		if(position >= (SIZE - 1)){
			SIZE *= 2;
			huffList = (char *)realloc(huffList, SIZE * sizeof(char));
		}
		for(j = 0; j < strlen(paths[i].path); j++){
			huffList[position++] = paths[i].path[j];
		}
	}
	huffList[position] = '\0';
}

void binaryConversion(char *buffer, char *binary, path *paths){
	int SIZE = 1024, i, j, p = 0, position = 0, binStrLen, flag1_5 = 0, flag0_5 = 0;
	node *current;
	//Redundant Bits
	binary[position++] = '0';
	binary[position++] = '0';
	binary[position++] = '0';
	for(i = 0; i < strlen(buffer); i++){
		p = 0;
		while(paths[p].c != buffer[i])
			p++;
		for(j = 0; j < strlen(paths[p].path); j++){
			binary[position++] = paths[p].path[j];
			if(position >= (SIZE - 1)){
				SIZE *= 2;
				binary = (char *)realloc(binary, SIZE * sizeof(char));
			}
			//To identify various Flags
			if(binary[position - 1] == '1'){
				flag0_5 = 0;
				if(flag1_5 == 4){
					binary[position++] = '0';
					flag1_5 = 0;
				}
				else
					flag1_5++;
			}
			else{
				flag1_5 = 0;
				if(flag0_5 == 4){
					binary[position++] = '1';
					flag0_5 = 0;
				}
				else
					flag0_5++;
			}
		}
	}
	binary[position] = '\0';
}

void appendRedundantBits(char *binary){
	int SIZE, appendSize, i;
	SIZE = strlen(binary);
	binary = (char *)realloc(binary, (SIZE + 16) * sizeof(char));
	appendSize = 8 - (SIZE % 8);
	if(appendSize != 8)
		for(i = 0; i < appendSize; i++)
			binary[SIZE++] = '0';
	binary[SIZE] = '\0';
	switch(appendSize){
		case 0:
			binary[0] = '0';
			binary[1] = '0';
			binary[2] = '0';
			break;
		case 1:
			binary[0] = '0';
			binary[1] = '0';
			binary[2] = '1';
			break;
		case 2:
			binary[0] = '0';
			binary[1] = '1';
			binary[2] = '0';
			break;
		case 3:
			binary[0] = '0';
			binary[1] = '1';
			binary[2] = '1';
			break;
		case 4:
			binary[0] = '1';
			binary[1] = '0';
			binary[2] = '0';
			break;
		case 5:
			binary[0] = '1';
			binary[1] = '0';
			binary[2] = '1';
			break;		
		case 6:
			binary[0] = '1';
			binary[1] = '1';
			binary[2] = '0';
			break;		
		case 7:
			binary[0] = '1';
			binary[1] = '1';
			binary[2] = '1';
			break;
	}
}

void binToAscii(char *binary, char *output){
	int SIZE = 1024, i, j, position = 0, counter = 0, sum, index;
	for(i = 0; i < strlen(binary) / 8; i++){
		sum = 0;
		for(j = 0; j < 8; j++){
			index = 7 - j;
			sum += (((int)binary[position++] - 48) * pow(2, index));
		}
		// printf("Saket:-%d--->%d---->%d\n", position, sum, counter);
		// printf("%d\n", sum);
		output[counter++] = (char)sum;
		if(counter >= (SIZE - 1)){
			SIZE *= 2;
			output = (char *)realloc(output, SIZE * sizeof(char));
		}
	}
	output[counter] = '\0';
}

//-----------------------------------------------------------------------------------------------------------------------------

void reStorePath(char *huffList,path *paths, int uCount){
	int i, j = 0, k, uTmp, SIZE = 1024;
	char *uTmpBuffer;
	for(i = 0; i < uCount; i++){
		uTmp = (int)huffList[j];
		if(uTmp < 0)
			uTmp += 256;
		if(uTmp == 253)
			j++;
		paths[i].c = huffList[j++];
		uTmpBuffer = (char *)malloc(SIZE * sizeof(char));
		k = 0;
		while(huffList[j] == '0' || huffList[j] == '1')
			uTmpBuffer[k++] = huffList[j++];
		uTmpBuffer[k] = '\0';
		for(k = 0; k < strlen(uTmpBuffer); k++)
			paths[i].path[k] = uTmpBuffer[k];
		paths[i].path[k] = '\0';
		free(uTmpBuffer);
	}
}

char* asciiToBin(char *binary, char *output){
// void asciiToBin(char *output, char *binary){
	int SIZE = 1024, i = 0, j, uTmp, uTmp_1, bTrack, position = 0;
	char *uTmpBuffer;
	while(i < strlen(output)){
		uTmp = (int)output[i];
		if(uTmp < 0)
			uTmp += 256;
		// printf("%d--->%d\n", i, uTmp);
		uTmpBuffer = (char *)malloc(16 * sizeof(char));
		bTrack = 7;
		while(uTmp != 0){
			uTmp_1 = (char)((uTmp % 2) + 48);
			uTmpBuffer[bTrack] = uTmp_1;
			bTrack--;
			uTmp /= 2;
		}			
		while(bTrack >= 0){
			uTmpBuffer[bTrack] = '0';
			bTrack--;
		}
		for(j = 0; j < 8; j++){
			// printf("%c", uTmpBuffer[j]);
			binary[position++] = uTmpBuffer[j];
			// printf("Sak-%c\n", binary[position - 1]);
			if(position >= (SIZE - 1)){
				SIZE *= 2;
				binary = (char *)realloc(binary, SIZE * sizeof(char));
			}
		}
		free(uTmpBuffer);
		i++;
	}
	binary[position] = '\0';
	// printf("%s\n", binary);
	return binary;
}

char* removeRedundantBits(char *binary, char *output){
	int SIZE = 1024, strLen, tmp, pos = 3, flag0_5 = 0, flag1_5 = 0;
	char t0, t1, t2;
	t0 = binary[0];
	t1 = binary[1];
	t2 = binary[2];

	if(t0 == '0' && t1 == '0' && t2 == '0')
		tmp = 0;
	else if(t0 == '0' && t1 == '0' && t2 == '1')
		tmp = 1;
	else if(t0 == '0' && t1 == '1' && t2 == '0')
		tmp = 2;
	else if(t0 == '0' && t1 == '1' && t2 == '1')
		tmp = 3;
	else if(t0 == '1' && t1 == '0' && t2 == '0')
		tmp = 4;
	else if(t0 == '1' && t1 == '0' && t2 == '1')
		tmp = 5;
	else if(t0 == '1' && t1 == '1' && t2 == '0')
		tmp = 6;
	else if(t0 == '1' && t1 == '1' && t2 == '1')
		tmp = 7;

	strLen = strlen(binary) - tmp;

	tmp = 0;
	while(pos < strLen){
		if(binary[pos] == '0'){
			flag1_5 = 0;
			flag0_5++;
		}
		else{
			flag0_5 = 0;
			flag1_5++;
		}
		output[tmp++] = binary[pos++];
		if(tmp >= (SIZE - 1)){
			SIZE *= 2;
			output = (char *)realloc(output, SIZE * sizeof(char));
		}
		if(flag0_5 == 5){
			pos++;
			flag0_5 = 0;
		}
		else if(flag1_5 == 5){
			pos++;
			flag1_5 = 0;
		}
	}
	output[tmp] = '\0';
	return output;
}

char* finalConversion(char *output, char *buffer, path *paths, int uCount){
	int SIZE = 1024, i, j, k, strLen, pos = 0, counter = 0, status, flag = 0;
	char *uTmpBuffer, *auxBuffer;

	auxBuffer = (char *)malloc(SIZE * sizeof(char));
	k = 0;
	while(output[pos] != '\0'){
		if(flag == 1){
			auxBuffer = (char *)malloc(SIZE * sizeof(char));
			k = 0;
			flag = 0;
		}
		auxBuffer[k++] = output[pos++];
		for(i = 0; i < uCount; i++){
			strLen = strlen(paths[i].path);
			uTmpBuffer = (char *)malloc(SIZE * sizeof(char));
			for(j = 0; j < strLen; j++)
				uTmpBuffer[j] = paths[i].path[j];
			uTmpBuffer[j] = '\0';
			// printf("%s\n", uTmpBuffer);
			status = strcmp(auxBuffer, uTmpBuffer);
			if(status == 0){
				buffer[counter++] = paths[i].c;
				if(counter >= (SIZE - 1)){
					SIZE *= 2;
					buffer = (char *)realloc(buffer, SIZE * sizeof(char));
				}
				flag = 1;
				// free(auxBuffer);//*********
				break;
			}
			free(uTmpBuffer);
		}
	}
	buffer[counter] = '\0';
	return buffer;
}

