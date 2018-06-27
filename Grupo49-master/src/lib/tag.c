#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "tag.h"


struct tag {
    char* tag_name;
    long  id;
    int   count;
};

TAG create_tag(unsigned char* tag_name, unsigned char* id, unsigned char* count) {
  TAG t = malloc(sizeof(struct tag));

  t->tag_name  = mystrdup((const char*) tag_name);
  if (id)    t->id = atol((const char*) id);
  if (count) t->count = atoi((const char*) count);

  return t;
}

long* get_tag_id_pointer(TAG t) {
  return (&t->id);
}

char* get_tag_name(TAG t ){
  return (t->tag_name);
}

long get_tag_id(TAG t){
  return (t->id);
}

int get_tag_count(TAG t){
  return(t->count);
}


void free_tags(void* rip) {
  TAG t = (TAG) rip;

  if (t) {
    free(t->tag_name);
    free(t);
  }
}

TAG create_incomplete_tag(char* tag,long id){
  TAG t = malloc(sizeof(tag));
  t->tag_name = mystrdup(tag);
  t->id = id;
  t->count = 1;
  return t;
}

void increment_tag (TAG t){
  t->count += 1;
}

struct top_tag{
  int size;
  SIMPLE_LIST list;
};

TOP_TAG create_top_tag(int size, SIMPLE_LIST list){
    TOP_TAG t = malloc(sizeof(struct top_tag));
    t -> size = size;
    t -> list = list;
    return t;
}

int get_top_tag_size(TOP_TAG t){
  return t->size;
}

SIMPLE_LIST get_top_tag_list(TOP_TAG t){
   return t->list;
}


void set_top_tag_list(TOP_TAG t, SIMPLE_LIST list){
    t->list = list;
}
