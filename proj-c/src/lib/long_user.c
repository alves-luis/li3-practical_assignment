#include "long_user.h"

struct long_user {
  char * bio;
  char* name;
  long id;
  SEQUENCE allPosts; //by date
  int reputation;
  int numberOfPosts;
};

LONG_USER long_user_create(char * bio, char * name, long id, int rep) {
  LONG_USER l = malloc(sizeof(struct long_user));
  if (l) {
    long_user_setBio(l,bio);
    long_user_setName(l,name);
    long_user_setId(l,id);
    long_user_setNumberOfPosts(l,0);
    long_user_setReputation(l,rep);
    l->allPosts = seq_create();
  }
  return l;
}

char * long_user_getBio(LONG_USER u) {
  if (u)
    return u->bio;
  else
    return NULL;
}

void long_user_addPost(LONG_USER u, void * post) {
  if (u)
    seq_insertPost(u->allPosts,(POST) post);
}

SEQUENCE long_user_getPosts(LONG_USER u) {
  if (u) {
    seq_sortPost(u->allPosts);
    return u->allPosts;
  }
  else
    return NULL;
}

long * long_user_get10LastPosts(LONG_USER u) {
  if (u)
    return seq_getNFirstPost(u->allPosts,10);
  else
    return NULL;
}

char * long_user_getName(LONG_USER u) {
  if (u)
    return u->name;
  else
    return NULL;
}

long long_user_getId(LONG_USER u) {
  if (u)
    return u->id;
  else
    return -1;
}

int long_user_getNumberOfPosts(LONG_USER u) {
  if (u)
    return u->numberOfPosts;
  else
    return -1;
}

int long_user_getReputation(LONG_USER u) {
  if (u)
    return u->reputation;
  else
    return -1;
}

void long_user_setName(LONG_USER u, char * nname) {
  if (u)
    u->name = mystrdup(nname);
}

void long_user_setBio(LONG_USER u, char * nbio) {
  if (u)
    u->bio = mystrdup(nbio);
}

void long_user_setId(LONG_USER u, long nid) {
  if (u)
    u->id = nid;
}

void long_user_setNumberOfPosts(LONG_USER u, int num) {
  if (u)
    u->numberOfPosts = num;
}

void long_user_setReputation(LONG_USER u,int rep) {
  if (u)
    u->reputation = rep;
}

void long_user_addNumberOfPosts(LONG_USER u, int num) {
  if (u)
    u->numberOfPosts += num;
}

void long_user_free(LONG_USER u) {
  if (u) {
    free(u->bio);
    free(u->name);
    seq_free(u->allPosts);
    free(u);
  }
}

void long_user_printSize(LONG_USER p) {
  printf("Size of bio: %lu\n",sizeof(p->bio));
  printf("Size of id: %lu\n",sizeof(p->name));
  printf("Size of creationDate: %lu\n",sizeof(p->id));
  printf("Size of User: %lu\n",sizeof(p->reputation));
  printf("Size of type: %lu\n",sizeof(p->numberOfPosts));
  printf("Total size: %lu\n",sizeof(struct long_user));
}
