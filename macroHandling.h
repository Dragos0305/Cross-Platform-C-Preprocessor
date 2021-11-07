#ifndef MACROHANDLING_H 
#define MACROHANDLING_H 1

#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "algorithms.h"
#include "Outputfile.h"


int getMacroType(char* content);
void add_one_line_define(char* content, hashMap* HM);
void add_multi_line_define(char** content, hashMap* HM, int* start_index);
void undef(char* content, hashMap* HM);
int findKey(char** keys, int lenght_of_keys, char* content, int* number_of_chars);
void Parse_IFDEF(char** lines,int*final_index,OutputFile* FILE,hashMap* HM);
void Parse_IFNDEF(char** lines, int* start_index, OutputFile* FILE, hashMap* HM);
void Parse_IF(char** lines, int* start_index, OutputFile* FILE, hashMap* HM);
void Parse_Include_Directives(OutputFile* FILE,hashMap*HM,char* include_directive);
int check_else(char** lines, int start_index);
int get_endif_position(char** lines, int start_index);
void decide_block(char** lines, OutputFile* FILE, int* start_index, hashMap* HM);
#endif