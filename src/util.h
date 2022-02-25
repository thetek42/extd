#ifndef _H_UTIL
#define _H_UTIL


#include <stdbool.h>


#define STRCAT_A_BUF_MAX 1024


bool  file_exists (char *path);
char *file_read   (char *path);
void  file_write  (char *path, char *content);

void strcat_a           (char **dest, char *src);
void strcat_a_buf_char  (char **dest, char src);
void strcat_a_buf       (char **dest, char *src);
void strcat_a_buf_flush (char **dest);


#endif

