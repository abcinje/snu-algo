#include <stdio.h>
#include <stdlib.h>

int res;
long line;

void error(char opcode, int operand, int ans)
{
	printf("line %ld (%c %d) : Output should be %d, not %d.\n", line, opcode, operand, ans, res);
	exit(1);
}

int main(int argc, char* argv[])
{
	// initialize
	if (argc != 3)
	{
		printf("wrong number of arguments (%d for 3)\n", argc);
		return -1;
	}

	FILE* ifp = fopen(argv[1], "rt");
	if (ifp == NULL)
	{
		puts("Failed to open input sequences file");
		return -1;
	}

	FILE* ofp = fopen(argv[2], "rt");
	if (ofp == NULL)
	{
		puts("Failed to open output sequences file");
		return -1;
	}

	int size = 0;
	char opcode;
	int c;
	int operand;

	char* arr = (char*)calloc(1000, sizeof(char));

	while (1)
	{
		line++;
		fscanf(ifp, "%c %d", &opcode, &operand);
		fscanf(ofp, "%d", &res);	
		if (opcode == 'I')
		{
			if (!arr[operand])
			{
				if (res != operand) error(opcode, operand, operand);
				arr[operand] = 1;
				size++;
			}
			else if (res != 0) error(opcode, operand, 0);
		}

		else if (opcode == 'D')
		{
			if (arr[operand])
			{
				if (res != operand) error(opcode, operand, operand);
				arr[operand] = 0;
				size--;
			}
			else if (res != 0) error(opcode, operand, 0);
		}

		else if (opcode == 'S')
		{
			if (operand > size)
			{
				if (res != 0) error(opcode, operand, 0);
			}
			else
			{
				int i;
				int sum = 0;
				for (i = 0; sum < operand; i++)
					sum += arr[i];
				i--;
				if (res != i) error(opcode, operand, i);
			}
		}

		else if (opcode == 'R')
		{
			if (arr[operand])
			{
				int sum = 0;
				for (int i = 1; i <= operand; i++)
					sum += arr[i];
				if (res != sum) error(opcode, operand, sum);
			}
			else if (res != 0) error(opcode, operand, 0);
		}

		do c = fgetc(ifp);
		while ((c == '\n') || (c == ' '));

		if (c == EOF) break;
		fseek(ifp, -1, SEEK_CUR);
	}

	fclose(ifp);
	fclose(ofp);
	free(arr);
	puts("Passed correctness verification.");
	return 0;
}
