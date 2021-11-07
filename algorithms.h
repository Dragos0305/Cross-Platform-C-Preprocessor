#ifndef ALGORITHMS_H
#define ALGORITHMS_H 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int binarySearch(int* values, int needle, int start, int end);
char** split_string(char* str, int* lenght, const char* delim);
char* getFIleContent(const char* filename);
long getFileSize(FILE* fp);
FILE* openFile(const char* filename);

#endif