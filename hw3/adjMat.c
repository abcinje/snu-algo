#include "header.h"

void aDFS(char** matrix, int i)
{
	visited[i] = YES;
	for (int j = 0; j < n; j++)
		if ((matrix[i][j] == 1) && (visited[j] == NO))
			aDFS(matrix, j);
	complete[last++] = i;
}

void DFS(char** matrix)
{
	for (int i = 0; i < n; i++)
		visited[i] = NO;
	for (int i = 0; i < n; i++)
		if (visited[i] == NO) aDFS(matrix, i);
}

void aDFS_T(char** matrixT, int i)
{
	visited[i] = YES;
	result[numSCC][resIdx++] = i;
	for (int j = 0; j < n; j++)
		if ((matrixT[i][j] == 1) && (visited[j] == NO))
			aDFS_T(matrixT, j);
}

void DFS_T(char** matrixT)
{
	for (int i = 0; i < n; i++)
		visited[i] = NO;
	for (int i = n-1; i >=0; i--)
	{
		char flag = 0;

		resIdx = 0;
		if (visited[complete[i]] == NO)
		{
			aDFS_T(matrixT, complete[i]);
			flag = 1;
		}
		result[numSCC][resIdx] = -1;

		if(flag) numSCC++;
	}
	result[numSCC][0] = -1;
}

void adjMat(void)
{
	last = 0;
	resIdx, numSCC = 0;

	// algorithm
	clock_t start, end;
	start = clock();
	DFS(mat);
	DFS_T(matT);
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
	
	
	/*
	for (int i = 0; i < n+1; i++)
	{
		for (int j = 0; j < n+1; j++)
			printf("%d ", result[i][j]+1);
		puts("");
	}
	*/

	puts("*** Adjacency Matrix Result ***");
	printf("Program running time : %ldms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
	puts("");

	/*
	for (int i = 0; i < n; i++)
		printf("%d ", complete[i]+1);
	puts("");
	*/
}
