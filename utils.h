#ifndef UTILS_H
#define UTILS_H 1

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);					\
		}							\
	} while (0)


        

#define NORMAL_LINE 0
#define ONE_LINE_DEFINE 1
#define MULTI_LINE_DEFINE 2
#define IFDEF_STATEMENT 3
#define UNDEF_STATEMENT 4
#define IFDEF_BLOCK 5
#define IFNDEF_BLOCK 6
#define IF_BLOCK 7
#define INCLUDE_DIRECTIVE 8


#define D_FLAG 10
#define O_FLAG 11
#define I_FLAG 12
#define INFILE 13

#endif