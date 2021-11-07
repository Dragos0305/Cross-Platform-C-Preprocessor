#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H 1
#include "hashmap.h"
#include "algorithms.h"

int getFlagType(const char* contet);

void parse_D_FLAG(char const* args[], int* index, hashMap* HM);
char* parse_I_FLAG(char const* args[], int* index);
char* parse_O_FLAG(char const* args[], int* index);
char* infile(char const* filename);

#endif