#include "hashmap.h"
#include "algorithms.h" 
#include "preprocessor.h"
#include "utils.h"
#include "OutputFile.h"
#include "command_parser.h"

int main(int argc, char const* argv[])
{
    //Init hashmap
    hashMap HM;
    initHashMap(&HM);

    //Init struct for final output
    OutputFile* OF = (OutputFile*)malloc(sizeof(OutputFile));
    initFile(OF);

    char* filename = NULL;
    char* output_filename = NULL;
    for (int i = 1; i < argc; i++) {

        int FlagType = getFlagType(argv[i]);

        switch (FlagType)
        {

        case D_FLAG:
            parse_D_FLAG(argv, &i, &HM);
            break;
        case I_FLAG: ;
            char* path; 
            path = parse_I_FLAG(argv,&i);
            addPath(OF,path);
            break;
        case O_FLAG:
            output_filename = parse_O_FLAG(argv, &i);
            DIE(filename == NULL, "Filename error");
            break;
        case INFILE:
            filename = infile(argv[i]);
            break;
        default:
            exit(12);
            break;
        }

    }
   

    if(filename == NULL) {

        filename = strdup("stdin");
        FILE*fp = fopen(filename,"w");

        char content[256];
        while(fgets(content,256,stdin)!=NULL)
            fprintf(fp,"%s\n",content);

        fclose(fp);
   }

    collectMacros(&HM, filename,OF);
    replaceMacros(filename, HM,OF);

   

    if(output_filename !=NULL) {
            FILE*to_write = fopen(output_filename,"w");
            SaveContent(to_write,OF);
    }else
            printContent(OF);

    for(int i=0;i<OF->number_of_lines;i++)
        free(OF->lines[i]);

    
    free(OF->lines);
    free(filename);
    free(OF);
    free_map(&HM);
    


    return 0;
}

