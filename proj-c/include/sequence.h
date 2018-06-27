#ifndef __SEQUENCE__
#define __SEQUENCE__

/** \file sequence.h
  * Includes all the functions to manage a Sequence;
*/

#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "date_time.h"
#include "post.h"
#include "pair.h"
#include "list.h"


/**
  * Opaque data structure of a SEQUENCE: it's actually a GSequence implementation
*/
typedef GSequence * SEQUENCE;

/**
	* Creates a Sequence
	* @return Sequence with allocated memory
*/
SEQUENCE seq_create();

/**
	* Frees the memory used by the Sequence
	* @param s Sequence with allocated memory to be freed
*/
void seq_free(SEQUENCE s);

/**
	* Inserts a POST at the beggining of the sequence
	* @param s Sequence where the post will be inserted
  * @param p Post to be inserted
*/
void seq_insertPost(SEQUENCE s, POST p);

/**
	* Inserts a POST at the end of the sequence
  * @param p Post to be inserted
  * @param s Sequence where the post will be inserted
*/
void seq_insertPostEnd(POST p, SEQUENCE s);

/**
	* Gets how many elements there are in a sequence
  * @param s Sequence which need the size of
*/
int seq_getSize(SEQUENCE s);

/**
	* Sorts the Sequence using inverse chronology
  * @param s Sequence to be sorted
*/
void seq_sortPost(SEQUENCE s);

/**
	* Sorts the Sequence using regular chronology
  * @param s Sequence to be sorted
*/
void seq_sortPostNormal(SEQUENCE s);

/**
	* Sorts the Sequence decreasingly by the number of votes each question has
  * @param s Sequence to be sorted
*/
void seq_sortAnswer(SEQUENCE s);

/**
	* Checks if a post is in a sequence
  * @param s Sequence where the elements are stored
  * @param p Pointer to the post
  * @return NULL if not found, pointer to post in sequence if found
*/
void * seq_elem(SEQUENCE s,void * p);

/**
	* Gets the first N posts in the sorted sequence
  * @param s Sequence where the elements are stored
  * @param N Number of elements
  * @return Array of longs containing the first N Id's of the posts
*/
long * seq_getNFirstPost(SEQUENCE s, int N);

/**
	* Gets the first N posts in the sorted sequence to a LONG_list
  * @param s Sequence where the elements are stored
  * @param N Number of elements
  * @return LONG_list containing the id's of the posts
*/
LONG_list seq_toList (SEQUENCE s, int N);

/**
	* Applies a function to every element of the sequence (sorted by dates) in between two dates
  * @param s Sequence where the elements are stored
  * @param d1 Oldest date (in the format DateTime)
  * @param d2 Most recent date (in the format DateTime)
  * @param func Function to be applied to each element
  * @param data Data to be passed along with each element to the function received as parameter
*/
void seq_inBetweenDates(SEQUENCE s, DateTime d1, DateTime d2, GFunc func, void* data);

#endif
