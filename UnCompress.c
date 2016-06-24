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
	path *paths;
	FILE *fp;
	int i, j, flag = 0, SIZE = 1024, USIZE = 1024, uCount, uFlag = 0, uFlag_1 = 0, uTmp;
	char zipFileName[32] = "", *buffer, *binary, *output, *huffList, character, dflag, cnt, *saket;

	fp = fopen(argv[1], "r");
	huffList = (char *)malloc(SIZE * sizeof(char));
	output = (char *)malloc(SIZE * sizeof(char));
	i = 0;
	j = 0;
	while((character = fgetc(fp)) != EOF){
		uTmp = (int)character;
		if(uTmp < 0)
			uTmp += 256;		
		if(uFlag == 0){
			uCount = uTmp;
			uFlag = 1;
		}
		else{
			if(uTmp != 252 && uFlag_1 == 0){
				huffList[i++] = character;
				if(i >= (SIZE - 1)){
					SIZE *= 2;
					huffList = (char *)realloc(huffList, SIZE * sizeof(char));
				}
			}
			else{
				uFlag_1 = 1;
				if(uTmp != 252){
					output[j++] = character;
					if(j >= (USIZE - 1)){
						USIZE *= 2;
						output = (char *)realloc(output, USIZE * sizeof(char));
					}
				}
			}
		}
	}
	huffList[i] = output[j] = '\0';
	fclose(fp);

	paths = (path *)malloc(uCount * sizeof(path));
	reStorePath(huffList, paths, uCount);

	binary = (char *)malloc(SIZE * sizeof(char));
	binary = asciiToBin(binary, output);
	free(output);

	output = (char *)malloc(SIZE * sizeof(char));
	output = removeRedundantBits(binary, output);

	buffer = (char *)malloc(SIZE * sizeof(char));
	buffer = finalConversion(output, buffer, paths, uCount);

	i = 0;
	while(argv[1][i] != '.'){
		zipFileName[i] = argv[1][i];
		i++;
	}

	fp = fopen(zipFileName, "w+");
	fprintf(fp, "%s", buffer);
	fclose(fp);

	printf("\nUnCompressed\n\t-----------------------------------------------------------------------------------------------------------\n");
	return 0;
}