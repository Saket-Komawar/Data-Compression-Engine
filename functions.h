#define PATH 1024


typedef struct node{
	char letter;
	int frequency;
	int flag;//Distinguishes node and huffmanNode.
	struct node *next;//For linkList.
	struct node *left, *right;//For Huffman Tree.
	char path[PATH];//Path From Root to respective Node.
}node;

typedef struct list{
	node *head;
	int cnt;
}list;

typedef struct path{
	char c;
	char path[PATH];
}path;


void init(list *l);
void traverse(list *l);
void append(list *l, char letter);
void searchAndAdd(list *l, char letter);
void bubbleSort(list *l);
list* huffmanTree(list *l);
void preOrder(node *t);
void appendPath(char *array, char c);
void assignPath(list *l);
void storePath(node *t, path *paths);
void storeHuffList(char *huffList, path *paths, int cnt);
void binaryConversion(char *buffer, char *binary, path *paths);
void appendRedundantBits(char *binary);
void binToAscii(char *binary, char *output);
//----------------------------------------------------------------------------
void reStorePath(char *huffList,path *paths, int uCount);
char* asciiToBin(char *binary, char *output);
// void asciiToBin(char *output, char *binary);
char* removeRedundantBits(char *binary, char *output);
char* finalConversion(char *output,char *buffer, path *paths, int uCount);