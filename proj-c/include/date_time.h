#ifndef __DATE_TIME_H__
#define __DATE_TIME_H__

/** \file date_time.h
  * Includes all the functions to manage a DateTime date;
*/

/**
  * DateTime is a pointer to a Glib implementation GDateTime
*/
typedef struct GDateTime* DateTime;

#include "date.h"
#include <stdio.h>
#include <glib.h>

/**
	* Creates a DateTime
  * @param year Year of the date
  * @param month Month of the date
  * @param day Day of the date
  * @param hour Hour of the date
  * @param minute Minute of the date
  * @param seconds Seconds of the date (in the format XX.XXX, to the miliseconds)
	* @return DateTime created
*/
DateTime date_time_create(int year, int month, int day, int hour, int minute, double seconds);

/**
	* Converts a date in the format DateTime to the format Date (losing the information of the time)
  * @param d DateTime to be converted
	* @return DateTime
*/
Date date_time_to_date (DateTime d);

/**
	* Converts a date in the format Date to the format DateTime (the time is set to 00:00:00.000)
  * @param d Date to be converted
	* @return DateTime
*/
DateTime date_to_date_time (Date d);

/**
	* Compares two DateTime dates
  * @param d1 First DateTime to be compared
  * @param d2 Second DateTime to be compared
	* @return -1 if the first date preceeds the second, 0 if they're the same, 1 if the second preceeds the first
*/
int date_time_compare (DateTime d1, DateTime d2);

/**
	* Adds a day to a certain DateTime
  * @param d1 DateTime to which a day will be added
	* @return DateTime a day later
*/
DateTime date_time_inc (DateTime d1);

/**
	* Frees the memory used by the Datetime
  * @param d DateTime to be freed
*/
void date_time_free (DateTime d);

/**
	* Converts a DateTime to a string
  * @param d DateTime to become a string
  * @param pStr Pointer to where the string will be stored
*/
void date_time_to_string(DateTime d, char* pStr);

/**
	* Prints the DateTime
  * @param d DateTime to be printed
*/
void date_time_print(DateTime d);

#endif
