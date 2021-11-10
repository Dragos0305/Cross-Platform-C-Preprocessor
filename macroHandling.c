#include "macroHandling.h"
#include "preprocessor.h"
#include <limits.h>
int getMacroType(char* content)
{

    int define_indicator = strncmp(content, "#define",strlen("#define"));

    if (content[strlen(content)-1] == '\\' && define_indicator == 0) {
        return MULTI_LINE_DEFINE;
    }
    else if (content[strlen(content) - 1] != '\\' && define_indicator == 0) {
        return ONE_LINE_DEFINE;
    }

    if (strstr(content, "#ifdef"))
        return IFDEF_BLOCK;

    if (strstr(content, "#ifndef"))
        return IFNDEF_BLOCK;

    if (strstr(content, "#if"))
        return IF_BLOCK;

    if (strstr(content, "#include"))
        return INCLUDE_DIRECTIVE;

    if (strstr(content, "#endif"))
        return -2;

    return NORMAL_LINE;
}

void add_one_line_define(char* content, hashMap* HM) {

    int number_of_words;
    char** words = split_string(content, &number_of_words, " ");



    char* key = words[1];
    if (number_of_words == 2) {
        insertKeyValue(HM, key, (char*)" ");
        return;
    }


    char value[100];
    memset(value, 0, 100);

    for (int k = 2; k < number_of_words; k++) {

        char* check_value = getValue(*HM, words[k]);
        if (check_value != (char*)NULL)
            strcat(value, check_value);
        else
            strcat(value, words[k]);

        if (k >= 2 && k < number_of_words - 1) 
            strcat(value, " ");
        
    }

    insertKeyValue(HM, key, value);
    free(words);
}

void add_multi_line_define(char** content, hashMap* HM, int* start_index) {

    char value[100];
    strcpy(value, "");

    int number_of_words;
    char** words = split_string(content[*start_index], &number_of_words, " \\");
    char* key = words[1];

    for (int k = 2; k < number_of_words; k++) {

        char* test_value = getValue(*HM, words[k]);

        if (test_value != (char*)NULL)
            strcpy(words[k], test_value);


        strcat(value, words[k]);
        if (k > 1 && k < number_of_words)
            strcat(value, " ");
    }

    *start_index = *start_index + 1;
    free(words);
    while (strstr(content[*start_index], "\\")) {

        char** words = split_string(content[*start_index], &number_of_words, " \t\\");
        for (int k = 0; k < number_of_words; k++)
        {
            char* test_value = getValue(*HM, words[k]);
            if (test_value != (char*)NULL)
                strcat(value, test_value);
            else
                strcat(value, words[k]);

            if (k < number_of_words)
                strcat(value, " ");
        }

        *start_index = *start_index + 1;
        free(words);
    }

    words = split_string(content[*start_index], &number_of_words, " ");

    for (int k = 0; k < number_of_words; k++)
    {
        char* test_value = getValue(*HM, words[k]);
        if (test_value != (char*)NULL)
            strcpy(words[k], test_value);

        strcat(value, words[k]);

        if (k >= 0 && k < number_of_words - 1)
            strcat(value, " ");
    }

    insertKeyValue(HM, key, value);
    free(words);
    //start_index = *start_index + 1;


}


void undef(char* content, hashMap* HM) {

    
    char* key = strstr(content, " ") + 1;
    removeKey(HM, key);
   
}


int findKey(char** keys, int lenght_of_keys, char* content, int* number_of_chars) {

    if(lenght_of_keys == 0) {
        
        *number_of_chars = strlen(content);
        return -1;
    }


    
    int return_index = -1;
    int min = INT_MAX;

    int right = -1;
    
    char* left_quotion_mark = strstr(content, "\"");
    char* right_quotion_mark = (char*)NULL;

    if (left_quotion_mark != (char*)NULL) {

        left_quotion_mark = left_quotion_mark + 1;
        right_quotion_mark = strstr(left_quotion_mark, "\"");
        right = right_quotion_mark - content + 1;

    }

    if (left_quotion_mark == NULL && lenght_of_keys != 0) {

        
        for (int i = 0; i < lenght_of_keys; i++) {

           
            char* p = strstr(content, keys[i]);

            if (p != NULL) {

                int position = p - content;
                if (position < min) {

                    return_index = i;
                    min = position;
                    *number_of_chars = min;

                }
            }
        }
    }
    else {

        *number_of_chars = right;
        return -1;

    }

    if (return_index == -1) {

        
        *number_of_chars = strlen(content);
        return return_index;
    }
    else
        return return_index;
}

