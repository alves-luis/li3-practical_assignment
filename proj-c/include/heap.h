#ifndef __HEAP__
#define __HEAP__
/** \file heap.h
 * Includes all the function definitions to build a heap based on number of posts
 */

#include <stdlib.h>
#include <stdio.h>
#include "long_user.h"

/**
  * Defines Parent index in heap
*/
#define PARENT(i) (i-1)/2

/**
  * Defines Left child index in heap
*/
#define LEFT(i) 2*i + 1

/**
  * Defines Right child index in heap
*/
#define RIGHT(i) 2*i + 2

/**
	* HEAP is a pointer to an opaque data struct called struct heap.
*/
typedef struct heap * HEAP;

/** Creates a new heap of given size
 * @param size Heap size
 * @param valueFunction Function that retrieves the value to order the maxHeap
 * @return Allocated heap (NULL if could not allocate)
*/
HEAP heap_new(int size, int (*valueFunction)(LONG_USER u));

/** Inserts a LONG_USER into the heap
 * @param h Heap to insert
 * @param u LONG_USER to insert
 * @return int of Success (0 if could insert, -1 if could not)
*/
int heap_insert(HEAP h, LONG_USER u);

/** Removes a LONG_USER from the heap
 * @param h Heap to remove a user
 * @return LONG_USER removed (can be NULL, if HEAP empty or NULL Heap)
*/
LONG_USER heap_remove(HEAP h);

/** Swaps elements in a heap
 * @param h Heap to swap
 * @param a
 * @param b
*/
void swap(HEAP h, int a, int b);

/** Bubbles an element up in the heap into its place
 * @param h Heap to bubbleUp
 * @param i Elem to bubbleUp
*/
void heap_bubbleUp(HEAP h, int i);

/** Bubbles an element down in the heap into its place
 * @param h Heap to bubbleDown
 * @param a Elem to bubbleDown
*/
void heap_bubbleDown(HEAP h, int a);

/** Returns the number of elements in the heap
 * @param h Heap
 * @return Number of elements in the heap (-1 if NULL Heap)
*/
int heap_getUsed(HEAP h);

/** Returns the max size of the heap
 * @param h Heap
 * @return Max size of the heap (-1 if NULL Heap)
*/
int heap_getSize(HEAP h);

/** Frees up the memory used by the heap
 * @param h Heap
*/
void heap_free(HEAP h);

/**
  * Clones a heap
  * @param h Original Heap
  * @return Cloned heap
*/
HEAP heap_clone(HEAP h);

#endif
