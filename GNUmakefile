CC = cl
CFLAGS = /MD /D_CRT_SECURE_NO_WARNINGS


so-cpp.exe: Source.obj preprocessor.obj macroHandling.obj command_parser.obj algorithms.obj hashmap.obj list.obj OutputFile.obj
	link /nologo /out:$@ $**

Source.obj: Source.c hashmap.h algorithms.h preprocessor.h utils.h OutputFile.h command_parser.h

preprocessor.obj: preprocessor.c hashmap.h algorithms.h OutputFile.h macroHandling.h utils.h

macroHandling.obj: macroHandling.c hashmap.h utils.h algorithms.h OutputFile.h preprocessor.h 

command_parser.obj: command_parser.c command_parser.h utils.h

algorithms.obj: algorithms.c algorithms.h utils.h

hashmap.obj: hashmap.c list.c hashmap.h list.h utils.h 

list.obj: list.c list.h

OutputFile.obj: OutputFile.c OutputFile.h utils.h

clean:
	del *.obj *.exe