#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "ical.h"
#include "../string_extensions/string_extensions.h"

/**
 * @brief Read an `.ics` file and return the next property in a key-value pair.
 *        Lines are unfolded automatically.
 *        Property values are not checked for validity with the rfc5545 spec.
 * 
 * @param ical Initialised ical_s struct
 * @param key out KEY of an ics prop
 * @param value out VALUE of an ics prop
 * @return int 
 */
int consume__next_icalprop(struct ical_s *ical, char **key, char **value)
{
  char *buffer = NULL;
  size_t len;
  ssize_t characters;
  characters = getline(&buffer, &len, ical->instream);
  mutate__str_crlf_to_lf(buffer); // Clean the string

  str_split(buffer, ":", key, value);

  // Unfold lines
  while (feof(ical->instream) == 0) // Base case: Loop until no more data is available
  {
    char next = getc(ical->instream);
    if (isspace(next) == 0) // If it is not a space, the line is not 'folded'
    {
      ungetc(next, ical->instream); // Push the character back to be used for the next read
      break;
    }

    buffer = NULL;
    characters += getline(&buffer, &len, ical->instream);
    mutate__str_crlf_to_lf(buffer); // Clean the string

    // Case 1: The colon was not in the last entry, thus the key is not finished
    if (*value == NULL)
    {
      char *key_next = NULL;
      str_split(buffer, ":", &key_next, value);

      const ssize_t size = strlen(*key) + strlen(key_next) + 2;

      // Reallocate the memory as the previous size was smaller
      *key = realloc(*key, size);
      strlcat(*key, key_next, size);
    }

    // Case 2: The last line ended with a colon, in which case read a value
    else if (*value != NULL && **value == '\0')
    {
      *value = strndup(buffer, characters);
    }
    // Case 3: The value is not finished
    else
    {
      const size_t len = strlen(*value) + characters + 2;
      *value = realloc(*value, len);
      strlcat(*value, buffer, len);
    }

    // Release the allocated memory
    free(buffer);
  }

  return characters;
}