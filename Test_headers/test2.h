#ifndef DEBUG_STR
#define DEBUG_STR "debuging
#endif
 
#if DEBUG
#define debug fprintf(stderr, DEBUG_STR "\n")
#else
#define debug
#endif
