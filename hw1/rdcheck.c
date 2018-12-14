#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	// initialize
	if (argc != 4)
	{
		printf("wrong number of arguments (%d for 4)\n", argc);
		return -1;
	}
	int i = atoi(argv[1]);
	int res = atoi(argv[3]);
	FILE* fp = fopen(argv[2], "rt");
	if (fp == NULL)
	{
		puts("failed to open file");
		return -1;
	}

	char buf[20];
	int bufIdx = 0, count = 1;
	int dup = 0;
	while (1)
	{
		int c = fgetc(fp);
		if (c == 45 || (c >= 48 && c <= 57))
			buf[bufIdx++] = c;
		else if (bufIdx != 0)
		{
			buf[bufIdx] = 0;
			bufIdx = 0;
			if(atoi(buf) < res) count++;
			else if (atoi(buf) == res) dup++;
		}

		if (c == EOF) break;
	}
	fclose(fp);

	puts("*** Check correctness of rdselect ***");

	if (!dup)
	{
		printf("no elements with value %d -> WRONG\n", res);
		return 0;
	}

	if(dup > 1) printf("%d is the [%d-%d]th smallest element -> ", res, count, count + dup - 1);
	else printf("%d is the [%d]th smallest element -> ", res, count);

	if (i >= count && i < count + dup) puts("CORRECT");
	else puts("WRONG");

	return 0;
}
