#include "OutputFile.h"

void addLine(OutputFile* FILE, char* line)
{
	if( !strlen(line) )
	 	return;
		
	if (FILE->number_of_lines == 0) {

		FILE->lines = (char**)malloc(sizeof(char*));
		DIE(FILE->lines == NULL, "Malloc error");

		FILE->lines[FILE->number_of_lines] = (char*)malloc(strlen(line) * sizeof(char) + 1);
		DIE(FILE->lines[FILE->number_of_lines] == 0, "Error malloc");

		strcpy(FILE->lines[FILE->number_of_lines], line);
		FILE->number_of_lines++;

	}
	else if(FILE->number_of_lines > 0) {

		DIE(FILE->lines == NULL, "Passing NULL pointer to realloc");
		FILE->lines = (char**)realloc(FILE->lines, sizeof(char*) * ++(FILE->number_of_lines));
		DIE(FILE->lines == NULL, "Realloc error");

		FILE->lines[FILE->number_of_lines - 1] = (char*)malloc(sizeof(char) * (strlen(line) +1));
		DIE(FILE->lines[FILE->number_of_lines - 1] == NULL, "Malloc error");

		strcpy(FILE->lines[FILE->number_of_lines - 1], line);
	}


}

void printContent(OutputFile* FILE) {
	for ( int i = 0; i < FILE->number_of_lines; ++i)
	{
		printf("%s\n", FILE->lines[i]);
	}

}

void initFile(OutputFile* FILE) {

	FILE->lines = NULL;
	//FILE->paths = NULL;
	FILE->number_of_lines = 0;
	FILE->number_of_paths = 0;
}

void SaveContent(FILE* to_write, OutputFile* FILE) {
	for (int i = 0; i < FILE->number_of_lines; i++) {

		fprintf(to_write, "%s\n", FILE->lines[i]);
	}

}

void addPath(OutputFile* FILE, char* path) {



	strcpy(FILE->paths[FILE->number_of_paths++],path);
	
	// if (FILE->number_of_paths == 0) {

	// 	FILE->paths = (char**)malloc(sizeof(char*));
	// 	DIE(FILE->paths == NULL, "Malloc error");

	// 	FILE->paths[FILE->number_of_paths] = (char*)malloc(sizeof(char) * (strlen(path) + 1));
	// 	DIE(FILE->paths[FILE->number_of_paths] == 0, "Error malloc");

	// 	strcpy(FILE->paths[FILE->number_of_paths], path);
	// 	FILE->number_of_paths++;

	// }
	// else if (FILE->number_of_paths > 0) {
		
	// 	DIE(FILE->paths == NULL, "Passing NULL pointer to realloc");
	// 	FILE->paths = (char**)realloc(FILE->lines, sizeof(char*) * ++(FILE->number_of_paths));
	// 	DIE(FILE->paths == NULL, "Realloc error");

	// 	FILE->paths[FILE->number_of_paths - 1] = (char*)malloc(sizeof(char) * (strlen(path)+1));
	// 	DIE(FILE->paths[FILE->number_of_paths - 1] == NULL, "Malloc error");

	// 	strcpy(FILE->paths[FILE->number_of_paths - 1], path);
	// }


}
