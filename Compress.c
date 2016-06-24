#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


int main(int argc, char *argv[]){
	if(argc == 1){
		printf("Very Few Arguments\n");
		printf("File Name Missing\n");
		exit(1);
	}

	list *l = (list *)malloc(sizeof(list));
	init(l);
	path *paths;
	FILE *fp;
	int i, j, flag = 0, SIZE = 1024, USIZE = 1024, uCount, uFlag = 0, uFlag_1 = 0, uTmp;
	char zipFileName[32] = "", *buffer, *binary, *output, *huffList, character, dflag, cnt, *saket;
	for(i = 0; argv[1][i] != '\0'; i++){
		zipFileName[i] = argv[1][i];
	}
	zipFileName[i++] = '.';
	zipFileName[i++] = 's';
	zipFileName[i++] = 'a';
	zipFileName[i++] = 'k';

	fp = fopen(argv[1], "r");
	if(!fp){
		printf("File Doesn't Exist\n");
		exit(2);
	}

	buffer = (char *)malloc(SIZE * sizeof(char));
	i = 0;
	while((character = getc(fp)) != EOF){
		buffer[i] = character;
		if(i >= (SIZE - 1)){
			SIZE *= 2;
			buffer = (char *)realloc(buffer, SIZE);
		}
		if(flag == 0){
			append(l, character);
			flag = 1;
		}
		else
			searchAndAdd(l, character);
		i++;
	}
	buffer[i] = '\0';
	fclose(fp);

	bubbleSort(l); //Initial Sorting According to Weight.

	l = huffmanTree(l);

	assignPath(l);

	paths = (path *)malloc(l->cnt * sizeof(path));
	storePath(l->head, paths);

	huffList = (char *)malloc(SIZE * sizeof(char));
	storeHuffList(huffList, paths, l->cnt);

	binary = (char *)malloc(SIZE * sizeof(char));
	binaryConversion(buffer, binary, paths);
	printf("%s\n", binary);
	i = strlen(binary);
	printf("%d\n", i);
	free(buffer);
	free(paths);

	appendRedundantBits(binary);
	printf("%s\n", binary);

	output = (char *)malloc(SIZE * sizeof(char));
	binToAscii(binary, output);
	printf("%s\n", output);

	free(binary);

	dflag = (char)252; //11111100
	cnt = (char)l->cnt;//nodeCount
	fp = fopen(zipFileName, "w+");
	fprintf(fp, "%c", cnt);
	fprintf(fp, "%s", huffList);
	fprintf(fp, "%c", dflag);
	fprintf(fp, "%s", output);
	free(huffList);
	free(output);
	fclose(fp);

	printf("\nCompressed\n\t-------------------------------------------------------------------------------------------------------------\n");

	return 0;
}