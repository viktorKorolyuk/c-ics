#include "string_extensions.h"

/**
 * @brief Mutate the input string such that it ends at the first occurance of `target`.
 *        A NULL is inserted at the first character position of `target`.
 * 
 * @param str Input string
 * @param target Target character to limit the string
 */
void mutate__str_limit_to_first_chr(char *str, char target)
{
  char *index = str;
  while (*index != '\0')
  {
    if (*index == target)
    {
      *index = 0;
      return;
    }
    index++;
  }
}

void mutate__str_crlf_to_lf(char *str)
{
  mutate__str_limit_to_first_chr(str, '\n'); // Remove newline
  mutate__str_limit_to_first_chr(str, '\r'); // Remove carriage return (\r) when parsing CRLF
}