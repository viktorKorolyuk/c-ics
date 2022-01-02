#include <string.h>
#include <stdlib.h>
#include "string_extensions.h"

/**
 * @brief Split a string `str` at the first occurance of a character in `target`.
 *        The substring before the split is stored in `first` and substring after the split is stored in `remainder`.
 * 
 * @param str Input string
 * @param target Split delimiter
 * @param first out KEY
 * @param remainder out VALUE
 */
void str_split(char *str, char *target, char **first, char **remainder)
{
  char *str_copy = strndup(str, strlen(str) + 1);

  if (str_copy == NULL)
    return; // Memory allocation failed

  char *remainder_mem = str_copy; // Mutable pointer to the remainder
  strsep(&remainder_mem, target); // Set '\0' at the first occurance of the delimiter

  // Copy first and remainder
  *first = strndup(str_copy, strlen(str_copy) + 1);

  // remainder_mem is NULL when the target characters were not found
  if (remainder_mem != NULL)
  {
    *remainder = strndup(remainder_mem, strlen(remainder_mem) + 1);
  }
  else
  {
    *remainder = NULL;
  }

  free(str_copy);
}