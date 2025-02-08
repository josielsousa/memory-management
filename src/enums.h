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

typedef enum {
  STATUS_OK = 200,
  STATUS_BAD_REQUEST = 400,
  STATUS_FORBIDDEN = 403,
  STATUS_NOT_FOUND = 404,
  STATUS_INTERNAL_SERVER_ERROR = 500,
} http_status_t;

char *http_to_str(http_status_t status);
