#ifndef __LONG_USER__
#define __LONG_USER__

/** \file long_user.h
 * Includes all the functions to manage a LONG_USER
 */

#include <stdlib.h>
#include <stdio.h>
#include "sequence.h"
#include "common.h"
#include "post.h"

/**
	* Opaque data struct that points to a long_user
*/
typedef struct long_user* LONG_USER;

/**
 * Creates a new Long_User
 * @param bio Description
 * @param name Username
 * @param id userID
 * @param rep reputation
 * @return LONG_USER
 */
LONG_USER long_user_create(char * bio, char * name, long id, int rep);

/**
  * Getter for the bio of a user
  * @param u User to retrieve the bio
  * @return bio
*/
char * long_user_getBio(LONG_USER u);

/**
 * Getter for the username
 * @param u Long_user
 * @return Username (NULl, if invalid user)
 */
char * long_user_getName(LONG_USER u);

/**
 * Getter for the user ID
 * @param u Long_user
 * @return ID (as int) (can be -1, if invalid user)
*/
long long_user_getId(LONG_USER u);

/**
 * Getter for the numberOfPosts from a user
 * @param u Long_user
 * @return number of posts (-1, if invalid user)
*/
int long_user_getNumberOfPosts(LONG_USER u);

/**
 * Getter for the reputation of a user
 * @param u long_user
 * @return reputation (-1, if invalid user)
*/
int long_user_getReputation(LONG_USER u);

/**
 * Setter for the userName
 * @param u Long_user
 * @param name New username
*/
void long_user_setName(LONG_USER u, char * name);

/**
  * Setter for the user bio
  * @param u Long_user
  * @param bio Bio of the user
*/
void long_user_setBio(LONG_USER u, char * bio);

/**
 * Setter for the userID
 * @param u Long_user
 * @param id New User ID
*/
void long_user_setId(LONG_USER u, long id);

/**
 * Setter for the user numberofposts
 * @param u Long_user
 * @param num New number of posts
*/
void long_user_setNumberOfPosts(LONG_USER u, int num);

/**
  * Setter for the user reputation
  * @param u long_user
  * @param rep new reputation
*/
void long_user_setReputation(LONG_USER u,int rep);

/**
  * Adds (or subtracts) a given number to count of posts
  * @param u long_user
  * @param num sum to add
*/
void long_user_addNumberOfPosts(LONG_USER u, int num);

/**
  * Adds a post to a user
  * @param u long_user
  * @param post post
*/
void long_user_addPost(LONG_USER u, void * post);

/**
  * Returns the pointer to all the posts of a User
  * @param u User
  * @return Sequence
*/
SEQUENCE long_user_getPosts(LONG_USER u);

/**
  * Returns a pointer to the ids of the last 10 posts
  * of a user
  * @param u Long_user
  * @return List of ids
*/
long * long_user_get10LastPosts(LONG_USER u);

/**
 * Frees up memory alocated for the LONG_USER
 * @param u Long_user
*/
void long_user_free(LONG_USER u);

/**
  * Prints the size of a long_user
  * @param p Long_user
*/
void long_user_printSize(LONG_USER p);

#endif
