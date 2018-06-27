#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <limits.h>

struct llist {
  int size;
  int occupied;
  long * list;
};

LONG_list create_list(int size) {
    if(size <= 0) return NULL;
    LONG_list l = malloc(sizeof(struct llist));
    l->size = size;
    l->list = malloc(sizeof(long) * size);
    l->occupied = 0;
    return l;
}

long get_list(LONG_list l, int index) {
    return l->list[index];
}

int get_size(LONG_list l) {
  return l->size;
}

int get_occupied(LONG_list l) {
  return l->occupied;
}

void inc_occupied (LONG_list l) {
  l->occupied +=1;
}

void set_list(LONG_list l, int index, long value) {
  if (index >= 0 && index < get_size(l))
    l->list[index] = value;
}

void add_list(LONG_list l, long value) {
  if (l->occupied == l->size) {
    l->list = realloc(l->list, 2*(l->size)*sizeof(struct llist));
    l->size *= 2;
  }
  l->list[l->occupied] = value;
  inc_occupied(l);
}

void free_list(LONG_list l) {
  if(l) {
    free(l->list);
    free(l);
  }
}

void free_unused_mem(LONG_list l) {
  if (l->occupied <= 0) return;
  void* tmp = realloc(l->list, (l->occupied-1)*sizeof(struct llist));
  if (!tmp) puts("Couldn't shorten size");
  else l->list = tmp;
  l->size = l->occupied;
}

void reverse_list(LONG_list l) {
  int size = get_size(l)-1;
  for (int i=0; i<size/2; i++) {
      long temp = l->list[size-i];
      l->list[size-i] = l->list[i];
      l->list[i] = temp;
  }
}

void print_list(LONG_list l) {
  int size = get_size(l);
  int occupied = get_occupied(l);
  for (int i=0; i<occupied; i++)
    printf("Id: %ld; ", get_list(l, i));

  printf("\n");
  printf("Occupied: %d\n", occupied);
  printf("Size: %d\n", size);
}

int elem_list(LONG_list l, long elem) {
  if (get_size(l) == 0) return 0;
  for (int i=0; i<get_size(l); i++)
    if (get_list(l, i) == elem) return 1;
  return 0;
}

// For Query 6
void insert_postSortedByVotes (POST p, ARRAY_POINTERS aop) {

  HASHTABLE h = (HASHTABLE) aop_getPointer(aop, 0);
  LONG_list l = (LONG_list) aop_getPointer(aop, 1);

  if (!post_getType(p)) return;

  int votes = post_getVoteCount(p), votes_i = INT_MIN, new_elem = 0, i;

  if (get_occupied(l) < get_size(l)) {new_elem = 1; inc_occupied(l);}

  for (i=get_occupied(l)-1; i>=0; i--) {
    if (!new_elem) votes_i = post_getVoteCount((POST) hash_get(get_list(l, i), h));
    if (votes < votes_i) break;
    if (i > 0) set_list(l, i, get_list(l, i-1));
    if (new_elem) new_elem=0;
  }

  if (i < get_occupied(l)-1) set_list(l, i+1, post_getId(p));
}

// For query 7
void insert_postSortedByNumAnswers (POST p, ARRAY_POINTERS aop) {

  HASHTABLE h = aop_getPointer(aop,0);
  LONG_list l = aop_getPointer(aop,1);

  if (post_getType(p)) return;

  int answers = post_getNumAnswers(p), answers_i = INT_MIN, new_elem = 0, i;

  if (get_occupied(l) < get_size(l)) {new_elem = 1; inc_occupied(l);}

  for (i=get_occupied(l)-1; i>=0; i--) {
    if (!new_elem) answers_i = post_getNumAnswers((POST) hash_get(get_list(l, i), h));
    if (answers < answers_i) break;
    if (i > 0) set_list(l, i, get_list(l, i-1));
    if (new_elem) new_elem=0;
  }

  if (i < get_occupied(l)-1) set_list(l, i+1, post_getId(p));
}

// For query 11
void insert_idSortedByCount (long* id_pointer, ARRAY_POINTERS aop) {

  HASHTABLE h = aop_getPointer(aop,0);
  LONG_list l = aop_getPointer(aop,1);

  long id = *id_pointer;

  int* count_v = (int*) hash_get(id, h);

  int count = (int) *count_v, count_i = INT_MIN, new_elem = 0, i;

  if (get_occupied(l) < get_size(l)) {new_elem = 1; inc_occupied(l);}

  for (i=get_occupied(l)-1; i>=0; i--) {
    if (!new_elem) {
      int* count_vi = hash_get(get_list(l, i), h);
      count_i = (int) *count_vi;
    }
    if (count <= count_i) break;
    if (i > 0) set_list(l, i, get_list(l, i-1));
    if (new_elem) new_elem=0;
  }

  if (i < get_occupied(l)-1) set_list(l, i+1, id);
}
