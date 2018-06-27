#ifndef __PARSER_H__
#define __PARSER_H__

/** \file parser.h
 * Includes all the functions to help parse the XML files
 */
#include <glib.h>
#include <libxml/tree.h>
#include "date_time.h"
#include "linked_list.h"

/**
	* parseArray is a pointer to a Glib GPtrArray
*/
typedef GPtrArray *parseArray;

/**
  * Parse a single filename through libxml (function is as suggested in)
  * libxml tutorial
  * @param filename Filename
  * @return docPointer of the parsed file
*/
xmlDocPtr parseS(char * filename);

/**
  * Parse multiple files into a pointer array
  * @param ar Array to store the parsed files
  * @param N Number of files
  * @param filename[N] Array of filenames
  * @return Pointer array with parsed files
 */
parseArray parseM(parseArray ar, int N, char * filename[N]);

/**
	* Returns a given attribute of a node. Its memory needs to be freed.
	* @param attribute Attribute that we want to retrieve
	* @param node Current node on the parsedDoc
	* @return String containing the value of the attribute
*/
char * getAttribute (char *attribute, xmlNodePtr node);

/**
	* Returns the AboutMe attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
char * getUserBio(xmlNodePtr node);

/**
	* Returns the DisplayName attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
char * getUserName(xmlNodePtr node);

/**
	* Returns the Id attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
long getId(xmlNodePtr node);

/**
	* Returns the Reputation attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
int getUserRep(xmlNodePtr node);

/**
	* Returns the PostTypeId attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
int getPostType(xmlNodePtr node);

/**
	* Returns the ParentId attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
long getPostParentId(xmlNodePtr node);

/**
	* Returns the Title attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
char * getPostTitle(xmlNodePtr node);

/**
	* Returns the CreationDate attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
DateTime getPostDate(xmlNodePtr node);

/**
	* Returns the OwnerUserId attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
long getPostCreatorId(xmlNodePtr node);

/**
	* Returns the Score attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
int getPostScore(xmlNodePtr node);

/**
	* Returns the CommentCount attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
int getPostComments(xmlNodePtr node);

/**
  * Returns the Favorite count attribute of a given node
  * @param node Current node
  * @return Content of the attribute
*/
int getPostFavoriteCount(xmlNodePtr node);

/**
	* Returns the Linked list containing the tags of a question
	* @param non_parsed Tag attribute
	* @return List of tags of a question
*/
LIST getPostTags (char* non_parsed);

/**
	* Returns the tag attribute of a given node
	* @param node Current node
	* @return Content of the attribute
*/
char * getPostTag(xmlNodePtr node);

/**
  * Returns the attribute TagName
  * @param node Current node
  * @return Content of the TagName
*/
char * getTagName(xmlNodePtr node);

#endif
