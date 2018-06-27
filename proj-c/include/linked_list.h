#ifndef __LINKED_H__
#define __LINKED_H__

/** \file linked_list.h
 * Includes all the functions to manage a Linked List
 */

#include <glib.h>
#include "list.h"
#include "pair.h"
#include "post.h"
#include "common.h"
#include "array_pointers.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Creates a new empty linked list
 * @return LIST
*/
LIST linked_create();

/**
 * Adds an element to the head of the linked list
 * @param l List where the element will be added
 * @param content Element to be added
 * @return New pointer to the beggining of the linked list
*/
LIST linked_add (LIST l, void* content);

/**
 * Auxiliary function to print a list of tags
 * @param tag Tag to be printed
*/
void print_tag (char* tag);

/**
 * Prints the list of tags in a post
 * @param l List of tags to be printed
*/
void print_list_tags(LIST l);

/**
 * Inserts a list of tags to a hash that counts how many times each is used
 * @param l List of tags to be added
 * @param aop Array of Pointers containing the hash where we'll insert (along with other data)
*/
void linked_insert_tags_hash(LIST l, ARRAY_POINTERS aop);

/**
 * Auxiliary to the linked_insert_tags_hash. Inserts each tag into an Hash
 * @param str Tag to be added
 * @param aop Array of Pointers containing the hash where we'll insert (along with other data)
*/
void tag_to_long_to_hash (char* str, ARRAY_POINTERS aop);

/**
 * Adds each id of the hash into the list of longs sorted by the number of times each tag was used
 * @param ids Linked list containing each id
 * @param count HashTable with each tag counted by the number of times used
 * @param l Long list where we'll maybe insert each tag
*/
void linked_foreachIdInsert(LIST ids, HASHTABLE count, LONG_list l);

#endif
