#include "date_time.h"

DateTime date_time_create(int year, int month, int day, int hour, int minute, double seconds) {
  DateTime date = (DateTime) g_date_time_new_utc(year, month, day, hour, minute, seconds);
  return date;
}

DateTime date_to_date_time (Date d) {
  DateTime date = (DateTime) date_time_create (get_year(d), get_month(d), get_day(d), 0, 0, 0);
  return date;
}

Date date_time_to_date (DateTime d) {
  Date date = createDate (g_date_time_get_year((GDateTime*) d),
                          g_date_time_get_month((GDateTime*) d),
                          g_date_time_get_day_of_month((GDateTime*) d));
  return date;
}

DateTime date_time_inc (DateTime d1) {
  return (DateTime) g_date_time_add_days((GDateTime*) d1, 1);
}

int date_time_compare (DateTime d1, DateTime d2) {
  return g_date_time_compare((GDateTime*) d1,(GDateTime*) d2);
}

void date_time_free (DateTime d) {
  g_date_time_unref((GDateTime*) d);
}


void date_time_to_string(DateTime d, char* pStr) {
  sprintf(pStr, "%d/%d/%d - %d:%d:%f",
  g_date_time_get_day_of_month((GDateTime*) d), g_date_time_get_month((GDateTime*) d),
  g_date_time_get_year((GDateTime*) d), g_date_time_get_hour((GDateTime*) d),
  g_date_time_get_minute((GDateTime*) d), g_date_time_get_seconds((GDateTime*) d));
}

void date_time_print(DateTime d) {
  char str[100];
  date_time_to_string(d, str);
  printf("Date: %s\n", str);
}
