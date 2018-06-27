#include "sequence.h"

SEQUENCE seq_create() {
  return g_sequence_new(NULL);
}

void seq_free(SEQUENCE s) {
  g_sequence_free(s);
}

void seq_insertPost(SEQUENCE s, POST p) {
  if (s)
    g_sequence_prepend(s,p);
}

void seq_insertPostEnd(POST p, SEQUENCE s) {
  if (s)
    g_sequence_append(s,p);
}

int seq_getSize(SEQUENCE s) {
  return g_sequence_get_length (s);
}

void seq_sortPost(SEQUENCE s) {
  g_sequence_sort (s,(GCompareDataFunc)postCompare,NULL);
}

void seq_sortPostNormal(SEQUENCE s) {
  g_sequence_sort (s,(GCompareDataFunc) post_compare,NULL);
}

int post_compareByVotes (POST a, POST b) {
  return -(post_getVoteCount(a) - post_getVoteCount(b));
}

void seq_sortAnswer(SEQUENCE s) {
  g_sequence_sort(s, (GCompareDataFunc) post_compareByVotes, NULL);
}

void * seq_elem(SEQUENCE s,void * p) {
  seq_sortPost(s);
  return g_sequence_lookup(s,(POST)p,(GCompareDataFunc)postCompare,NULL);
}

long * seq_getNFirstPost(SEQUENCE s, int N) {
  long * posts = malloc(sizeof(long)*N);
  int i = 0;
  POST p;
  seq_sortPost(s);
  GSequenceIter * begin = g_sequence_get_begin_iter(s);
  GSequenceIter * end = g_sequence_get_iter_at_pos(s,N);
  if (posts) {
    while (begin != end) {
      p = g_sequence_get(begin);
      posts[i++] = post_getId(p);
      begin = g_sequence_iter_next(begin);
    }
  }
  // fills the rest of the array of longs with 0's
  while (i < N) {
    posts[i++] = 0;
  }
  return posts;
}

LONG_list seq_toList (SEQUENCE s, int N) {
  if (N <= 0) {
    LONG_list l = create_list(seq_getSize(s));
    g_sequence_foreach(s, (GFunc) add_list, l);
    return l;
  } else {
    LONG_list l = create_list(N);
    GSequenceIter* it = g_sequence_get_begin_iter(s);
    for (int i=0; i<N; i++) {
      add_list(l, post_getId((POST) g_sequence_get(it)));
      it = g_sequence_iter_next(it);
    }
    return l;
  }
}

void seq_inBetweenDates(SEQUENCE s, DateTime d1, DateTime d2, GFunc func, void* data) {
  POST p1 = post_create(0, NULL);
  post_setDate(p1, d1);

  DateTime d2b = date_time_inc(d2);
  date_time_free(d2);
  POST p2 = post_create(0, NULL);
  post_setDate(p2, d2b);

  GSequenceIter* begin = g_sequence_search(s, p1, (GCompareDataFunc) post_compare, NULL);
  GSequenceIter* end = g_sequence_search(s, p2, (GCompareDataFunc) post_compare, NULL);
  end = g_sequence_iter_prev(end);

  GSequenceIter* temp;
  POST p;

  do {
    temp = g_sequence_iter_prev(begin);
    p = (POST) g_sequence_get(temp);
    if (post_compare(p,p1) >= 0 && !g_sequence_iter_is_begin(temp))
      begin = temp;
  } while(!g_sequence_iter_is_begin(temp) && post_compare(p,p1) >= 0);

  do {
    temp = g_sequence_iter_next(end);
    if (temp && !g_sequence_iter_is_end(temp)) {
      p = (POST) g_sequence_get(temp);
      if (post_compare(p,p2) < 0)
        end = temp;
    }
  } while(temp && !g_sequence_iter_is_end(temp) && post_compare(p, p2) < 0);

  g_sequence_foreach_range(begin, g_sequence_iter_next(end), func, data);

  post_free(p1);
  post_free(p2);
}
