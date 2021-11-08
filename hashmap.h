#ifndef HASHMAP_H
#define HASHMAP_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#define M 10



typedef struct hashMap {
	int numElements;
	listNode* buckets[M];
}hashMap;

// HashMAp functions list
int hash(const char* str);
char* getValue(hashMap HM, const char* key);
void removeKey(hashMap* HM, const char* key);
int getSize(hashMap HM);
int isEmpty(hashMap HM);
void initHashMap(hashMap* HM);
char** getKeys(hashMap HM, int* number_of_keys);
void printHashMAp(hashMap HM);
void insertKeyValue(hashMap* HM, char* key, char* value);
void free_map(hashMap*HM);



#endif