#include "load.h"

parseArray loadFiles(char * dump_path) {
  parseArray parsedFiles = g_ptr_array_sized_new(3);
  char * files[3];
  int length = strlen(dump_path) + strlen("Posts.xml") + 1;
  int i;

  for(i = 0; i < 3; i++) {
    files[i] = malloc(length);
    if (files[i])
      strcpy(files[i],dump_path);
  }
  strcat(files[0],"Tags.xml");
  strcat(files[1],"Posts.xml");
  strcat(files[2],"Users.xml");

  parsedFiles = parseM(parsedFiles,3,files);

  for(i = 0; i < 3; i++) {
    free(files[i]);
  }
  return parsedFiles;
}

xmlNodePtr setNodePointer(xmlDocPtr docpointer) {
  xmlNodePtr nodePointer = xmlDocGetRootElement(docpointer);
  nodePointer = nodePointer->xmlChildrenNode;
  return nodePointer;
}

void loadUser(TAD_community com, xmlNodePtr node) {
  LONG_USER u;
  char * bio;
  char * name; // placeholder for memory returned from xml who needs free

  bio = getUserBio(node);

  name = getUserName(node);
  u = long_user_create(bio,name,getId(node),getUserRep(node));
  xmlFree(bio); // cleans up memory once again
  xmlFree(name);
  // Inserts User into HashTable by Ids
  hash_insert(long_user_getId(u),u,tad_getUsersByHash(com));
  heap_insert(tad_getUsersByReputation(com),u);
}

TAD_community loadUsers(TAD_community com, xmlDocPtr users) {
  xmlNodePtr node = setNodePointer(users);

  while (node) {
    if (!xmlIsBlankNode(node))
      loadUser(com,node);
    node = node->next;
  }
  return com;
}

POST loadAnswer(TAD_community com, xmlNodePtr node) {
  POST parent = (POST) hash_get(getPostParentId(node),tad_getPostsByHash(com));
  POST p = post_create(1,parent);
  post_setDate(p,getPostDate(node));
  post_setNumComments(p,getPostComments(node));
  post_setScore(p,getPostScore(node));
  post_setNumComments(p,getPostComments(node));
  if (parent)
    post_addAnswer(parent,p);
  return p;
}

POST loadQuestion(xmlNodePtr node) {
  POST p = post_create(0,NULL);
  post_setDate(p,getPostDate(node));
  post_setTags(p,getPostTags(getPostTag(node)));
  return p;
}

void loadQuestionAndAnswer(TAD_community com, xmlNodePtr node, POST p) {
  LONG_USER u;
  char * temp; // to cleanup memory from libxml

  post_setId(p,getId(node));

  u = (LONG_USER) hash_get(getPostCreatorId(node),tad_getUsersByHash(com));
  post_setCreator(p,getPostCreatorId(node));

  temp = getPostTitle(node);
  post_setTitle(p,temp);
  xmlFree(temp);

  hash_insert(post_getId(p),p,tad_getPostsByHash(com));
  seq_insertPost(tad_getPostsBySequence(com), p);

  long_user_addNumberOfPosts(u,1);
  long_user_addPost(u,p);

}

void loadQuestionsAndAnswers(TAD_community com, xmlNodePtr nodePointer, int flag) {
  int type;
  POST p;
  while(nodePointer) {
    if (!xmlIsBlankNode(nodePointer)) {
      type = getPostType(nodePointer);
      if (type == 1 && flag == 1) {
        p = loadQuestion(nodePointer);
        loadQuestionAndAnswer(com,nodePointer,p);
      }
      if (type == 2 && flag == 2) {
        p = loadAnswer(com,nodePointer);
        loadQuestionAndAnswer(com,nodePointer,p);
      }
    }
    nodePointer = nodePointer->next;
  }
}


TAD_community loadPosts(TAD_community com, xmlDocPtr posts) {
  xmlNodePtr nodePointer = setNodePointer(posts);
  loadQuestionsAndAnswers(com,nodePointer,1);
  loadQuestionsAndAnswers(com,nodePointer,2);
  seq_sortPostNormal(tad_getPostsBySequence(com));
  return com;
}

void loadHeap(TAD_community com) {
  g_hash_table_foreach(tad_getUsersByHash(com),hash_toHeap,tad_getUsersByNumberOfPosts(com));
}

TAD_community loadTags(TAD_community com, xmlDocPtr tags) {
  xmlNodePtr nodePointer = setNodePointer(tags);
  char * tag;
  long * id;
  HASHTABLE h = tad_getTagsByHash(com);
  while (nodePointer) {
    if (!xmlIsBlankNode(nodePointer)) {
      id = malloc(sizeof(long));
      *id = getId(nodePointer);
      tag = getTagName(nodePointer);
      str_hash_insert(tag,id,h);
    }
    nodePointer = nodePointer->next;
  }
  return com;
}

TAD_community load(TAD_community com, char* dump_path) {
  parseArray parsedFiles = loadFiles(dump_path);
  xmlDocPtr tags = g_ptr_array_index(parsedFiles,0);
  xmlDocPtr posts = g_ptr_array_index(parsedFiles,1);
  xmlDocPtr users = g_ptr_array_index(parsedFiles,2);

  com = loadTags(com,tags);
  com = loadUsers(com,users);
  com = loadPosts(com,posts);
  loadHeap(com);
  xmlFreeDoc(tags);
  xmlFreeDoc(posts);
  xmlFreeDoc(users);
  g_ptr_array_free(parsedFiles,TRUE);
  return com;
}
