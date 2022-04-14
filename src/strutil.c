#include "strutil.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"



str_t
str_new ()
{
    char *content;
    if ((content = malloc (STR_ALLOC)) == NULL) MALLOC_FAILED ();
    content[0] = '\0';
    return (str_t) {
        content,
        0,
        STR_ALLOC,
    };
}


void
str_cat (str_t *dest,
         char  *src)
{
    str_lcat (dest, src, strlen (src));
}


void
str_lcat (str_t *dest,
          char  *src,
          size_t len)
{
    if (len >= dest->allocated_len - dest->len)
    {
        size_t to_alloc = (len / STR_ALLOC + 1) * STR_ALLOC;
        char *res;
        if ((res = malloc (dest->allocated_len + to_alloc)) == NULL) MALLOC_FAILED ();
        res[0] = '\0';
        strcat (res, dest->str);
        strcat (res, src);
        free (dest->str);
        dest->str = res;
        dest->len += len;
        dest->allocated_len += to_alloc;
    }
    else
    {
        strcat (dest->str, src);
        dest->len += len;
    }
}


void
str_ccat (str_t *dest,
          char   c)
{
    if (dest->len + 1 >= dest->allocated_len)
    {
        char *res;
        if ((res = malloc (dest->allocated_len + STR_ALLOC)) == NULL) MALLOC_FAILED ();
        strcpy (res, dest->str);
        res[dest->len] = c;
        dest->len++;
        res[dest->len] = '\0';
        free (dest->str);
        dest->str = res;
        dest->allocated_len += STR_ALLOC;
    }
    else
    {
        dest->str[dest->len] = c;
        dest->len++;
    }
}


void
str_free (str_t str)
{
    free (str.str);
}

