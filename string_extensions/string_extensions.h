#ifndef STRING_EXTENSIONS
#define STRING_EXTENSIONS
#include <string.h>

#define m_streq(a, b) strcasecmp(a, b) == 0
#define m_strneq(a, b) strcasecmp(a, b) != 0

void mutate__str_limit_to_first_chr(char *str, char target);
void mutate__str_crlf_to_lf(char *str);
void str_split(char *str, char *target, char **first, char **remainder);
#endif