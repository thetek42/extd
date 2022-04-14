#ifndef _H_STRUTIL
#define _H_STRUTIL


#include <stddef.h>


#define STR_ALLOC 512


typedef struct {
    char  *str;
    size_t len;
    size_t allocated_len;
} str_t;


str_t str_new  ();
void  str_cat  (str_t *dest, char *src);
void  str_lcat (str_t *dest, char *src, size_t len);
void  str_ccat (str_t *dest, char c);
void  str_free (str_t str);


#endif

