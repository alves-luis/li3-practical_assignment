#include "heap.h"

struct heap {
    int   size;
    int   used;
    int (*valueFunc)(LONG_USER u);
    LONG_USER * heap ;
};

int heap_getSize(HEAP h) {
  if (h)
	 return h->size;
  else
    return -1;
}

int heap_getUsed(HEAP h) {
  if (h)
    return h->used;
  else
    return -1;
}

HEAP heap_new(int size, int (*valueFunction) (LONG_USER)) {
	HEAP h = malloc(sizeof(struct heap));
	if (h) {
		h->size = size;
		h->used = 0;
		h->heap = malloc(size*sizeof(LONG_USER));
    h->valueFunc = valueFunction;
		return h;
	}
	return NULL;
}

int heap_insert(HEAP h, LONG_USER u) {
	if (h) {
    if (h->used == h->size) {
      h->heap = realloc(h->heap, 2*(h->size)*sizeof(LONG_USER));
      h->size *= 2;
	  }
    h->heap[(h->used)] = u;
    h->used++;
    heap_bubbleUp(h,h->used-1);
    return 0;
  }
  else
    return -1;
}

LONG_USER heap_remove(HEAP h) {
	if (h) {
	  if (h->used > 0) {
      LONG_USER l = h->heap[0];
      h->heap[0] = h->heap[(h->used-1)];
      (h->used)--;
      heap_bubbleDown(h,0);
      return l;
    }
	}
  return NULL;
}

void swap(HEAP h, int a, int b) {
  if (h) {
    LONG_USER tmp = h->heap[a];
    h->heap[a] = h->heap[b];
    h->heap[b] = tmp;
  }
}

void heap_bubbleUp(HEAP h,int i) {
	if (h) {
    while(i > 0 && h->valueFunc(h->heap[PARENT(i)]) < h->valueFunc(h->heap[i])) {
      swap(h,i,PARENT(i));
      i = PARENT(i);
	   }
  }
}

void heap_bubbleDown(HEAP h,int i) {
	if (h) {
    int biggest = i;
    if (LEFT(i) < h->used && h->valueFunc(h->heap[biggest]) < h->valueFunc(h->heap[LEFT(i)]))
      biggest = LEFT(i);
    if (RIGHT(i) < h->used && h->valueFunc(h->heap[biggest]) < h->valueFunc(h->heap[RIGHT(i)]))
		  biggest = RIGHT(i);
	  if (biggest != i) {
      swap(h,i,biggest);
      heap_bubbleDown(h,biggest);
    }
  }
}

void heap_free(HEAP h) {
  if (h) {
    free(h->heap);
    free(h);
  }
}

HEAP heap_clone(HEAP h) {
  HEAP new = NULL;
  if (h) {
    new = heap_new(h->size,h->valueFunc);
    if (new) {
      new->valueFunc = h->valueFunc;
      new->used = h->used;
      new->heap = memcpy(new->heap,h->heap,h->size*sizeof(LONG_USER));
    }
  }
  return new;
}
