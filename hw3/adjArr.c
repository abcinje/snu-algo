#include "header.h"

typedef struct
{
	int elem;
	int* end;
} HeadElem;

extern int lines;

int isConnectedA(HeadElem* head, int* arr, int i, int j)
{
	int p, r;
	if (i == 0)
	{
		p = 0;
		r = head[0].elem;
	}
	else
	{
		p = head[i - 1].elem;
		r = head[i].elem;
	}

	for (int idx = p; idx < r; idx++)
		if (arr[idx] == j)
			return 1;

	return 0;
}

void aDFSA(HeadElem* head, int* arr, int i)
{
	visited[i] = YES;
	for (int j = 0; j < n; j++)
		if (isConnectedA(head, arr, i, j) && (visited[j] == NO))
			aDFSA(head, arr, j);
	complete[last++] = i;
}

void DFSA(HeadElem* head, int* arr)
{
	for (int i = 0; i < n; i++)
		visited[i] = NO;
	for (int i = 0; i < n; i++)
		if (visited[i] == NO) aDFSA(head, arr, i);
}

void aDFSA_T(HeadElem* headT, int* arrT, int i)
{
	visited[i] = YES;
	result[numSCC][resIdx++] = i;
	for (int j = 0; j < n; j++)
		if (isConnectedA(headT, arrT, i, j) && (visited[j] == NO))
			aDFSA_T(headT, arrT, j);
}

void DFSA_T(HeadElem* headT, int* arrT)
{

	for (int i = 0; i < n; i++)
		visited[i] = NO;
	for (int i = n - 1; i >= 0; i--)
	{
		char flag = 0;

		resIdx = 0;
		if (visited[complete[i]] == NO)
		{
			aDFSA_T(headT, arrT, complete[i]);
			flag = 1;
		}
		result[numSCC][resIdx] = -1;

		if (flag) numSCC++;
	}
	result[numSCC][0] = -1;
}

void adjArr(void)
{
	HeadElem* head = (HeadElem*)calloc(n, sizeof(HeadElem));
	int* arr = (int*)malloc(lines * sizeof(int));

	int idx = 0;
	for (int i = 0; i < n; i++)
	{
		head[i].end = &arr[idx];
		for (int j = 0; j < n; j++)
			if (mat[i][j] == 1)
				arr[idx++] = j;
		head[i].elem = idx;
	}

	HeadElem* headT = (HeadElem*)calloc(n, sizeof(HeadElem));
	int* arrT = (int*)malloc(lines * sizeof(int));

	idx = 0;
	for (int i = 0; i < n; i++)
	{
		headT[i].end = &arrT[idx];
		for (int j = 0; j < n; j++)
			if (matT[i][j] == 1)
				arrT[idx++] = j;
		headT[i].elem = idx;
	}

	last = 0;
	resIdx, numSCC = 0;



	// algorithm
	clock_t start, end;
	start = clock();
	DFSA(head, arr);
	DFSA_T(headT, arrT);
	end = clock();

	// sort
	sort(result);

	// print
	if (PRINT)
	{
		int i = 0;
		while (result[i][0] != -1)
		{
			int j = 0;
			while (result[i][j] != -1)
			{
				printf("%d ", result[i][j] + 1);
				j++;
			}
			puts("");
			i++;
		}
	}

	puts("*** Adjacency Array Result ***");
	printf("Program running time : %ldms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
	puts("");

	return;
}