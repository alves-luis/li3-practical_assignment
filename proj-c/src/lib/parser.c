#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <string.h>
#include "parser.h"

xmlDocPtr parseS(char *filename) {
    xmlDocPtr doc; /* the resulting document tree */

	/*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", filename);
	  exit(-1);
    }

	/*
	 * Cleanup function for the XML library.
	 */
	xmlCleanupParser();

	/*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();

	return doc;
}

parseArray parseM(parseArray a, int N, char *filename[]) {
	int i;
	if (a) {
		for (i = 0; i < N; i++)
      g_ptr_array_insert(a,i,parseS(filename[i]));
	}
	return a;

}

char * getAttribute (char *attribute, xmlNodePtr node) {
  char * content;
  content = (char *) xmlGetProp(node,(const xmlChar *)attribute);
  return content;
}

char * getUserBio(xmlNodePtr node) {
  return getAttribute("AboutMe",node);
}

char * getUserName(xmlNodePtr node) {
  return getAttribute("DisplayName",node);
}

long getId(xmlNodePtr node) {
  char * result = getAttribute("Id",node);
  long id = -1;
  if (result) id = atol(result);
  xmlFree(result);
  return id;
}

int getUserRep(xmlNodePtr node) {
  char * result = getAttribute("Reputation",node);
  int rep = 0;
  if (result) rep = atoi(result);
  xmlFree(result);
  return rep;
}

int getPostType(xmlNodePtr node) {
  char * result = getAttribute("PostTypeId",node);
  int type = 0;
  if (result) type = atoi(result);
  xmlFree(result);
  return type;
}

long getPostParentId(xmlNodePtr node) {
  char * result = getAttribute("ParentId",node);
  long id = -1;
  if (result) id = atol(result);
  xmlFree(result);
  return id;
}

char * getPostTitle(xmlNodePtr node) {
  return getAttribute("Title",node);
}

DateTime getPostDate(xmlNodePtr node) {
  // 2017-12-03T01:59:53.370
  char * result = getAttribute("CreationDate",node);
  int year,month,day,hour,minute;
  double second;
  sscanf(result,"%d-%d-%dT%d:%d:%lf",&year,&month,&day,&hour,&minute,&second);
  DateTime date = date_time_create(year,month,day,hour,minute,second);
  xmlFree(result);
  return date;
}

long getPostCreatorId(xmlNodePtr node) {
  char * result = getAttribute("OwnerUserId",node);
  long id = -1;
  if (result) id = atol(result);
  xmlFree(result);
  return id;
}

int getPostScore(xmlNodePtr node) {
  char * result = getAttribute("Score",node);
  int score = 0;
  if (result) score = atoi(result);
  xmlFree(result);
  return score;
}

int getPostComments(xmlNodePtr node) {
  char * result = getAttribute("CommentCount",node);
  int comments = 0;
  if (result) comments = atoi(result);
  xmlFree(result);
  return comments;
}

int getPostFavoriteCount(xmlNodePtr node) {
  char * result = getAttribute("FavoriteCount",node);
  int favoritec = 0;
  if (result) favoritec = atoi(result);
  xmlFree(result);
  return favoritec;
}

LIST getPostTags (char* non_parsed) {
  int i = 0;
  int max_size = strlen(non_parsed);

  LIST list = linked_create();

  while (i < max_size) {
    char temp[max_size];
    sscanf(non_parsed + i, "<%[^>]", temp);
    char* tag = mystrdup(temp);
    list = linked_add(list, tag);
    i +=  strlen(tag) + 2;
  }

  xmlFree(non_parsed);
  return list;
}

char * getPostTag(xmlNodePtr node) {
  return getAttribute("Tags", node);
}

char * getTagName(xmlNodePtr node) {
  return getAttribute("TagName",node);
}
