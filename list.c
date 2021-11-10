#include "list.h"
#include <string.h>

void removeNodeFromList(listNode** listStart, int poz) {
	if (poz == 0) {
		removeNodeHeadOfList(listStart);
		return;
	}
	listNode* aux = getNode(*listStart, poz - 1);
	if (aux->next != NULL) {
		listNode* aux1 = aux->next;
		free(aux1->key);
		free(aux1->value);
		aux->next = aux->next->next;
		free(aux1);
	}
}


int get_num_of_elements(listNode** listStart) {

	int ok = 0;
	listNode* p = *listStart;
	while (p != NULL)
	{
		ok++;
		p = p->next;
	}

	return ok;
}

void removeNodeHeadOfList(listNode** listStart) {
	if (*listStart == NULL)
		return;
	listNode* aux = (*listStart);
	if(aux->key != NULL)
		free(aux->key);
	free(aux->value);
	*listStart = (*listStart)->next;
	free(aux);
	aux=NULL;
}

void insertNodeHeadOfList(listNode** listStart, char* key, char* value) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (node == NULL) {
		fprintf(stderr, "ERROR: CAN NOT ALLOCATE RAM\n");
		return;
	}
	node->next = *listStart;
	node->key = (char*)malloc(strlen(key)+1);
	strcpy(node->key,key);
	//node->key = key;
	node->value = (char*)malloc(strlen(value)+1);
	//node->value = value;
	strcpy(node->value,value);

	*listStart = node;
}



listNode* getNode(listNode* listNode, int poz) {
	if (listNode == NULL)
		return NULL;
	for (int i = 0; i < poz; i++) {
		if (listNode->next == NULL)
			break;
		listNode = listNode->next;
	}
	return listNode;
}