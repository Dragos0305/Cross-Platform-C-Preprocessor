#include "algorithms.h"
#include "utils.h"

char** split_string(char* str, int* lenght, const char* delim) {

    
    char** splits = NULL;
    char* token = strtok(str, delim);
    
    int spaces = 0;

    while (token) {
        splits = (char**)realloc(splits, sizeof(char*) * ++spaces);
        DIE(splits == NULL, "Realloc error");
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, delim);
    }
    *lenght = spaces;

    DIE(splits[spaces - 1] == NULL, "Space doesn't exist");
    for (int i = 0; i < strlen(splits[spaces - 1]); i++) {

        if (splits[spaces - 1][i] < 0) {
            splits[spaces - 1][i] = '\0';
            break;
        }
    }

    return splits;


}

char* getFIleContent(const char* filename) {

    FILE* fp = fopen(filename, "r");
    size_t rc;

    if (fp == NULL) {
        fprintf(stderr, "Cannot open file %s", filename);
        exit(1);
    }

    //long file_size = getFileSize(fp);
    //char* content = (char*)malloc(file_size + 1);
    char content[256];
    DIE(content == NULL, "Malloc error");

    rc = fread(content, sizeof(char), 256, fp);
    content[rc] = '\0';

    char*return_value = (char*)malloc(strlen(content)+1);
    strcpy(return_value,content);    

    if (!rc) {
        fprintf(stderr, "Can't read content\n");
    }
    
    
    fclose(fp);

    return return_value;
}

long getFileSize(FILE* fp) {

    fseek(fp, 0, SEEK_END);
    long return_value = ftell(fp);
    rewind(fp);
    return return_value;

}

FILE* openFile(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    return fp;

}