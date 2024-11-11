#ifndef __SQD__
#define __SQD__

#include <stdio.h>
#include <stdlib.h>

typedef struct sqd{
	int data;
	struct sqd *link1;
	struct sqd *link2;
}SQD;

#endif
