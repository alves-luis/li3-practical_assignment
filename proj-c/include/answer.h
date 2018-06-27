#ifndef __ANSWER__
#define __ANSWER__
/** \file answer.h
 * Includes all the function definitions to manage answers of a question
 */

#include <stdlib.h>
#include <stdio.h>
#include "date_time.h"
#include "post.h"

/**
	* ANSWER is a pointer to an opaque struct answer
*/
typedef struct answer * ANSWER;

/** Creates an answer, given a Question as a parent.
 * This is used when creating a Post (see post.h)
 * @param parent Question the answer answers (very funny)
 * @return ANSWER allocated memory for the answer
*/
ANSWER answer_create(POST parent);

/** Gets the current score of an answer
 * @param a Answer from whom we want to retrieve the info
 * @return s score or -1 if NULL answer
*/
int answer_getScore(ANSWER a);

/** Sets the score of an answer
 * @param a Answer to set the info
 * @param ns NewScore
*/
void answer_setScore(ANSWER a, int ns);

/** Gets the current number of Comments of an Answer
 * @param a Answer from whom we want to retrieve the info
 * @return n number of comments, or -1 if NULL Answer
*/
int answer_getNumComments(ANSWER a);

/** Sets the number of comments of an Answer
 * @param a Answer to set the info
 * @param nc New number of comments
*/
void answer_setNumComments(ANSWER a, int nc);

/** Gives the pointer to the Post that represents the question this answer
 * is answering. Yeah, nice grammar mate.
 * @param a Answer from whom we want to retrieve the info
 * @return q Post (question answered) (can be NULL)
*/
POST answer_getParent(ANSWER a);

/** Sets the pointer to the Post that representes the question this answer..
 * (you know the rest...)
 * @param a Answer to change the info
 * @param p Post that represents the question
*/
void answer_setParent(ANSWER a, POST p);

/** Gets the Id of the Question this Answer answers.
 * @param a Answer from whom we want to retrieve the info
 * @return id Id of the question (-1 if NULL Answer or Community owned)
*/
long answer_getParentId(ANSWER a);

/** Frees the memory alocated for an Answer
 * @param a Answer to free the memory
*/
void answer_free(ANSWER a);

/** Gets the post from an answer
 * @param a Answer from where to get the post
 * @return Post
*/
POST answer_getPost(ANSWER a);

#endif
