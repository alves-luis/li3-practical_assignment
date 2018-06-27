#ifndef __LOAD_H__
#define __LOAD_H__
/** \file load.h
 * Includes all the functions to load xmlParsedFiles into our TAD_community
 */

#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <glib.h>
#include "interface.h"

/**
	* Loads all the files from a given dump_path into a parseArray
	* @param dump_path
	* @return An array containing the parsed files through LibXML
*/
parseArray loadFiles(char * dump_path);

/**
	* Moves a bunch of pointers of libxml. Gets it all ready for use in loadFuncs
	* Honestly, it's kinda Witchcraft.
	* @param docpointer
	* @return nodePointer
*/
xmlNodePtr setNodePointer(xmlDocPtr docpointer);

/**
	* Routine that is used to get user info from xmlParsed file
	* @param com Community to insert the data
	* @param node Current node
*/
void loadUser(TAD_community com, xmlNodePtr node);

/**
	* Loads all the users into their proper structures inside TAD_community
	* @param com Community to insert the users
	* @param users Docpointer to the users parsed though libxml
	* @return All Users into their structures inside TAD_community
*/
TAD_community loadUsers(TAD_community com, xmlDocPtr users);

/**
	* Loads all the things related to a Post of type Answer inside TAD_community
	* @param com Community to insert Answers
	* @param node NodePointer that points to the current answer
	* @return Post to be added to other structures
*/
POST loadAnswer(TAD_community com, xmlNodePtr node);

/**
	* Loads all the things related to a Post of type Question inside TAD_community
	* @param node Current node
	* @return Post with all the question related things set.
*/
POST loadQuestion(xmlNodePtr node);

/**
	* Loads all the things related to a Post that are common to a Question and an
	* Answer inside TAD_community
	* @param com Community to load those things
	* @param node Current  node
	* @param p Post to load all the stuff to
*/
void loadQuestionAndAnswer(TAD_community com, xmlNodePtr node, POST p);

/**
  * Loads all the questions or answers, depending on the flag
  * 1 if question, 2 if answer
  * @param com Community to load
  * @param nodePointer Start of the parsed file
  * @param flag Flag
*/
void loadQuestionsAndAnswers(TAD_community com, xmlNodePtr nodePointer, int flag);

/**
	* Loads all the Posts into their proper structures inside TAD_community
	* @param com Community to insert the posts
	* @param posts Docpointer to the posts parsed though libxml
	* @return All Posts into their structures inside TAD_community
*/
TAD_community loadPosts(TAD_community com, xmlDocPtr posts);

#endif
