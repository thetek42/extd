#include "util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "macros.h"


static char   STRCAT_A_BUF_BUFFER [STRCAT_A_BUF_MAX] = { 0 };
static size_t STRCAT_A_BUF_SIZE = 0;


bool
file_exists (char *path)
{
    return access (path, F_OK) == 0;
}


char *
file_read (char *path)
{
    FILE *f;
    char *buffer;
    long  len;

    f = fopen (path, "r");

    if (f)
    {
        fseek (f, 0, SEEK_END);
        len = ftell (f);
        fseek (f, 0, SEEK_SET);

        buffer = malloc (len + 1);

        if (buffer)
        {
            fread (buffer, 1, len, f);
            buffer[len] = '\0';
        }
        else MALLOC_FAILED ();

        fclose (f);
    }
    else DIE ("Cannot read file '%s'\n", path);

    return buffer;
}


void
file_write (char *path,
            char *content)
{
    FILE *f;
    f = fopen (path, "w+");
    if (fputs (content, f) == EOF)
        DIE ("Could not write to file %s.", path);
    fclose (f);
}


void
strcat_a (char **dest,
          char  *src)
{
    char *res;
    if ((res = malloc (sizeof (char) * (strlen (*dest) + strlen(src) + 1))) != NULL)
    {
        res[0] = '\0';
        strcat (res, *dest);
        strcat (res,  src);
    }
    else MALLOC_FAILED ();
    free (*dest);
    *dest = res;
}


void
strcat_a_buf_char (char **dest,
                   char   src)
{
    STRCAT_A_BUF_BUFFER[STRCAT_A_BUF_SIZE] = src;
    STRCAT_A_BUF_SIZE++;

    if (STRCAT_A_BUF_SIZE == STRCAT_A_BUF_MAX)
        strcat_a_buf_flush (dest);
}


void
strcat_a_buf (char **dest,
                  char  *src)
{
    size_t srclen = strlen (src);
    if (srclen + STRCAT_A_BUF_SIZE > STRCAT_A_BUF_MAX)
    {
        strcat_a_buf_flush (dest);
        strcat_a (dest, src);
    }
    strncpy (STRCAT_A_BUF_BUFFER + STRCAT_A_BUF_SIZE, src, srclen);
    STRCAT_A_BUF_SIZE += srclen;

    if (STRCAT_A_BUF_SIZE == STRCAT_A_BUF_MAX)
        strcat_a_buf_flush (dest);
}


void
strcat_a_buf_flush (char **dest)
{
    char *res;
    size_t dest_len = strlen (*dest);
    if ((res = malloc (sizeof (char) * (dest_len + STRCAT_A_BUF_SIZE + 1))))
    {
        res[0] = '\0';
        strcat (res, *dest);
        strncat (res, STRCAT_A_BUF_BUFFER, STRCAT_A_BUF_SIZE);
        res[dest_len + STRCAT_A_BUF_SIZE] = '\0';
    } else MALLOC_FAILED ();
    free (*dest);
    *dest = res;
    STRCAT_A_BUF_SIZE = 0;
}

