#ifndef _H_MACROS
#define _H_MACROS


#include <stdio.h>
#include <stdlib.h>



/* string macros */

#define ERROR  "[\x1b[31mERROR\x1b[0m] "
#define LINENR "\x1b[34mLine %zu\x1b[0m: "



/* usage / help text */

#define PRINT_USAGE() printf (                                                    \
        "Usage: `extd <file> [options]`\n\n"                                      \
        "Available options:\n"                                                    \
        "  -h  --help    Prints this message.\n"                                  \
        "  -o  --output  Specifies the output location. If ommited, the output\n" \
        "                file will be chosen based on the input filename.\n"      \
        "  -t  --theme   Specifies the theme to be used in the resulting HTML.\n" \
        "                Can either be a built-in theme, or a custom CSS file.\n")



/* error handling */

#define DIE(...)                    \
    do {                            \
        printf (ERROR __VA_ARGS__); \
        exit (EXIT_FAILURE);        \
    } while (0)

#define MALLOC_FAILED() DIE ("Failed to allocate memory.\n")



/* macros that hopefully make extd.c more readable */

#define CLEAN_UP_P_TAGS()                                                                               \
    do {                                                                                                \
        if (p_tag_open)                                                                                 \
        {                                                                                               \
            if (format_len > 0)                                                                         \
                DIE ("Unclosed formatting tag in paragraph before \x1b[34mline %zu\x1b[0m.\n", linenr); \
            strcat_a_buf (&html, "</p>\n");                                                             \
            p_tag_open = false;                                                                         \
        }                                                                                               \
    } while (0)

#define FORMAT_CHAR(key, tag)                                                                        \
    format_pos = formatpos (formats, (key), format_len);                                             \
    if (format_pos >= 0)                                                                             \
    {                                                                                                \
        if (format_len > (size_t) format_pos + 1) DIE (LINENR "Unclosed formatting tag.\n", linenr); \
        format_len--;                                                                                \
        strcat_a_buf (&html, "</" tag ">");                                                          \
    }                                                                                                \
    else                                                                                             \
    {                                                                                                \
        formats[format_len] = key;                                                                   \
        format_len++;                                                                                \
        strcat_a_buf (&html, "<" tag ">");                                                           \
    }



#endif

