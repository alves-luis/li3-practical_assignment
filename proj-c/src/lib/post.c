#include "post.h"

union type {
  ANSWER answer;
  QUESTION question;
};

struct post {
    char * title; // can be NULL
    long id;
    DateTime creationDate;
    long creator;
    int type; // whether it's an answer (!0) or question (0)
    union subtype {
      ANSWER answer;
      QUESTION question;
    } subtype;
};

// If it's an answer, pass the reference to the question. Else, pass NULL.
POST post_create(int type, void * question) {
  POST p = malloc(sizeof(struct post));
  if (!p) return NULL;

  p->title = NULL;
  p->id = -99;
  p->creationDate = NULL;
  p->creator = -1;
  p->type = type;

  if (type) // answer
    p->subtype.answer = answer_create((POST) question);
  else // question
    p->subtype.question = question_create();

  return p;
}

void post_free(POST p) {
  if (p) {
    free(p->title);
    date_time_free(p->creationDate);
    if (p->type) // answer
      answer_free(p->subtype.answer);
    else
      question_free(p->subtype.question);
    free(p);
  }
}

long post_getId (POST p) {
  if (p)
    return p->id;
  else
    return 0;
}

long post_getCreatorId (POST p) {
  if (p)
    return p->creator;
  else
    return -1;
}

char * post_getTitle (POST p) {
  if (p)
    return p->title;
  else
    return NULL;
}

DateTime post_getDate (POST p) {
  if (p)
    return p->creationDate;
  else
    return NULL;
}

int post_getType(POST p) {
  if (p)
    return p->type;
  else
    return -1;
}

void post_setId (POST p, long nid) {
  if (p)
    p->id = nid;
}

void post_setCreator (POST p, long id) {
  if (p)
    p->creator = id;
}

void post_setTitle(POST p, char * newtitle) {
  if (p)
    p->title = mystrdup (newtitle);
}

void post_setDate(POST p, DateTime d) {
  if (p)
    p->creationDate = d;
}

void post_setType(POST p, int t) {
  if (p)
    p->type = t;
}

void post_addAnswer(POST p, POST answer) {
  if (p && !(p->type))
    question_addAnswer(p->subtype.question,answer);
}

void post_print (POST p) {
  long postid = post_getId(p);

  char date[25];
  date_time_to_string(post_getDate(p), date);

  printf("PID: %ld, PPID: %ld, DATE: %s, TYPE: %s;", postid, post_getCreatorId(p), date, (post_getType(p) ? "Answer" : "Question"));
  if (post_getType(p))
    printf(" VOTES: %d\n", post_getVoteCount(p));
  else {
    printf(" No Answers: %d;", post_getNumAnswers(p));
    printf(" TAGS: ");
    print_list_tags(post_getTags(p));
  }
}

POST post_getParent(POST p) {
  if (p && p->type)
    return answer_getParent(p->subtype.answer);
  else
    return NULL;
}

long post_getParentId(POST p) {
  long result = 0;
  if (p && p->type) {
    POST parent = post_getParent(p);
    result = post_getId(parent);
  }
  return result;
}

int post_getScore(POST p) {
  if (p && p->type)
    return answer_getScore(p->subtype.answer);
  else
    return -1;
}

void post_setScore(POST p, int nscore) {
  if (p && p->type)
    answer_setScore(p->subtype.answer,nscore);
}

int post_getNumComments(POST p) {
  if (p && p->type)
    return answer_getNumComments(p->subtype.answer);
  else
    return -1;
}

void post_setNumComments(POST p, int ncom) {
  if (p && p->type)
    answer_setNumComments(p->subtype.answer,ncom);
}

int post_getVoteCount(POST p) {
  if (p && p->type)
    return answer_getScore(p->subtype.answer);
  else
    return -1;
}

int post_getNumAnswers(POST p) {
  if (p && !p->type)
    return question_getNumAnswers(p->subtype.question);
  else
    return -1;
}

POST post_getNAnswer(POST p, int N) {
  if (p && !p->type)
    return question_getNAnswer(p->subtype.question,N);
  else
    return NULL;
}

LIST post_getTags(POST p) {
  if (p && !p->type)
    return question_getTags(p->subtype.question);
  else
    return NULL;
}

int post_check_tag(POST p, char* tag) {
  if (post_getType(p)) return 0;
  LIST tags = post_getTags(p);
  return (g_slist_find_custom(tags, tag, (GCompareFunc) strcmp) != NULL);
}

void post_setTags (POST p, LIST tags) {
  if (p && !p->type)
    question_setTags(p->subtype.question, tags);
}

int post_betweenDates (POST p, DateTime begin, DateTime end) {
 DateTime date = post_getDate(p);
 return date_time_compare(date, begin) >= 0 &&
        date_time_compare(date, end) <= 0;
}

// Compares Answers by date
int postCompare(POST a, POST b) {
  if (!a || !b) return 0;
  DateTime da = post_getDate(a);
  DateTime db = post_getDate(b);
  return date_time_compare(db,da);
}

int post_compare(POST a, POST b) {
  if (!a || !b) return 0;
  DateTime da = post_getDate(a);
  DateTime db = post_getDate(b);
  return date_time_compare(da,db);
}

void countQA (POST p, LONG_pair lp) {
  post_getType(p) ? inc_snd_long(lp) : inc_fst_long(lp);
}

void post_printSize(POST p) {
  printf("Size of title: %lu\n",sizeof(p->title));
  printf("Size of id: %lu\n",sizeof(p->id));
  printf("Size of creationDate: %lu\n",sizeof(p->creationDate));
  printf("Size of User: %lu\n",sizeof(p->creator));
  printf("Size of type: %lu\n",sizeof(p->type));
  printf("Size of pointer: %lu\n",sizeof(p->subtype));
  printf("Total size: %lu\n",sizeof(struct post));
}
