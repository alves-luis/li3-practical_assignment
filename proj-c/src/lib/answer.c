#include "answer.h"

struct answer {
  POST parent;
  int score;
  int comments;
};

ANSWER answer_create(POST parent) {
  ANSWER r = malloc(sizeof(struct answer));
  if (r) {
    r->parent = parent;
    r->score = 0;
    r->comments = 0;
  }
  return r;
}

void answer_free(ANSWER a) {
  if (a)
    free(a);
}


int answer_getScore(ANSWER a) {
  if (a)
    return a->score;
  else
    return -1;
}

void answer_setScore(ANSWER a, int ns) {
  if (a)
    a->score = ns;
}

int answer_getNumComments(ANSWER a) {
  if (a)
    return a->comments;
  else
    return -1;
}

void answer_setNumComments(ANSWER a, int nc) {
  if (a)
    a->comments = nc;
}

POST answer_getParent(ANSWER a) {
  if (a)
    return a->parent;
  else
    return NULL;
}

void answer_setParent(ANSWER a, POST p) {
  if (a)
    a->parent = p;
}

long answer_getParentId(ANSWER a) {
  long result = -1;
  POST q;
  if (a) {
    q = answer_getParent(a);
    result = post_getId(q);
  }
  return result;
}

long answer_getCreatorId(ANSWER a) {
  long result = -1;
  if (a) {
    POST p = answer_getPost(a);
    result = post_getCreatorId(p);
  }
  return result;
}

POST answer_getPost(ANSWER a) {
  if (a) {
    return a->parent;
  }
  else
    return NULL;
}

long answer_getId(ANSWER a) {
  long result = -1;
  if (a) {
    POST p = answer_getPost(a);
    result = post_getId(p);
  }
  return result;
}


// Compares Answers by date (most recent is < 0)
int answerCompare(ANSWER a, ANSWER b) {
  POST pa = answer_getPost(a);
  POST pb = answer_getPost(b);
  DateTime da = post_getDate(pa);
  DateTime db = post_getDate(pb);
  return date_time_compare(da,db);
}
