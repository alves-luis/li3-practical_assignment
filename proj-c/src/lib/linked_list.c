#include "linked_list.h"

LIST linked_create() {
  LIST l = NULL;
  return l;
}

LIST linked_add (LIST l, void* content) {
  return g_slist_prepend(l, content);
}

// TAGS
void linked_free_tags (LIST tags) {
  g_slist_free_full(tags, free);
}

void print_tag (char* tag) {
  printf("%s; ", tag);
}

void print_list_tags(LIST l) {
  g_slist_foreach(l, (GFunc) print_tag, NULL);
  printf("\n");
}

//Query 11

void linked_insert_tags_hash(LIST l, ARRAY_POINTERS aop) {
  g_slist_foreach(l, (GFunc) tag_to_long_to_hash, aop);
}

void tag_to_long_to_hash (char* str, ARRAY_POINTERS aop) {
  long* temp = str_hash_get(str, aop_getPointer(aop,1));
  long id = (long) * temp;
  hash_increment(aop_getPointer(aop,0), id);
}

void linked_foreachIdInsert(LIST ids, HASHTABLE count, LONG_list l) {
  ARRAY_POINTERS aop = aop_create(2);
  aop_addPointer(aop, count);
  aop_addPointer(aop, l);
  g_slist_foreach(ids, (GFunc) insert_idSortedByCount, aop);
  aop_free(aop);
}
