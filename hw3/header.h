#ifndef _HEADER_
#define	_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NO 1
#define YES 0

#define PRINT 1

extern int n;
extern char** mat;
extern char** matT;
extern char* visited;

extern int* complete;
extern int last;

extern int** result;
extern int resIdx;
extern int numSCC;

void sort(int** A);

#endif
