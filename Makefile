compress : functions.o dataStructure.o stack.o
	cc Compress.c functions.o dataStructure.o stack.o -lm -o compress
uncompress : functions.o dataStructure.o stack.o
	cc UnCompress.c functions.o dataStructure.o stack.o -lm -o uncompress
functions.o : 
	cc -c functions.c
dataStructure.o :
	cc -c dataStructure.c
stack.o :
	cc -c stack.c
clean :
	rm *.o
	rm compress
	rm uncompress