char* is_defined(char* line, hashMap* HM) {

    char* key = strstr(line, " ") + 1;
    char* is_defined = getValue(*HM, key);

    return is_defined;

}

void Parse_IFDEF(char** lines,int*final_index, OutputFile* FILE,hashMap*HM)
{
   
    char* isdefined = is_defined(lines[*final_index],HM);
    int endif_position = get_endif_position(lines, *final_index);
    int check_for_else = check_else(lines, *final_index);

    if (isdefined != NULL) {

        *final_index = *final_index + 1;
            
        if (check_for_else == -1) {

            for (int i = *final_index; i < endif_position; i++) {
                decide_block(lines,FILE, &i, HM);
            }
            *final_index = endif_position;
        }
        else{

            for (int i = *final_index; i < check_for_else; i++) {
                decide_block(lines, FILE, &i, HM);
               
            }
            *final_index = endif_position;
        }

    }
    else {

        if (check_for_else == -1)
            *final_index = endif_position;
        else
        {
            for (int i =check_for_else+1; i < endif_position; i++) {
                decide_block(lines, FILE, &i, HM);
            }
            *final_index = endif_position;
        }

    }
  
}

void Parse_IFNDEF(char** lines, int* start_index, OutputFile* FILE, hashMap* HM)
{
    char* isdefined = is_defined(lines[*start_index], HM);
    int endif_position = get_endif_position(lines, *start_index);
   // int check_for_else = check_else(lines, *start_index);
       
    if (isdefined == NULL) {

        *start_index = *start_index + 1;
            for (int i = *start_index; i < endif_position; i++) {
                decide_block(lines, FILE, &i, HM);
            }

        *start_index = endif_position;
    }
    else {
        *start_index = endif_position;
    }
    
}


void Parse_IF(char** lines, int* start_index, OutputFile* FILE, hashMap* HM)
{

    int number_of_conditions = 0;
    int conditions[10];
    char content[10][128];
    memset(content, 0, sizeof(content));

    char* find_end = strstr(lines[*start_index], "#endif");
    if (find_end != NULL)
        return;
    while (1) {

        //Parse if statement
        if (strstr(lines[*start_index], "#if")) {

            char* key = lines[*start_index] + strlen("#if ");
            char* value = getValue(*HM, key);

            if (value == NULL) {

                conditions[number_of_conditions] = atoi(key);
                *start_index = *start_index + 1;
                strcpy(content[number_of_conditions], lines[*start_index]);
                number_of_conditions++;
            }
            else {
                conditions[number_of_conditions] = atoi(value);
                *start_index = *start_index + 1;
                strcpy(content[number_of_conditions], lines[*start_index]);
                number_of_conditions++;
            }

        }

        //Parse elif statement
        if (strstr(lines[*start_index], "#elif")) {

            char* key = lines[*start_index] + strlen("#elif ");
            char* value = getValue(*HM, key);

            if (value == NULL) {
                conditions[number_of_conditions] = atoi(key);
                *start_index = *start_index + 1;
                strcpy(content[number_of_conditions], lines[*start_index]);
                number_of_conditions++;
            }
            else {
                conditions[number_of_conditions] = atoi(value);
                *start_index = *start_index + 1;
                strcpy(content[number_of_conditions], lines[*start_index]);
                number_of_conditions++;
            }

        }

        //Parse else statement
        if (strstr(lines[*start_index], "#else")) {

            *start_index = *start_index + 1;
            strcpy(content[number_of_conditions], lines[*start_index]);
        }


        //Check for end
        char* find_end = strstr(lines[*start_index], "#endif");
        if (find_end != NULL)
            break;
        
        *start_index = *start_index + 1;
        
    }


    //Search true condition
    for (int i = 0; i < number_of_conditions; i++) {

        //If find true condition addLine and return from frunction
        if (conditions[i] != 0) {

            int line_type = getMacroType(content[i]);
            if (line_type == ONE_LINE_DEFINE)
                add_one_line_define(content[i], HM);
            else
                addLine(FILE, content[i]);
            return;
        }
    }

    //Else case
    addLine(FILE, content[number_of_conditions]);



}

