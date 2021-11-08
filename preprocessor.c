#include "preprocessor.h"
#include "utils.h"
#include "macroHandling.h"


void collectMacros(hashMap* HM, const char* filename, OutputFile* OF) {

    char* content = getFIleContent(filename);
    
    int number_of_lines;
    char** lines = split_string(content, &number_of_lines, "\n");
    

    for (int i = 0; i < number_of_lines; i++) {

        int define_type = getMacroType(lines[i]);
        
        switch (define_type)
        {
        case ONE_LINE_DEFINE:
            add_one_line_define(lines[i], HM);
            break;
        case MULTI_LINE_DEFINE:
            add_multi_line_define(lines, HM, &i);
            break;
        case IFDEF_BLOCK:
            Parse_IFDEF(lines, &i, OF,HM);
            break;
        case IFNDEF_BLOCK:
            Parse_IFNDEF(lines, &i, OF, HM);
            break;
        case IF_BLOCK:
            Parse_IF(lines, &i, OF, HM);
            
            break;
        case INCLUDE_DIRECTIVE:
            Parse_Include_Directives(OF, HM, lines[i]);
            break;
        case NORMAL_LINE:
            addLine(OF, lines[i]);
            break;
        default:
            break;
        }

    }

   
   
    
    // for (int i = 0; i < number_of_lines; i++)
    // {
    //     free(lines[i]);
    //     lines[i] = NULL;
    // }
    
    free(lines);
    lines = NULL;
    free(content);
    content = NULL;
}



void replaceMacros(const char* filename, hashMap HM,OutputFile* OF) {

    
    int number_of_keys;
    char** keys = getKeys(HM, &number_of_keys);

    for (int i = 0; i < OF->number_of_lines; i++)
    {

        char*test_undef = strstr(OF->lines[i], "#undef");
        if (test_undef) {
            
            
            undef(OF->lines[i], &HM);
             
            memset(OF->lines[i],0,strlen(OF->lines[i]));
            strcpy(OF->lines[i], "\n\0");
            keys = getKeys(HM, &number_of_keys);
            i++;
            
        }
       
        // if (!strncmp(OF->lines[i], "#undef",strlen("#undef"))) {
            
            
        //     undef(OF->lines[i], &HM);
        //     char* newline = strdup("\n");
        //     strcpy(OF->lines[i], newline);
            
        //     for(int i=0;i<number_of_keys;i++)
        //         free(keys[i]);

        //     free(keys);
        //     keys = getKeys(HM, &number_of_keys);
            
        //     i = i+1;
        //     //printf("Am iterat i ul\n");
        //    // printf("Linia curenta este: %s\n",OF->lines[i]);
        //     //printf("Dimensiune: %d",strlen(OF->lines[i]));
        // }

            char modified_line[100];
            int chars_to_copy;
            
            
            memset(modified_line, 0, 100);
            int line_size = strlen(OF->lines[i]);
            int position_reminder = line_size;
            
            while (line_size) {

                int index = findKey(keys, number_of_keys, OF->lines[i], &chars_to_copy);
               
                if (index == -1) {
                    
                   
                    strncat(modified_line,OF->lines[i], chars_to_copy);
                    OF->lines[i] = OF->lines[i] + chars_to_copy;
                    line_size -= chars_to_copy;
                   

                }
                else {

                    strncat(modified_line,OF->lines[i], chars_to_copy);
                    char* value = getValue(HM, keys[index]);
                    strcat(modified_line, value);
                    OF->lines[i] = OF->lines[i] + chars_to_copy + strlen(keys[index]);
                    line_size -= chars_to_copy;
                    line_size -= strlen(keys[index]);

                }

            }

           OF->lines[i] = OF->lines[i] - position_reminder;
           memcpy(OF->lines[i], modified_line,strlen(modified_line));
           OF->lines[i][strlen(modified_line)] = '\0';
           
           
    }
    
    for (int i = 0; i < number_of_keys; i++)
    {
        free(keys[i]);
        keys[i] = NULL;
    }
    free(keys);
    
}