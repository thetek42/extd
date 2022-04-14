#include "extd.h"

#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "strutil.h"
#include "types.h"
#include "util.h"


str_t
extd_to_html (char* extd,
              char* css)
{
    str_t html = str_new ();

    str_lcat (&html, "<html>\n<head>\n<style>\n\n", 23);
    str_cat (&html, css);
    str_lcat (&html, "\n</style>\n</head>\n<body>\n\n", 26);


    size_t   linenr        = 0;
    bool     start_of_line = true;
    bool     p_tag_open    = false;
    size_t   format_len    = 0;
    format_t formats[FORMAT_T_LEN];
    ssize_t  format_pos    = 0;

    for (size_t c = 0; c < strlen (extd); c++)
    {
        if (start_of_line) linenr++;

        // newlines
        if (extd[c] == '\n')
        {
            CLEAN_UP_P_TAGS ();
            str_ccat (&html, '\n');
        }

        // headers
        else if (start_of_line && extd[c] == '#')
        {
            CLEAN_UP_P_TAGS ();
            size_t header_level = 0;
            while (start_of_line && extd[c] == '#') { header_level++; c++; }
            if (header_level > 6) DIE (LINENR "Headers can only have up to 6 levels.\n", linenr);
            str_lcat (&html, (char[]){'<','h',header_level+48,'>','\0'}, 4);
            while (extd[c] == ' ') c++;
            while (extd[c] != '\n')
                str_ccat (&html, extd[c++]);
            str_lcat (&html, (char[]){'<','/','h',header_level+48,'>','\n','\0'}, 5);
        }

        // regular paragraphs
        else
        {
            if (!p_tag_open)
            {
                str_lcat (&html, "<p>\n", 4);
                p_tag_open = true;
            }
            while (extd[c] != '\n')
            {
                switch (extd[c])
                {
                    case '\\': c++; str_ccat (&html, extd[c]); break;
                    case '*': FORMAT_CHAR (FMT_BOLD,      "b");    break;
                    case '_': FORMAT_CHAR (FMT_ITALIC,    "i");    break;
                    case '=': FORMAT_CHAR (FMT_UNDERLINE, "u");    break;
                    case '|': FORMAT_CHAR (FMT_HIGHLIGHT, "emph"); break;
                    case '`': FORMAT_CHAR (FMT_MONOSPACE, "code"); break;
                    default: str_ccat (&html, extd[c]);
                }
                c++;
            }
            str_ccat (&html, '\n');
        }

        start_of_line = (extd[c] == '\n');
    }

    CLEAN_UP_P_TAGS ();


    str_lcat (&html, "</body>\n</html>\n\n", 17);

    return html;
}


ssize_t
formatpos (format_t formats[],
           format_t fmt,
           size_t   fmtlen)
{
    for (size_t i = 0; i < fmtlen; i++)
        if (formats[i] == fmt)
            return i;
    return -1;
}

