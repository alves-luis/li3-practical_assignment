#ifndef __POST__
#define __POST__

/** \file post.h
  * Includes all the functions to manage a Post;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "question.h"
#include "answer.h"
#include "date_time.h"
#include "long_user.h"


/**
  * Opaque data structure that representes a Post
*/
typedef struct post * POST;

/**
	* Creates a post, given a type (Question or Answer)
	* @param type (0 if question, !=0, if answer)
	* @param question Pointer to the question(if it's an answer, pass NULL)
	* @return Post with allocated memory
*/
POST post_create(int type, void * question);

/**
	* Frees the space allocated for a Post
	* @param p Post to free its memory
*/
void post_free(POST p);

/**
	* Returns the Id of a given Post
	* @param p Post
	* @return Id (0 if invalid post)
*/
long post_getId(POST p);

/**
	* Returns the Id of the User who created the Post
	* @param p Post
	* @return CreatorId
*/
long post_getCreatorId(POST p);

/**
	* Returns the title of a given Post (can be NULL)
	* @param p post
	* @return Title
*/
char * post_getTitle(POST p);

/**
	* Returns the creation date of a given Post
	* @param p Post
	* @return Date
*/
DateTime post_getDate(POST p);

/**
	* Returns the type of a Post.
	* 0 if question, !0 if answer;
	* @param p Post
	* @return Type
*/
int post_getType(POST p);

/**
	* Sets the Id of a Post
	* @param p Post
	* @param id New Id
*/
void post_setId(POST p, long id);

/**
	* Sets the creator of a Post
	* @param p Post
	* @param id Creator
*/
void post_setCreator(POST p, long id);

/**
	* Sets the title of a Post
	* @param p Post
	* @param newtitle NewTitle
*/
void post_setTitle(POST p, char * newtitle);

/**
	* Sets the date of a Post
	* @param p Post
	* @param d newDate
*/
void post_setDate(POST p, DateTime d);

/**
	* Sets the type of a Post (Question or Answer)
	* 0 if question, !0 if answer;
	* @param p Post
	* @param nt New Type
*/
void post_setType(POST p, int nt);

/**
	* Adds an answer to a Post of type (question)
	* @param p Post
	* @param a Answer to add to Post
*/
void post_addAnswer(POST p, POST a);

/**
	* Gets the Parent of a given Post (Answer)
	* @param p Post
	* @return Parent (Question), or NULL, if it fails
*/
POST post_getParent(POST p);

/**
  * Gets the Id of a parent of a post (answer)
  * @param p Post
  * @return -1 if no parent, or the id of the parent.
*/
long post_getParentId(POST p);

/**
	* Gets the score of a given Answer
	* @param p Post (of type Answer)
	* @return score, or -1, if invalid request
*/
int post_getScore(POST p);

/**
	* Sets the score of a given Answer
	* @param p Post (of type Answer)
	* @param nscore New score
*/
void post_setScore(POST p, int nscore);

/**
	* Gets the number of comments of a given Answer
	* @param p Post
	* @return Number of comments (-1 if invalid request)
*/
int post_getNumComments(POST p);

/**
	* Sets the number of comments of a given Answer
	* @param p Post
	* @param ncom New number of comments
*/
void post_setNumComments(POST p, int ncom);

/**
	* Gets the voteCount of a given Answer
	* @param p Post
	* @return voteCount (or -1, if invalid request)
*/
int post_getVoteCount(POST p);

/**
	* Retrieves the number of answers of a given question
	* @param p Post
	* @return Number of Answers (-1 if invalid);
*/
int post_getNumAnswers(POST p);

/**
  * Retrieves the N answer of a question
  * @param p Post
  * @param N Position of the answer in the list
*/
POST post_getNAnswer(POST p, int N);

/**
  * Gets the tags of a given Post
  * @param p Post
  * @return List of Tags (NULL if invalid);
*/
LIST post_getTags(POST p);

/**
  * Checks if a post got a certain tag
  * @param p Post
  * @param tag Tag we want to check
  * @return 1 if it does, 0 if not
*/
int post_check_tag(POST p, char* tag);

/**
	* Sets tags to a Post
	* @param p Post
	* @param tags Tags to be added
*/
void post_setTags (POST p, LIST tags);

/**
	* Compares two posts by Date (see date_time_compare)
	* @param a Post
	* @param b Post
	* @return date_time_compare(b,a)
*/
int postCompare(POST a, POST b);

/**
	* Compares two posts by Date (see date_time_compare)
	* @param a Post
	* @param b Post
	* @return date_time_compare(a,b)
*/
int post_compare(POST a, POST b);

/**
	* Adds the type of post to the pair
	* @param p Post
	* @param lp LONG_pair
*/
void countQA (POST p, LONG_pair lp);

/**
	* Says if a post is between 2 dates
	* @param p Post
	* @param begin DateTime
  * @param end DateTime
	* @return 0 if doesn't, !0 if it does
*/
int post_betweenDates(POST p, DateTime begin, DateTime end);

/**
	* Just a fun function to print how much space a Post uses.
	* @param p Post
*/
void post_printSize(POST p);

/**
	* Prints a post.
	* @param p Post
*/
void post_print(POST p);

#endif
