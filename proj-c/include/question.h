#ifndef __QUESTION__
#define __QUESTION__

/** \file question.h
  * Includes all the functions to manage a Question;
*/

#include "post.h"
#include "linked_list.h"
#include "common.h"
#include "sequence.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

/**
  * Opaque data structure of Question: is a pointer to the actual struct.
*/
typedef struct question * QUESTION;

/**
  * Allocs space for a new Question
  * Sets the LIST answers and tags to NULL;
  * @return A Question with memory alocated
*/
QUESTION question_create();

/**
  * Gets a list of Answers of a given Question
  * @param q Question
  * @return List of all the answers
*/
LIST question_getAnswers(QUESTION q);

/**
  * Gets a list of size N of Answers to a given Question
  * @param q Question
  * @param N Number of answers
  * @return List of N answers
*/
LIST question_getNAnswers(QUESTION q, int N);

/**
  * Gets an answer n N position of a question
  * @param q question
  * @param N position
  * @return p post
*/
POST question_getNAnswer(QUESTION q, int N);


/**
  * Gets the number of answers of a question
  * @param q question
  * @return N number of answers (-1 if null question)
*/
int question_getNumAnswers(QUESTION q);

/**
  * Gets a list of Tags of a given Question
  * @param q Question
  * @return List of all the Tags
*/
LIST question_getTags(QUESTION q);

/**
  * Adds a given post as an Answer to a question
  * @param q Question that will have the answer
  * @param a Post to be added as an Answer
*/
void question_addAnswer(QUESTION q, POST a);

/**
  * Adds the tags to a question
  * @param q Question that will hold the tags
  * @param l Tags to add to the question
*/
void question_setTags(QUESTION q, LIST l);

/**
  * Frees all the space allocated for a question
  * @param q Question to free up space.
*/
void question_free(QUESTION q);


#endif
