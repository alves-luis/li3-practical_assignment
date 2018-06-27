#ifndef __HASH__
#define __HASH__

/** \file hash.h
 * Includes all the functions to manage HashTables
 */

#include <stdio.h>
#include <glib.h>
#include "heap.h"
#include "long_user.h"

/**
	* HASHTABLE is a pointer to a GHashTable, implementation from GLib
*/
typedef GHashTable *HASHTABLE;

/**
 * Creates new HASHTABLE based on IDs.
 * @param func GDestroyNotify func (function to destroy values)
 * @param type (0 if long key, !0 if string key)
 * @return HASHTABLE
*/
HASHTABLE hash_new(GDestroyNotify func, int type);

/**
 * Inserts a new Question/Answer/User in a HastTable (by ID)
 * @param key Id
 * @param value Pointer to Question/Answer/User
 * @param h HashTable to insert
 * @return Boolean (if could insert or not)
*/
int hash_insert(long key, void * value, HASHTABLE h);

/**
  * Inserts a new Tag in a HashTable
  * @param key Tag
  * @param value Id of the Tag
  * @param h Hashtable
  * @return Boolean (if could insert or not)
*/
int str_hash_insert(char * key, long * value, HASHTABLE h);
/**
 * Gets a Question/Answer/User (given an ID) from the HashTable
 * @param id Id of the Question/Answer/User
 * @param h Hashtable to retrieve the post from
 * @return Question/Answer/User
 */
void * hash_get(long id, HASHTABLE h);

/**
  * Gets the id of a tag from the char * of the tag
  * @param key Tag
  * @param h Hash of Tags
  * @¶eturn result of lookup
*/
long * str_hash_get(char * key, HASHTABLE h);

/**
  * Function to iterate over all the elements on the Hash
  * Is used when Hash is of type LONG_USERs
  * Used in g_hash_table_foreach
  * @param key of Hash
  * @param value LONG_USER
  * @param user_data Heap
*/
void hash_toHeap(gpointer key, gpointer value, gpointer user_data);

/**
 * Frees up a HashTable
 * @param h Hashtable
*/
void hash_freeTable(HASHTABLE h);

/**
  * Executes func f with extra data on all the elements of a hashtable
  * @param h Hashtable
  * @param func Function(3 args void*)
  * @param data Extra data to pass to f
*/
void hash_forEach(HASHTABLE h, void * func, void * data);

/**
  * Compares the two glong values being pointed to
  * and returns TRUE if they are equal.
  * @param v1 Pointer to glong
  * @param v2 Pointer to glong
  * @return GBoolean
*/
gboolean g_long_equal (gconstpointer v1, gconstpointer v2);

/**
  * Converts a pointer to a glong to a hash value.
  * @param v Pointer to glong
  * @return GLong (hashed)
*/
glong g_long_hash (gconstpointer v);

/**
  * Increments the value stored in the hash with the corresponding key
  * @param h Hashtable where the data is stored
  * @param key Key to the value we want to add one to
*/
void hash_increment(HASHTABLE h, long key);

/**
  * Gets a linked list of all the keys used in the Hash (to free that list use hash_freeKeysList)
  * @param h Hashtable where the data is stored
  * @return The list containing all the keys
*/
LIST hash_getKeys(HASHTABLE h);

/**
  * Frees the list returned by hash_getKeys
  * @param l List returned by hash_getKeys
*/
void hash_freeKeysList (LIST l);

#endif
