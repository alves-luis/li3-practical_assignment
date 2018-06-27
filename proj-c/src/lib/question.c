#include "question.h"

struct question {
  LIST answers;
  LIST tags;
  int numAnswers;
};

QUESTION question_create() {
  QUESTION q = malloc(sizeof(struct question));
  if (!q) return NULL;
  q->answers = NULL;
  q->tags = NULL;
  q->numAnswers = 0;
  return q;
}

LIST question_getAnswers(QUESTION q) {
  if (!q) return NULL;
  return g_slist_sort(q->answers, (GCompareFunc)postCompare);
}

POST question_getNAnswer(QUESTION q, int N) {
  if (!q) return NULL;
  return (POST) g_slist_nth_data(g_slist_sort(q->answers, (GCompareFunc)postCompare),N);
}

LIST question_getNAnswers(QUESTION q, int N) {
  if (!q) return NULL;
  LIST result = g_slist_sort(q->answers, (GCompareFunc)postCompare);
  LIST it = NULL;
  int i;
  for (i = 0; i < (N > q->numAnswers ? q->numAnswers : N); i++) {
    it = g_slist_nth(q->answers,i);
    result = g_slist_append(result,it);
  }
  return result;
}

int question_getNumAnswers(QUESTION q) {
  if (q)
    return q->numAnswers;
  else
    return -1;
}

LIST question_getTags(QUESTION q) {
  if (!q) return NULL;
  return q->tags;
}

// Currently as List()
void question_addAnswer(QUESTION q, POST a) {
  if (q) {
    q->answers = g_slist_prepend (q->answers,a);
    q->numAnswers++;
  }
}

void question_setTags(QUESTION q, LIST l) {
  q->tags = l;
}

void question_free(QUESTION q) {
  if (q) {
    g_slist_free_full (q->tags,(GDestroyNotify)free);
    g_slist_free (q->answers);
    free(q);
  }
}
