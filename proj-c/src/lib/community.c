#include "community.h"

struct TCD_community {
    HASHTABLE usersByHash;
    HASHTABLE postsByHash;
    HASHTABLE tagsByString;
    HEAP usersByNumberOfPosts;
    HEAP usersByReputation;
    SEQUENCE postsBySequence;

};

TAD_community community_init() {
    TAD_community com = malloc (sizeof (struct TCD_community));
    if (com) {
      com->usersByHash = hash_new((GDestroyNotify)long_user_free,1);
      com->postsByHash = hash_new((GDestroyNotify)post_free,1);
      com->tagsByString = hash_new(NULL,0);
      com->usersByNumberOfPosts = heap_new(INITIAL_HEAP_SIZE, long_user_getNumberOfPosts);
      com->usersByReputation = heap_new(INITIAL_HEAP_SIZE, long_user_getReputation);
      com->postsBySequence = seq_create();
    }
    return com;
}

HASHTABLE tad_getUsersByHash(TAD_community com) {
  if (com)
    return com->usersByHash;
  else
    return NULL;
}


HEAP tad_getUsersByNumberOfPosts(TAD_community com) {
  if (com)
    return com->usersByNumberOfPosts;
  else
    return NULL;
}

HEAP tad_getUsersByReputation(TAD_community com) {
  if (com)
    return com->usersByReputation;
  else
    return NULL;
}

HASHTABLE tad_getPostsByHash(TAD_community com) {
  if (com)
    return com->postsByHash;
  else
    return NULL;
}

HASHTABLE tad_getTagsByHash(TAD_community com) {
  if (com)
    return com->tagsByString;
  else
    return NULL;
}

SEQUENCE tad_getPostsBySequence(TAD_community com) {
  if (com)
    return com->postsBySequence;
  else
    return NULL;
}
