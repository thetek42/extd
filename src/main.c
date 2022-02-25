#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extd.h"
#include "macros.h"
#include "util.h"
#include "themes/default.h"


int
main (int    argc,
      char **argv)
{
    if (argc == 1)
        PRINT_USAGE ();
    else if (strcmp (argv[1], "-h") == 0 || strcmp (argv[1], "--help") == 0)
        PRINT_USAGE ();
    else
    {
        char *input_file = argv[1];
        if (!file_exists (input_file))
            DIE ("File '%s' does not exist.\n", input_file);

        char *output_file = NULL;
        char *theme = "default";
        bool  custom_theme = false;
        
        for (int i = 2; i < argc; i++)
        {
            if (strcmp (argv[i], "-o") == 0 || strcmp (argv[i], "--output") == 0)
            {
                if (argc == i+1)
                    DIE ("Missing argument after option %s\n", argv[i]);
                output_file = argv[++i];
            }
            else if (strcmp (argv[i], "-t") == 0 || strcmp (argv[i], "--theme") == 0)
            {
                if (argc == i+1)
                    DIE ("Missing argument after option %s\n", argv[i]);
                theme = argv[++i];
                if (strcmp (theme, "default") != 0)
                {
                    if (!file_exists (theme))
                        DIE ("Theme '%s' does not exist.\n", theme);
                    custom_theme = true;
                }
            }
            else DIE ("Unrecognized option %s\n", argv[i]);
        }

        bool output_file_malloced = false;
        if (!output_file)
        {
            size_t len = strlen (input_file);
            if (!strcmp (input_file + len - 5, ".extd"))
            {
                output_file = malloc (sizeof (char) * (len + 1));
                if (!output_file) MALLOC_FAILED ();
                strncpy (output_file, input_file, len - 4);
                strcpy (output_file + len - 4, "html");
            }
            else
            {
                output_file = malloc (sizeof (char) * (len + 6));
                if (!output_file) MALLOC_FAILED ();
                strcpy (output_file, input_file);
                strcpy (output_file + len, ".html");
            }
            output_file_malloced = true;
        }

        char *inbuf = file_read (input_file);
        char *css;
        if (custom_theme)
            css = file_read (theme);
        else
        {
            // TODO: add more themes
            if (strcmp (theme, "default") == 0)
                css = THEME_DEFAULT;
            else
                css = THEME_DEFAULT;
        }

        char *html = extd_to_html (inbuf, css);

        file_write (output_file, html);

        free (inbuf);
        if (custom_theme) free (css);
        if (output_file_malloced) free (output_file);
    }

    return EXIT_SUCCESS;
}

