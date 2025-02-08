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
