# c_ics
This project aims to provide an easy API for parsing ics files according to the [rfc5545](https://www.rfc-editor.org/rfc/rfc5545) iCalendar specification.

## API
API | Description
--- | ---
int init_ical(struct ical_s *ical, FILE *instream); | Initialises a `ical_s` struct for use in the next API's.
int consume__next_icalprop(struct ical_s *ical, - char **key, char **value); | Given an initialised `ical_s` struct, read the `.ics` file and return the next property in a key-value pair. Line unfolding is handled here.
long consume__next_icalevent(struct ical_s *ical, struct VEVENT_s *event); | Given an initialised `ical_s` struct, read the `.ics` file and return the next event.
void free_VEVENT_s(struct VEVENT_s *event); | Cleanup method for `VEVENT_s` in order to avoid memory leaks.

## Build instructions
This program can be compiled with `build.sh`.

The shell script is in this format:
```bash
gcc -g\
  . . . main source\
  . . . libraries\
  -o c_ics
```