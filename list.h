#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct listNode {
	char* key;
	char* value;
	struct listNode* next;
}listNode;


// Linked functions list
void insertNodeHeadOfList(listNode** listStart, char* key, char* value);
int get_num_of_elements(listNode** listStart);
void removeNodeHeadOfList(listNode** listStart);
listNode* getNode(listNode* listNode, int poz);
void removeNodeFromList(listNode** listStart, int poz);


#endif