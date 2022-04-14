#ifndef _H_UTIL
#define _H_UTIL


#include <stdbool.h>


bool  file_exists (char *path);
char *file_read   (char *path);
void  file_write  (char *path, char *content);


#endif

