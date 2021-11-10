#include "hashmap.h"
#include "utils.h"


int hash(const char* str) {
	int sum = 0;
	for (; *str != '\0'; str++) {
		sum += *str;
		sum %= M;
	}
	return sum % M;
}


void insertKeyValue(hashMap* HM, char* key, char* value) {

	listNode* aux = NULL;
	aux = (listNode*)malloc(sizeof(listNode));
	DIE(aux == NULL, "Malloc error");

	//aux->key = NULL;
	aux->key = (char*)malloc(sizeof(char) * (strlen(key)+1));
	DIE(aux->key == NULL, "Malloc error");

	//aux->key = NULL;
	aux->value = (char*)malloc(sizeof(char) * (strlen(value)+1));
	DIE(aux->value == NULL, "Malloc error");

	strcpy(aux->key, key);
	strcpy(aux->value, value);
	aux->next = NULL;

	if (HM->buckets[hash(key)] == NULL)
	{
		HM->buckets[hash(key)] = aux;
		HM->numElements++;
	}
	else
	{
		insertNodeHeadOfList(&HM->buckets[hash(key)], key, value);
		HM->numElements++;
	}
}

char* getValue(hashMap HM, const char* key) {

	if (HM.buckets[hash(key)] == NULL) {

		return (char*)NULL;
	}

	if (HM.buckets[hash(key)]->next == NULL && !strcmp(HM.buckets[hash(key)]->key, key))
	{
		return HM.buckets[hash(key)]->value;
	}
	else
	{
		listNode* p = HM.buckets[hash(key)];
		while (p != NULL)
		{
			if (strcmp(p->key, key) == 0)
				return p->value;
			else
				p = p->next;
		}

	}
	return (char*)NULL;
}

void removeKey(hashMap* HM, const char* key) {

	listNode* p = NULL;
	p = HM->buckets[hash(key)];
	//int ok = 0;
	int count = 0;
	while (p != NULL)
	{
		if (!strcmp(p->key, key))
		{
			//ok = get_num_of_elements(&p);
			removeNodeFromList(&HM->buckets[hash(key)], count);
			HM->numElements = HM->numElements - 1;
			return;

		}
		count++;
		p = p->next;

	}


}

int getSize(hashMap HM) {
	return HM.numElements;
}

int isEmpty(hashMap HM) {
	return HM.numElements == 0;
}

void initHashMap(hashMap* HM) {
	HM->numElements = 0;
	for (int i = 0; i < M; i++)
		HM->buckets[i] = NULL;
}


char** getKeys(hashMap HM, int* number_of_keys) {

	if (HM.numElements == 0) {
		*number_of_keys = 0;
		return NULL;
	}

	char** keys = NULL;
	keys = (char**)malloc(sizeof(char*) * HM.numElements);
	DIE(keys == NULL, "Malloc error");
	unsigned int count = 0;
	for (int i = 0; i < M; i++) {

		if (HM.buckets[i] != NULL) {

			while (HM.buckets[i] != NULL)
			{
				unsigned long size = strlen(HM.buckets[i]->key);
				keys[count] = (char*)malloc(sizeof(char)*(size + 1));
				DIE(keys[count] == NULL, "Malloc error");


				strcpy(keys[count], HM.buckets[i]->key);
				//keys[count][size] = '\0';
				count++;
				HM.buckets[i] = HM.buckets[i]->next;
			}

		}

	}
	*number_of_keys = count;


	return keys;

}

void printHashMAp(hashMap HM) {

	for (int i = 0; i < 10; i++) {

		if (HM.buckets[i] != NULL) {

			while (HM.buckets[i] != NULL)
			{
				printf("Cheia %s valoarea %s\n", HM.buckets[i]->key, HM.buckets[i]->value);
				HM.buckets[i] = HM.buckets[i]->next;
			}

		}

	}

}

void free_map(hashMap*HM) {

for (size_t i = 0; i < M; i++)
{
	if(HM->buckets[i] != NULL) {

		while(HM->buckets[i] != NULL)
			removeNodeHeadOfList(&HM->buckets[i]);

	}
}




}