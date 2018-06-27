#include "array_pointers.h"

struct array_pointers {
  int size;
  int occupied;
  GPtrArray * pointers;
};

ARRAY_POINTERS aop_create (int size) {
  ARRAY_POINTERS aop = (ARRAY_POINTERS) malloc (sizeof (struct array_pointers));
  aop->size = size;
  aop->occupied = 0;
  aop->pointers = g_ptr_array_sized_new(size);
  return aop;
}

int aop_getSize(ARRAY_POINTERS aop) {
  return aop->size;
}

int aop_getOccupied(ARRAY_POINTERS aop) {
  return aop->occupied;
}

void aop_addPointer(ARRAY_POINTERS aop, void * pointer) {
  if (aop->occupied < aop->size) {
    g_ptr_array_insert(aop->pointers, aop->occupied, pointer);
    aop->occupied++;
  }
}

void* aop_getPointer(ARRAY_POINTERS aop, int index) {
  if (index >= aop->occupied)
    return NULL;
  return g_ptr_array_index(aop->pointers, index);
}

void aop_free(ARRAY_POINTERS aop) {
  g_ptr_array_free(aop->pointers, TRUE);
  free(aop);
}
