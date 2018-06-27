#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "users.h"
#include "post.h"
#include "common.h"

struct users {
  char* short_bio;
  char* nickname;
  long id;
  int rep;
  int post_number;
};

USERS create_users(unsigned char* short_bio, unsigned char* nickname, unsigned char* id, unsigned char* rep) {
  USERS u = malloc(sizeof(struct users));

  u->short_bio    = mystrdup((const char *)short_bio);
  u->nickname     = mystrdup((const char *)nickname);
  u->post_number  = 0;
  if (id) u->id   = atol((const char*)id);
  if (rep) u->rep = atoi((const char*) rep);
  return u;
}

USERS create_incomplete_users(unsigned char* id) {
  USERS u = malloc(sizeof(struct users));

  u -> short_bio = NULL;
  u -> nickname = NULL;
  u -> id = atol((const char*)id);
  u -> rep = -1;
  u -> post_number = 1;

  return u;
}

char* get_users_nickname(USERS u) {
  return u->nickname;
}

char* get_users_short_bio(USERS u) {
  return u->short_bio;
}

long get_users_id(USERS u) {
  return u->id;
}

long* get_users_id_pointer(USERS u) {
  return &(u->id);
}

int get_users_post_number(USERS u) {
  return u->post_number;
}

int get_users_rep(USERS u) {
  if(!u) return -1;
  return u->rep;
}

void set_users_post_number(USERS u, int n) {
  u->post_number = n;
}

void free_users(void* rip) {
  USERS u = (USERS) rip;
  
  if (u) {
    free(u->short_bio);
    free(u->nickname);
    free(u);
  }
}
