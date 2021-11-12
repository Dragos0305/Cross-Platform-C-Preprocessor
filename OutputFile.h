#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct OutputFile {

	char** lines;
	int number_of_lines;
	char paths[100][100];
	int number_of_paths;
}OutputFile;


void addLine(OutputFile* FILE, char* line);
void printContent(OutputFile* FILE);
void initFile(OutputFile* FILE);
void SaveContent(FILE* to_write, OutputFile* FILE);
void addPath(OutputFile* FILE, char* path);
//void deteleFile(OutputFile* FILE);
//void replaceLine(OutputFile* FILE, int line_number, char* line);

	


	







#endif