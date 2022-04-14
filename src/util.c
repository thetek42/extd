#include "util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "macros.h"


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

