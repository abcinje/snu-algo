#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char* argv[])
{
	// initialize
	if (argc != 2)
	{
		printf("wrong number of arguments (%d for 2)\n", argc);
		return -1;
	}

	// create input stream
	FILE* fp = fopen(argv[1], "rt");
	if (fp == NULL)
	{
		puts("Failed to open input sequences file");
		return -1;
	}

	// create output stream
	FILE* out = fopen("output", "wt");
	if (out == NULL)
	{
		puts("Failed to open output sequences file");
		return -1;
	}

	// allocate memory
	Tree* T = (Tree*)malloc(sizeof(Tree));
	T->root = (Node*)malloc(sizeof(Node));
	T->nil = (Node*)malloc(sizeof(Node));

	// nil
	T->nil->key = 0;
	T->nil->size = 0;
	T->nil->color = BLACK;

	// root
	T->root = T->nil;
	T->root->p = T->nil;

	char opcode;
	int operand;
	int c, ret;
	while (1)
	{
		// read input
		opcode = fgetc(fp);
		fscanf(fp, "%d", &operand);

		// print input
		printf("%c %d\n", opcode, operand);

		// operate
		if (opcode == 'I')
		{
			ret = OS_Insert(T, operand);
			fprintf(out, "%d\n", ret);
		}
		else if (opcode == 'D')
		{
			ret = OS_Delete(T, operand);
			fprintf(out, "%d\n", ret);
		}
		else if (opcode == 'S')
		{
			ret = OS_Select(T, operand);
			fprintf(out, "%d\n", ret);
		}	
		else if (opcode == 'R')
		{
			ret = OS_Rank(T, operand);
			fprintf(out, "%d\n", ret);
		}

		do c = fgetc(fp);
		while ((c == '\n') || (c == ' '));

		if (c == EOF) break;
		fseek(fp, -1, SEEK_CUR);
	}

	// terminate
	fclose(fp);
	fclose(out);

	// deallocate
	free(T->nil);
	free(T);
	
	return 0;
}
