#ifndef _H_EXTD
#define _H_EXTD


#include <sys/types.h>
#include "strutil.h"
#include "types.h"


str_t   extd_to_html (char *extd, char *css);
ssize_t formatpos    (format_t formats[], format_t fmt, size_t fmtlen);


#endif

