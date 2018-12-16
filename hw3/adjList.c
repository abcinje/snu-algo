#include "header.h"

typedef struct node
{
	struct node* next;
	int elem;
} Node;

int isConnectedL(Node** head, int i, int j)
{
	Node* temp = head[i];
	while (temp != NULL)
	{
		if (temp->elem == j) return 1;
		temp = temp->next;
	}
	return 0;
}

void aDFSL(Node** head, int i)
{
	visited[i] = YES;
	for (int j = 0; j < n; j++)
		if (isConnectedL(head, i, j) && (visited[j] == NO))
			aDFSL(head, j);
	complete[last++] = i;
}

void DFSL(Node** head)
{
	for (int i = 0; i < n; i++)
		visited[i] = NO;
	for (int i = 0; i < n; i++)
		if (visited[i] == NO) aDFSL(head, i);
}

void aDFSL_T(Node** headT, int i)
{
	visited[i] = YES;
	result[numSCC][resIdx++] = i;
	for (int j = 0; j < n; j++)
		if (isConnectedL(headT, i, j) && (visited[j] == NO))
			aDFSL_T(headT, j);
}

void DFSL_T(Node** headT)
{
	for (int i = 0; i < n; i++)
		visited[i] = NO;
	for (int i = n - 1; i >= 0; i--)
	{
		char flag = 0;

		resIdx = 0;
		if (visited[complete[i]] == NO)
		{
			aDFSL_T(headT, complete[i]);
			flag = 1;
		}
		result[numSCC][resIdx] = -1;

		if (flag) numSCC++;
	}
	result[numSCC][0] = -1;
}

void adjList(void)
{
	Node** head = (Node**)calloc(n, sizeof(Node*));
	for (int i = 0; i < n; i++)
	{
		char isFirst = 1;
		Node* temp = NULL;
		for(int j=0; j<n; j++)
			if (mat[i][j] == 1)
			{
				Node* append = (Node*)malloc(sizeof(Node));
				append->elem = j;
				append->next = NULL;
				
				if (isFirst)
				{
					head[i] = append;
					temp = append;
					isFirst = 0;
				}
				else
				{
					temp->next = append;
					temp = temp->next;
				}
			}
	}

	Node** headT = (Node**)calloc(n, sizeof(Node*));
	for (int i = 0; i < n; i++)
	{
		char isFirst = 1;
		Node* temp = NULL;
		for (int j = 0; j<n; j++)
			if (matT[i][j] == 1)
			{
				Node* append = (Node*)malloc(sizeof(Node));
				append->elem = j;
				append->next = NULL;

				if (isFirst)
				{
					headT[i] = append;
					temp = append;
					isFirst = 0;
				}
				else
				{
					temp->next = append;
					temp = temp->next;
				}
			}
	}

	last = 0;
	resIdx, numSCC = 0;

	// algorithm
	clock_t start, end;
	start = clock();
	DFSL(head);
	DFSL_T(headT);
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

	puts("*** Adjacency List Result ***");
	printf("Program running time : %ldms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
	puts("");

	return;
}