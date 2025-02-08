#pragma once

typedef enum DayOfWeek {
  SUNDAY = 1,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
} day_of_week_t;

typedef struct Event {
  char *name;
  day_of_week_t day;
} event_t;

// Use custom default values for the enum
typedef enum {
  RED = 83,
  GREEN = 127,
  BLUE = 15,
} color_t;

// Size of the enum - in C are the same size as an integer. However, if an enum
// value exceeds the range of an integer, it will be the size of a larger
// integer type, such as an unsigned int or long.
//
// - `unsigned int` - doesn't represent negative numbers, so it can represent
// larger positive numbers (
//          4,294,967,295 32-bit and
//          18,446,744,073,709,551,615 64-bit,
// )
// all of ranges negative numbers can be used to represent positive numbers
// - `long` - can represent larger numbers than `unsigned int`
// (9,223,372,036,854,775,807 64-bit)
typedef enum {
  STATUS_OK = 200,
  STATUS_BAD_REQUEST = 400,
  STATUS_FORBIDDEN = 403,
  STATUS_NOT_FOUND = 404,
  STATUS_INTERNAL_SERVER_ERROR = 500,
} http_status_t;

char *http_to_str(http_status_t status);
