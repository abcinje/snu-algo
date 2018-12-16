#include <stdio.h>
#include <stdlib.h>

int n;
char** mat;
char** matT;
char* visited;

int* complete;
int last;

int** result;
int resIdx;
int numSCC;

int* tmp;
int** tmp_P;

int lines;

void adjMat(void);
void adjList(void);
void adjArr(void);

int main(int argc, char* argv[])
{
	/*
	if (argc != 2)
	{
		printf("wrong number of arguments (%d for 2)\n", argc);
		return -1;
	}
	*/

	FILE* fp = stdin; //fopen(argv[1], "rt");
	if (fp == NULL)
	{
		puts("Failed to open input file");
		return -1;
	}

	// make matrices and array
	fscanf(fp, "%d", &n);
	while (fgetc(fp) != '\n');

	mat = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++)
		mat[i] = (char*)calloc(n, sizeof(char));

	for (int i = 0; i<n; i++)
	{
		int idx;
		fscanf(fp, "%d", &idx);
		int temp;
		for (int j = 0; j<idx; j++)
		{
			fscanf(fp, "%d", &temp);
			mat[i][temp - 1] = 1;
			lines++;
		}

		char c;
		do c = fgetc(fp);
		while ((c != '\n') && (c != EOF));
		if (c == EOF) break;
	}

	matT = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++)
		matT[i] = (char*)malloc(n * sizeof(char));
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matT[i][j] = mat[j][i];

	visited = (char*)malloc(n * sizeof(char));
	complete = (int*)malloc(n * sizeof(int));
	result = (int**)malloc((n+1) * sizeof(int*));
	for (int i = 0; i < n+1; i++)
		result[i] = (int*)malloc((n+1) * sizeof(int));

	tmp = (int*)malloc(n * sizeof(int));
	tmp_P = (int**)malloc(n * sizeof(int*));

	// adjacency matrix
	adjMat();

	// adjacency list
	adjList();

	// adjacency array
	adjArr();

	return 0;
}
