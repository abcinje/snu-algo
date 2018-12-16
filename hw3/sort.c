extern int* tmp;
extern int** tmp_P;

void merge(int* A, int p, int q, int r)
{
	int i = p;
	int j = q + 1;
	int t = 1;

	while (i <= q && j <= r)
	{
		if (A[i] <= A[j]) tmp[t++] = A[i++];
		else tmp[t++] = A[j++];
	}

	while (i <= q) tmp[t++] = A[i++];
	while (j <= r) tmp[t++] = A[j++];
	i = p;
	t = 1;
	while (i <= r) A[i++] = tmp[t++];
}

void mergeSort(int* A, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}
}

void merge_P(int** A, int p, int q, int r)
{
	int i = p;
	int j = q + 1;
	int t = 1;

	while (i <= q && j <= r)
	{
		if (A[i][0] <= A[j][0]) tmp_P[t++] = A[i++];
		else tmp_P[t++] = A[j++];
	}

	while (i <= q) tmp_P[t++] = A[i++];
	while (j <= r) tmp_P[t++] = A[j++];
	i = p;
	t = 1;
	while (i <= r) A[i++] = tmp_P[t++];
}

void mergeSort_P(int** A, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		mergeSort_P(A, p, q);
		mergeSort_P(A, q + 1, r);
		merge_P(A, p, q, r);
	}
}

void sort(int** A)
{
	int i = 0;
	while (A[i][0] != -1)
	{
		int r = 0;
		while (A[i][r] != -1)
			r++;
		if (r > 0) mergeSort(A[i], 0, r - 1);
		i++;
	}

	if (i > 0) mergeSort_P(A, 0, i - 1);
}