int check_guard(FILE*fp) {

    char line[100];
    fgets(line,100,fp);
    
    if(!strncmp(line,"#ifndef",strlen("#ifndef")))
        return 1;
    else
        return 0;

}

void Parse_Include_Directives(OutputFile* OF, hashMap* HM, char* include_directive) {

    char* header_name = strstr(include_directive,"\"") + 1;
    DIE(header_name == NULL, "No header name");
    header_name[strlen(header_name) - 1] = '\0';
    //collectMacros(HM, header_name, OF);
    char path[100];
    memset(path, 0, 100);
    strcpy(path,"_test/inputs/");
    strcat(path,header_name);
    FILE* test_exist = fopen(path, "r");
    
    if (test_exist != NULL) {

       
        collectMacros(HM, path, OF);
        return;
        
    }
    
    if (OF->number_of_paths == 0) {
       exit(12);
    }
    else {

       for (int i = 0; i < OF->number_of_paths; i++) {

           char path[100];
           memset(path, 0, 100);
           strcpy(path, OF->paths[i]);
           strcat(path,"/");
           strcat(path, header_name);
          
           test_exist = fopen(path, "r");

           if (test_exist != NULL) {
               fclose(test_exist);
               
               collectMacros(HM, path, OF);
               return;
           }
       }

    }


    exit(12);

    

}

int check_else(char** lines, int start_index)
{
    while (1)
    {
        if(!strncmp(lines[start_index],"#else",strlen("#else")))
            return start_index;

        if (!strncmp(lines[start_index], "#endif", strlen("#endif")))
            return -1;

        start_index = start_index + 1;
    }

    return 0;
}

int get_endif_position(char** lines, int start_index)
{
    listNode* head = NULL;
    char*blank_space = (char*)malloc(sizeof(char)+1);
    strcpy(blank_space," ");
    insertNodeHeadOfList(&head, lines[start_index], blank_space);
    start_index++;

    while (1) {

        if (!strncmp(lines[start_index], "#ifdef", strlen("#ifdef")) || !strncmp(lines[start_index], "#ifndef", strlen("#ifndef"))) {
            insertNodeHeadOfList(&head, lines[start_index], blank_space);
            
        }
        if (!strncmp(lines[start_index], "#endif", strlen("#endif"))) {
            removeNodeHeadOfList(&head);
            if (head == NULL){
                free(blank_space);
                return start_index;
            }
        }
        start_index++;
    }
    
    return 0;
}

void decide_block(char** lines, OutputFile* FILE, int* start_index, hashMap* HM)
{
    int line_type = getMacroType(lines[*start_index]);

    switch (line_type) {

    case ONE_LINE_DEFINE:
        add_one_line_define(lines[*start_index], HM);
        break;
    case IFNDEF_BLOCK:
        Parse_IFNDEF(lines, start_index, FILE, HM);
        break;
    case IF_BLOCK:
        Parse_IF(lines, start_index, FILE, HM);
        break;
    case NORMAL_LINE:
        addLine(FILE, lines[*start_index]);
        break;
    case INCLUDE_DIRECTIVE:
        Parse_Include_Directives(FILE, HM, lines[*start_index]);
        break;
    case IFDEF_BLOCK:
        Parse_IFDEF(lines, start_index, FILE, HM);
        break;
    default:
        break;
    }
}

