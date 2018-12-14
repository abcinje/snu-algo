#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int A[], int i1, int i2);

int rpartition(int A[], int p, int r)
{
	srand((unsigned)time(NULL));
	swap(A, p+(rand()%(r-p+1)), r);
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
		if (A[j] <= x)
			swap(A, ++i, j);
	swap(A, i + 1, r);
	return i + 1;
}

int rselect(int A[], int p, int r, int i)
{
	if (p == r) return A[p];
	int q = rpartition(A, p, r);
	int k = q - p + 1;
	if (i < k) return rselect(A, p, q - 1, i);
	else if (i == k) return A[q];
	else return rselect(A, q + 1, r, i - k);
}
