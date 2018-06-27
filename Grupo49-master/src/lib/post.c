#include <string.h>
#include <stdlib.h>
#include "post.h"
#include "common.h"
#include <stdio.h>

struct post {
    char* title;
    char* tags;
    long  id;
    long  parent_id;
    long  user_id;
    long best_answer_id;
    float best_answer_score;
    int   score;
    int reply_number;
};

struct short_post {
  long post_id;
  long user1_id;
  long user2_id;
};

POST create_post(unsigned char* title, unsigned char* tags, unsigned char* id, unsigned char* parent_id, unsigned char* user_id, unsigned char* post_type_id, unsigned char* score, unsigned char* reply_number) {
  POST p = malloc(sizeof(struct post));

  p->title = mystrdup((const char *)title);
  p->tags = mystrdup((const char *)tags);
  if (id) p->id = atol((const char*) id);

  if (atoi((const char*)post_type_id) == 2) {
    p->parent_id = atol((const char*) parent_id);
    p->reply_number =  atoi((const char*) reply_number);
  }else {
    p->parent_id = -1;
    p->reply_number = 0;
  }
  if (user_id) p->user_id = atol((const char*) user_id);
  if (score)   p->score = atoi((const char*) score);

  p->best_answer_id = -1;
  p->best_answer_score = -1;

  return p;
}
POST create_incomplete_post(long id, long best_answer_id ,int best_answer_score) {
  POST p = malloc(sizeof(struct post));

  p->id = id;
  p->best_answer_id = best_answer_id;
  p->best_answer_score = best_answer_score;
  p->reply_number = 0;

  return p;
}

long get_post_id(POST p) {
  return p->id;
}

long* get_post_id_pointer(POST p) {
    return &(p->id);
}

long get_post_user_id(POST p) {
    return p->user_id;
}

long* get_post_user_id_pointer(POST p) {
    return &(p->user_id);
}

long get_post_parent_id(POST p) {
    return p->parent_id;
}

long* get_post_parent_id_pointer(POST p) {
  return (&p->parent_id);
}

char* get_post_title(POST p) {
    return p->title;
}

char* get_post_tags(POST p) {
    return p->tags;
}

long get_post_best_answer_id(POST p) {
  return p->best_answer_id;
}

int get_post_type (POST p) {
  if (p->parent_id == -1) return 1;
  return 2;
}
int get_post_best_answer_score(POST p) {
  return p->best_answer_score;
}

int get_post_score(POST p) {
  return p->score;
}

int get_post_reply_number(POST p) {
  return p->reply_number;
}

void increment_post_reply_number(POST p){
      if (p) p->reply_number +=1;
}

void set_post_best_answer_id(POST p, long id) {
  p->best_answer_id = id;
}

void set_post_best_answer_score(POST p, int score) {
  p->best_answer_score = score;
}

void complete_post(POST p, POST aux) {
  p->title = aux->title;
  p->tags = aux->tags;
  p->parent_id = -1;
  p->user_id = aux->user_id;
  p->score = aux->score;
  p->reply_number = aux->reply_number;
}


SHORT_POST create_incomplete_short_post_user1(long id,long id1) {
  SHORT_POST s = malloc(sizeof(struct short_post));

  s->post_id = id;
  s->user1_id = id1;
  s->user2_id = -1000;

  return s;
}
SHORT_POST create_incomplete_short_post_user2(long id, long id2) {
  SHORT_POST s = malloc(sizeof(struct short_post));

  s->post_id = id;
  s->user1_id = -1000;
  s->user2_id = id2;

  return s;
}

long get_short_post_user1_id(SHORT_POST s) {
  return s->user1_id;
}

long get_short_post_user2_id(SHORT_POST s) {
  return s->user2_id;
}

void set_short_post_user1_id(SHORT_POST s, long id1){
  s->user1_id = id1;
}

void set_short_post_user2_id(SHORT_POST s, long id2){
  s->user2_id = id2;
}

void free_short_post(void* s) {
  SHORT_POST p = (SHORT_POST) s;

  if (p) {
    free(p);
  }
}

void free_post(void* rip) {
    POST p = (POST) rip;

    if(p) {
    free(p->title);
    free(p->tags);
    free(p);
  }
}
