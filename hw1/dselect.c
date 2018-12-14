void swap(int A[], int i1, int i2);

void under5(int A[], int p, int r)
{
	for (int j = p + 1; j <= r; j++)
	{
		int key = A[j];
		int i = j - 1;
		while (i > p - 1 && A[i] > key)
		{
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}

int dpartition(int A[], int p, int r, int mpos)
{
	swap(A, mpos, r);
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
		if (A[j] <= x)
			swap(A, ++i, j);
	swap(A, i + 1, r);
	return i + 1;
}

int dselect(int A[], int p, int r, int i)
{
	if (r - p + 1 <= 5)
	{
		under5(A, p, r);
		return A[p + i-1];
	}

	int idx;
	for (idx = 0; idx < ((r - p + 1) / 5); idx++)
	{
		under5(A, p + (5 * idx), p + (5 * idx) + 4);
		swap(A, p + idx, p + (5 * idx) + 2);
	}

	if ((r - p + 1) % 5)
	{
		under5(A, p + (5 * idx), r);
		swap(A, p + idx, r - (((r - p + 1) % 5) / 2));
		idx++;
	}

	int m = dselect(A, p, p + idx - 2, ((idx - 1)/2)+1);
	int temp = p;
	for (int j = p; j <= p + idx - 2; j++)
		if (A[j] == m)
			temp = j;

	int q = dpartition(A, p, r, temp);
	int k = q - p + 1;
	if (i < k) return dselect(A, p, q - 1, i);
	else if (i == k) return A[q];
	else return dselect(A, q + 1, r, i - k);
}