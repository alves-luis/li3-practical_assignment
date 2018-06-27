#ifndef __LONG_LIST__
#define __LONG_LIST__

typedef struct llist * LONG_list;

#include "common.h"
#include "post.h"
#include "array_pointers.h"

/**
  * LIST is an actual pointer to a GSList implementation from GLib.
*/

/**
	* Creates a list of longs
  * @param size Size of the linked list
	* @return List of longs
*/
LONG_list create_list(int size);

/**
	* Gets the long at an index
  * @param l List of longs
  * @param index Index from where we take the long
	* @return Long value of the list at position specified
*/
long get_list(LONG_list l, int index);

/**
	* Gets the size of the list
  * @param l List of longs
  * @return Number of longs the list can have
*/
int get_size(LONG_list l);

/**
	* Gets the number of elements in the list
  * @param l List of longs
  * @return Number of longs in the list
*/
int get_occupied(LONG_list l);

/**
	* Increments the number of occupied in the list
  * @param l List of longs
*/
void inc_occupied (LONG_list l);

/**
	* Put a long at a certain index in the list of longs
  * @param l List of longs
  * @param index Position where we want to insert
  * @param value Long we wish to insert
*/
void set_list(LONG_list l, int index, long value);

/**
	* Adds a long to the end of the list (if list is full, it doubles its size and inserts)
  * @param l List of longs
  * @param value Long we wish to insert
*/
void add_list(LONG_list l, long value);

/**
	* Frees the memory allocated not being used (to be used when finished inserting dynamically to the list)
  * @param l List of longs
*/
void free_unused_mem(LONG_list l);

/**
	* Frees all the memory allocated by the list of longs
  * @param l List of longs
*/
void free_list(LONG_list l);

/**
	* Prints the list of longs
  * @param l List of longs
*/
void print_list(LONG_list l);

/**
	* Reverses the list
  * @param l List of longs
*/
void reverse_list(LONG_list l);

/**
	* Checks if a long is in the list of longs
  * @param l List of longs
  * @param elem Value to check
  * @return 0 if value not found, 1 if found
*/
int elem_list(LONG_list l, long elem);

/**
	* Inserts the id of a post in a list of longs sorted decreasingly by the number of votes
  * @param p Post where the Id will come from
  * @param aop Array of pointers containing the list of longs where we insert and other data
*/
void insert_postSortedByVotes (POST p, ARRAY_POINTERS aop);

/**
	* Inserts the id of a post in a list of longs sorted decreasingly by the number of answers a question has
  * @param p Post where the Id will come from
  * @param aop Array of pointers containing the list of longs where we insert and other data
*/
void insert_postSortedByNumAnswers (POST p, ARRAY_POINTERS aop);

/**
	* Inserts the id of a tag in a list of longs sorted decreasingly by the number of times the tag was used
  * @param id_pointer Pointer to the id of the tag
  * @param aop Array of pointers containing the list of longs where we insert and other data
*/
void insert_idSortedByCount (long* id_pointer, ARRAY_POINTERS aop);

#endif
