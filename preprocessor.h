#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H 1

#include "hashmap.h"
#include  "algorithms.h"
#include "OutputFile.h"

void collectMacros(hashMap* HM, const char*,OutputFile*);
void replaceMacros(const char*, hashMap,OutputFile*);


#endif