CC = gcc
CFLAGS = -Wall -g

build: so-cpp

so-cpp: Source.o preprocessor.o macroHandling.o command_parser.o algorithms.o hashmap.o list.o OutputFile.o
	$(CC) $(CFLAGS) $^ -o $@
Source.o: Source.c hashmap.h algorithms.h preprocessor.h utils.h OutputFile.h command_parser.h

preprocessor.o: preprocessor.c hashmap.h algorithms.h OutputFile.h macroHandling.h utils.h

macroHandling.o: macroHandling.c hashmap.h utils.h algorithms.h OutputFile.h preprocessor.h 

command_parser.o: command_parser.c command_parser.h utils.h

algorithms.o: algorithms.c algorithms.h utils.h

hashmap.o: hashmap.c list.c hashmap.h list.h utils.h 

list.o: list.c list.h

OutputFile.o: OutputFile.c OutputFile.h utils.h

.PHONY: clean

clean:
	rm *.o so-cpp