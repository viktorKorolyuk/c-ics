#ifndef ICAL
#define ICAL
#include <time.h>
#include <stdio.h>

struct ical_s
{
  FILE *instream;
};

struct VEVENT_s
{
  /* Required */
  time_t dtstamp;
  char *uid;

  /* Required if VEVENT does not sepecify a METHOD property */
  time_t dtstart;

  /* Optional */
  char *class;
  time_t created;
  char *description;
  char *geo;
  time_t last_mod;
  char *location;
  char *organizer;
  char *priority;
  char *seq;
  char *status;
  char *summary;
  char *transp;
  char *url;
  char *recurid;

  /* Optional class 2 */
  char *rrule;

  /* Mutually exclisive */
  time_t dtend;
  time_t duration;

  /* Optional and can occur more than once */
  char **attach;
  char **attendee;
  char **categories;
  char **comment;
  char **contact;
  char **exdate;
  char **rstatus;
  char **related;
  char **resources;
  char **rdate;
  char **x_prop;
  char **iana_prop;
  // attach / attendee / categories / comment /
  //                 contact / exdate / rstatus / related /
  //                 resources / rdate / x-prop / iana-prop
};
int init_ical(struct ical_s *ical, FILE *instream);
int consume__next_icalprop(struct ical_s *ical, char **key, char **value);
long consume__next_icalevent(struct ical_s *ical, struct VEVENT_s *event);
void free_VEVENT_s(struct VEVENT_s *event);
#endif