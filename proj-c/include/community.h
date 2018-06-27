#ifndef __COMMUNITY__
#define __COMMUNITY__
/** \file community.h
  * Includes all the function definitions related to
  * the implementation of a TCD_community
*/

/**
  * Defines initial heap size
*/
#define INITIAL_HEAP_SIZE 1000

#include "interface.h"

/**
  * Allocs all the space for a TAD_community
  * @return TAD_community (NULL, if no memory available)
*/
TAD_community community_init();

/**
  * Returns a HashTable with all the Users by ID
  * @param com TAD_community
  * @return Hashtable with the users
*/
HASHTABLE tad_getUsersByHash(TAD_community com);

/**
  * Returns a Heap with all the Users by number of Posts
  * @param com TAD_community
  * @return Heap with the users by NumberOfPosts
*/
HEAP tad_getUsersByNumberOfPosts(TAD_community com);

/**
  * Returns a Heap with all the Users by Reputation
  * @param com TAD_community
  * @return Heap with the users by Reputation
*/
HEAP tad_getUsersByReputation(TAD_community com);

/**
  * Returns a HashTable with all the Posts by ID
  * @param com TAD_community
  * @return HashTable with the Posts
*/
HASHTABLE tad_getPostsByHash(TAD_community com);

/**
  * Returns a HashTable of Tags by char *
  * @param com TAD_community
  * @return HashTable with Tags
*/
HASHTABLE tad_getTagsByHash(TAD_community com);

/**
  * Returns a Sequence of posts sorted by date
  * @param com TAD_community
  * @return Sequence with the Posts
*/
SEQUENCE tad_getPostsBySequence(TAD_community com);
#endif
