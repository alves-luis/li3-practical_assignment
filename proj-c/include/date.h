#ifndef __DATE_H__
#define __DATE_H__

/** \file date.h
  Has the definition of every function used to handle a Date
*/

/**
  * Opaque data struct of a date by the teacher
*/
typedef struct date* Date;

/**
	* Creates a Date
  * @param day Day of the date
  * @param month Month of the date
  * @param year Year of the date
	* @return Date
*/
Date createDate(int day, int month, int year);

/**
	* Gets the day in stored in the date
  * @param d Date from where we need the day
	* @return Day of the date
*/
int get_day(Date d);

/**
	* Gets the month in stored in the date
  * @param d Date from where we need the month
	* @return Month of the date
*/
int get_month(Date d); // must return a value between 0 and 11

/**
	* Gets the year in stored in the date
  * @param d Date from where we need the year
	* @return Year of the date
*/
int get_year(Date d);

/**
	* Frees the memory allocated to store the date
  * @param d Date to be freed
*/
void free_date(Date d);

#endif
