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

// Use default values for the enum
typedef enum {
  RED = 83,
  GREEN = 127,
  BLUE = 15,
} color_t;
