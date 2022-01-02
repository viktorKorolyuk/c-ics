#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "string_extensions/string_extensions.h"
#include "ical/ical.h"

int main(int argc, char **argv)
{
  FILE *file = fopen("sample.ics", "r");
  struct ical_s ical;
  init_ical(&ical, file);
  struct VEVENT_s event;
  while (1)
  {
    long s = consume__next_icalevent(&ical, &event);
    
    int i = 0;
    while(event.attendee[i])
    {
      if (i == 0) printf("Attendees:\n");
      printf("\tAttendee information: %s\n", event.attendee[i]);
      i++;
    }
    free_VEVENT_s(&event);
    if (s == EOF)
      break;
  }
  return 0;
}