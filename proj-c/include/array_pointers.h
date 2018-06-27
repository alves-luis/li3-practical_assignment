#ifndef __ARRAY_POINTERS_H__
#define __ARRAY_POINTERS_H__

/** \file array_pointers.h
  * Includes all the functions to manage an array of pointers;
*/

/**
  * Opaque data struct that represents an array of pointers
*/
typedef struct array_pointers * ARRAY_POINTERS;

#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

/**
	* Creates an Array of pointers
  * @param size Size of the array
	* @return Array of pointers allocated
*/
ARRAY_POINTERS aop_create(int size);

/**
	* Gets how many pointers that can be in the array
  * @param aop Array of pointers
	* @return Number of pointers that can be in the array
*/
int aop_getSize(ARRAY_POINTERS aop);

/**
	* Gets how many pointers there are in the array
  * @param aop Array of pointers
	* @return Number of pointers in the array
*/
int aop_getOccupied(ARRAY_POINTERS aop);

/**
	* Adds a pointer to the array if there's space
  * @param aop Array of pointers
  * @param pointer Pointer to be added
*/
void aop_addPointer(ARRAY_POINTERS aop, void * pointer);

/**
	* Gets the pointer at the index specified (if within boundaries)
  * @param aop Array of pointers
  * @param index Position of the pointer to be received
  * @return NULL if the index is out of boundaries, the pointer if not
*/
void* aop_getPointer(ARRAY_POINTERS aop, int index);

/**
	* Frees the memory allocated for the array of pointers
  * @param aop Array of pointers
*/
void aop_free(ARRAY_POINTERS aop);

#endif
