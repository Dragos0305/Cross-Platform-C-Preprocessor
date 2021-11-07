#include "hashmap.h"
#include "algorithms.h" 
#include "preprocessor.h"
#include "utils.h"
#include "Outputfile.h"
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

    for (int i = 1; i < argc; i++) {

        int FlagType = getFlagType(argv[i]);

        switch (FlagType)
        {

        case D_FLAG:
            parse_D_FLAG(argv, &i, &HM);
            break;
        case I_FLAG:
            char* path = parse_I_FLAG(argv,&i);
            addPath(OF,path);
            break;
        case O_FLAG:
            filename = parse_O_FLAG(argv, &i);
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
   
    collectMacros(&HM, filename,OF);
    replaceMacros(filename, HM,OF);
    printContent(OF);

    free(OF->lines);
    free(OF);
   
    


    return 0;
}

