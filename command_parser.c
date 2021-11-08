#include "command_parser.h"
#include "string.h"
#include "utils.h"

int getFlagType(const char* content)
{
	if (strstr(content, "-D"))
		return D_FLAG;
	
	if (strstr(content, "-I"))
		return I_FLAG;

	if (strstr(content, "-o"))
		return O_FLAG;

	if (strchr(content, '-'))
		return -1;
	return INFILE;
}

void parse_D_FLAG(char const* args[], int* index, hashMap* HM)
{
	if (strlen(args[*index]) == 2) {

		*index = *index + 1;
		int len;
		char** key_value = split_string((char*)args[*index], &len, "=");
		if (len == 2)
			insertKeyValue(HM, key_value[0], key_value[1]);
		else
			insertKeyValue(HM, key_value[0], (char*)" ");

		free(key_value);
		key_value = NULL;
	}
	else {

		args[*index] = args[*index] + 2;
		int len;
		char** key_value = split_string((char*)args[*index], &len, "=");
		if (len == 2)
			insertKeyValue(HM, key_value[0], key_value[1]);
		else
			insertKeyValue(HM, key_value[0], (char*)" ");

		free(key_value);
		key_value = NULL;
	}
	
}

char* parse_I_FLAG(char const* args[], int* index)
{
	
	if(strlen(args[*index]) == 2) {

		*index = *index + 1;
		return (char*)args[*index];
	}else {

		args[*index] = args[*index] + 2;
		return (char*)args[*index];

	}


	
}

char* parse_O_FLAG(char const* args[], int* index)
{
	char* filename = NULL;
	if (strlen(args[*index]) == 2) {

		*index = *index + 1;
		filename = (char*)malloc(sizeof(char) * strlen(args[*index]));
		DIE(filename == NULL, "Memory Allocation Error");
		strcpy(filename, args[*index]);
		return filename;


	}
	else {

		args[*index] = args[*index] + 2;
		filename = (char*)malloc(sizeof(char) * strlen(args[*index]));
		DIE(filename == NULL, "Memory Allocation Error");
		strcpy(filename, args[*index]);
		return filename;
	}
	

	return filename;
}

char* infile(char const* filename)
{
	unsigned int size = strlen(filename) + 1;
	char* infile = (char*)malloc(size * sizeof(char));
	memcpy(infile, filename, size);
	

	return infile;
}