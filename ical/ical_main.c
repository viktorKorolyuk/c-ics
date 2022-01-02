#include "ical.h"
#include <stdlib.h>
#include <string.h>
#include "../string_extensions/string_extensions.h"
#include "../dtype_helpers/dtype_helpers.h"

int init_ical(struct ical_s *ical, FILE *instream)
{
  ical->instream = instream;
  return 0;
}

long consume__next_icalevent(struct ical_s *ical, struct VEVENT_s *event)
{
  event->attendee = calloc(2, sizeof(char *));
  struct dyn_arr attendees;
  
  // Initialise a dynamic array for attendees
  dyn_arr_init(&attendees, (void ***)&event->attendee, 2, sizeof(char *));

  char *buffer = NULL;
  size_t len;
  ssize_t characters;

  /// Consume lines until a BEGIN:VEVENT is found
  do
  {
    characters = getline(&buffer, &len, ical->instream);
    mutate__str_crlf_to_lf(buffer); // Clean the string
  } while (m_strneq(buffer, "BEGIN:VEVENT") && characters != EOF);

  if (characters == EOF)
    return EOF;

  // At this point buffer is equal to "BEGIN:VEVENT"
  while (m_strneq(buffer, "END:VEVENT") && characters != EOF)
  {
    char *key = NULL;
    char *value = NULL;
    consume__next_icalprop(ical, &key, &value);

    if (m_streq(key, "END") && m_streq(value, "VEVENT"))
      break;
    // printf("'%s' => '%s'\n", key, value);

    if (strstr(key, "ATTENDEE;") != NULL)
    {
      char *val_cpy = strdup(value); // WARN: MEM Alloc. Needs something to `free` it
      dyn_arr_push(&attendees, (long long)val_cpy);
    }

    if (key != NULL) // Always true
      free(key);
    if (value != NULL)
      free(value);
  }
  free(buffer);
  return 0;
}

void free_VEVENT_s(struct VEVENT_s *event)
{
  int i = 0;
  while (event->attendee[i])
  {
    free(event->attendee[i]);
    i++;
  }
  free(event->attendee);
}