#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXLEN 100000000

int rselect(int A[], int p, int r, int i);
int dselect(int A[], int p, int r, int i);

int main(int argc, char* argv[])
{
	// initialize
	if (argc != 3)
	{
		printf("wrong number of arguments (%d for 3)\n", argc);
		return -1;
	}
	int i = atoi(argv[1]);
	FILE* fp = fopen(argv[2], "rt");
	if (fp == NULL)
	{
		puts("failed to open file");
		return -1;
	}

	// copy input to memory
	int* A = (int *)malloc(sizeof(int)*MAXLEN);
	char buf[20];
	int r = 0, bufIdx = 0;
	while (1)
	{
		int c = fgetc(fp);
		if (c == 45 || (c >= 48 && c <= 57))
			buf[bufIdx++] = c;
		else if (bufIdx != 0)
		{
			buf[bufIdx] = 0;
			bufIdx = 0;
			A[r++] = atoi(buf);
		}

		if (c == EOF) break;
	}

	if (i < 1 || i > r)
	{
		puts("2nd argument exceeded array length");
		return -1;
	}

	clock_t start, end;
	int result;
	
	// Randomized-select
	start = clock();
	result = rselect(A, 0, r-1, i);
	end = clock();
	puts("*** Randomized select result ***");
	printf("[%d]th smallest element : %d\n", i, result);
	printf("Program running time : %ldms\n", (end - start)*1000/CLOCKS_PER_SEC);

	puts("");
	
	r = 0, bufIdx = 0;
	fseek(fp, 0, SEEK_SET);
	while (1)
	{
		int c = fgetc(fp);
		if (c == 45 || (c >= 48 && c <= 57))
			buf[bufIdx++] = c;
		else if (bufIdx != 0)
		{
			buf[bufIdx] = 0;
			bufIdx = 0;
			A[r++] = atoi(buf);
		}

		if (c == EOF) break;
	}
	fclose(fp);

	// Deterministic-select
	start = clock();
	result = dselect(A, 0, r-1, i);
	end = clock();
	puts("*** Deterministic select result ***");
	printf("[%d]th smallest element : %d\n", i, result);
	printf("Program running time : %ldms\n", (end - start)*1000/CLOCKS_PER_SEC);

	// terminate
	free(A);
	return 0;
}
