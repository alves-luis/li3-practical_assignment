#include "interface.h"
#include <glib.h>
#include <stdlib.h>

TAD_community init() {
    return community_init();
}

// *************************** QUERY 1 ***************************
STR_pair info_from_post(TAD_community com, long id) {
  STR_pair result;
  long creatorId;
  LONG_USER u;
  HASHTABLE h1 = tad_getPostsByHash(com);
  HASHTABLE h2 = tad_getUsersByHash(com);
  POST p = (POST) hash_get(id,h1);

  if (p) { // post exists
    if (!post_getType(p)) { // question
      creatorId = post_getCreatorId(p);
      u = (LONG_USER) hash_get(creatorId,h2);
      result = create_str_pair(post_getTitle(p),long_user_getName(u));
    }
    else { // answer
      POST parent = post_getParent(p);
      creatorId = post_getCreatorId(parent);
      u = (LONG_USER) hash_get(creatorId,h2);
      result = create_str_pair(post_getTitle(parent),long_user_getName(u));
    }
  }
  else
    result = create_str_pair(NULL,NULL);

  return result;
}

// *************************** QUERY 2 ***************************
LONG_list top_most_active(TAD_community com, int N) {
  LONG_list result;
  HEAP h = tad_getUsersByNumberOfPosts(com);
  h = heap_clone(h);
  LONG_USER heapElem;
  long listElem;
  int i, maxSize;

  maxSize = heap_getUsed(h) > N ? N : heap_getUsed(h);
  result = create_list(maxSize);
  for(i = 0; i < maxSize; i++) {
    heapElem = heap_remove(h);
    listElem = long_user_getId(heapElem);
    set_list(result, i, listElem);
  }
  heap_free(h);
  return result;
}

// *************************** QUERY 3 ***************************
LONG_pair total_posts (TAD_community com, Date begin, Date end) {
  SEQUENCE seq = tad_getPostsBySequence(com);
  DateTime d1 = date_to_date_time(begin);
  DateTime d2 = date_to_date_time(end);

  LONG_pair lp = create_long_pair(0,0);
  seq_inBetweenDates (seq, d1, d2, (GFunc) countQA, lp);
  return lp;
}

// *************************** QUERY 4 ***************************
void add_questions_with_tag (POST p, ARRAY_POINTERS aop) {
  char* tag = (char*) aop_getPointer(aop, 0);
  if (!post_getType(p) && post_check_tag(p, tag))
    add_list(aop_getPointer(aop, 1), post_getId(p));
}

LONG_list questions_with_tag (TAD_community com, char* tag, Date begin, Date end) {
  DateTime d1 = date_to_date_time(begin);
  DateTime d2 = date_to_date_time(end);
  SEQUENCE seq = tad_getPostsBySequence(com);

  LONG_list ll = create_list(1);
  ARRAY_POINTERS aop = aop_create(2);
  aop_addPointer(aop,tag);
  aop_addPointer(aop,ll);
  seq_inBetweenDates(seq, d1, d2, (GFunc) add_questions_with_tag, aop);
  aop_free(aop);
  free_unused_mem(ll);
  reverse_list(ll);
  return ll;
}
// *************************** QUERY 5 ***************************
USER get_user_info(TAD_community com, long id) {
  HASHTABLE hashOfUsers = tad_getUsersByHash(com);
  LONG_USER user = (LONG_USER) hash_get(id,hashOfUsers);
  if (!user) return NULL;

  long * posts = long_user_get10LastPosts(user);
  char * bio = long_user_getBio(user);
  USER result = create_user(bio,posts);
  return result;
}

// *************************** QUERY 6 ***************************

LONG_list most_voted_answers (TAD_community com, int N, Date begin, Date end) {
  DateTime d1 = date_to_date_time(begin);
  DateTime d2 = date_to_date_time(end);
  SEQUENCE seq = tad_getPostsBySequence(com);
  HASHTABLE hash = tad_getPostsByHash(com);

  LONG_list ll = create_list(N);
  ARRAY_POINTERS aop = aop_create(2);
  aop_addPointer(aop, hash);
  aop_addPointer(aop, ll);
  seq_inBetweenDates(seq, d1, d2, (GFunc) insert_postSortedByVotes, aop);
  aop_free(aop);
  return ll;
}

// *************************** QUERY 7 ***************************
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end) {
  DateTime d1 = date_to_date_time(begin);
  DateTime d2 = date_to_date_time(end);
  HASHTABLE hash = tad_getPostsByHash(com);

  SEQUENCE seq = tad_getPostsBySequence(com);
  LONG_list ll = create_list(N);
  ARRAY_POINTERS aop = aop_create(2);
  aop_addPointer(aop, hash);
  aop_addPointer(aop, ll);
  seq_inBetweenDates(seq, d1, d2, (GFunc) insert_postSortedByNumAnswers, aop);
  aop_free(aop);

  return ll;
}
// *************************** QUERY 8 ***************************
void post_hasWord(void * key, void * value, void * user_data) {
  POST p = (POST) value;
  parseArray wordAndSeq = (parseArray) user_data;
  SEQUENCE s = (SEQUENCE) g_ptr_array_index(wordAndSeq,0);
  char * word = (char *) g_ptr_array_index(wordAndSeq,1);
  char * result = NULL;
  if (post_getTitle(p)) result = strstr(post_getTitle(p),word);
  if (result) seq_insertPost(s,p);
}

LONG_list contains_word(TAD_community com, char* word, int N) {
  LONG_list result = NULL;
  long * listOfIndexes;
  int maxSize;
  SEQUENCE s = seq_create();
  parseArray wordAndSeq = g_ptr_array_sized_new(2);

  g_ptr_array_insert(wordAndSeq,0,s);
  g_ptr_array_insert(wordAndSeq,1,word);
  hash_forEach(tad_getPostsByHash(com),post_hasWord,wordAndSeq);
  seq_sortPost(s);

  maxSize = seq_getSize(s) > N ? N : seq_getSize(s);
  listOfIndexes = seq_getNFirstPost(s,maxSize);
  result = create_list(maxSize);
  for (int i = 0; i < maxSize; i++) {
    set_list(result,i,listOfIndexes[i]);
  }

  g_ptr_array_free(wordAndSeq,0);
  seq_free(s);
  free(listOfIndexes);
  return result;
}


// *************************** QUERY 9 ***************************
void both_participated_addPostsToHash(LONG_USER u1, TAD_community com, long * postsOfU1IDs, HASHTABLE postsOfU1byHash) {
  int i;
  POST p;
  for (i = 0; i < long_user_getNumberOfPosts(u1); i++) {
    p = (POST) hash_get(postsOfU1IDs[i],tad_getPostsByHash(com));
    // if it's an answer, add the question
    if (post_getType(p) && post_getParentId(p))
      hash_insert(post_getParentId(p),post_getParent(p),postsOfU1byHash);
    else
      hash_insert(postsOfU1IDs[i],p,postsOfU1byHash);
  }
}

void both_participated_cleanMemory(long * postsOfU1IDs, long * postsOfU2IDs, HASHTABLE postsOfU1byHash, long * listOfIndexes, SEQUENCE both_participated) {
  hash_freeTable(postsOfU1byHash);
  seq_free(both_participated);
  free(postsOfU1IDs);
  free(postsOfU2IDs);
  free(listOfIndexes);
}

void both_participated_addCommonToSeq(LONG_USER u2, TAD_community com, long * postsOfU2IDs, HASHTABLE postsOfU1byHash, SEQUENCE both_participated) {
  int i;
  POST p;
  for (i = 0; i < long_user_getNumberOfPosts(u2); i++) {
    p = (POST) hash_get(postsOfU2IDs[i],tad_getPostsByHash(com));
    // if it's answer, get the question
    if (post_getType(p) && post_getParentId(p))
      p = (POST) hash_get(post_getParentId(p),tad_getPostsByHash(com));
    // if question and exists and hasn't been added to seq, is common so add to seq
    if (!post_getType(p) && hash_get(post_getId(p),postsOfU1byHash) && !seq_elem(both_participated,p))
      seq_insertPost(both_participated,p);
  }
  seq_sortPost(both_participated);
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N) {
  LONG_USER u1 = (LONG_USER) hash_get(id1,tad_getUsersByHash(com));
  LONG_USER u2 = (LONG_USER) hash_get(id2,tad_getUsersByHash(com));

  if (u1 && u2) {
    HASHTABLE postsOfU1byHash = hash_new(NULL,1);
    SEQUENCE both_participated = seq_create();
    long * postsOfU1IDs = seq_getNFirstPost(long_user_getPosts(u1),long_user_getNumberOfPosts(u1));
    long * postsOfU2IDs = seq_getNFirstPost(long_user_getPosts(u2),long_user_getNumberOfPosts(u2));
    long * listOfIndexes;
    int i,maxSize;
    LONG_list result;

    both_participated_addPostsToHash(u1,com,postsOfU1IDs,postsOfU1byHash);
    both_participated_addCommonToSeq(u2,com,postsOfU2IDs,postsOfU1byHash,both_participated);

    maxSize = seq_getSize(both_participated) > N ? N : seq_getSize(both_participated);
    listOfIndexes = seq_getNFirstPost(both_participated,maxSize);
    result = create_list(maxSize);

    for (i = 0; i < maxSize; i++) {
      set_list(result,i,listOfIndexes[i]);
    }

    both_participated_cleanMemory(postsOfU1IDs,postsOfU2IDs,postsOfU1byHash,listOfIndexes,both_participated);
    return result;
  }
  else
    return NULL;
}

// *************************** QUERY 10 ***************************
long better_answer(TAD_community com, long id) {
  POST question = (POST) hash_get(id,tad_getPostsByHash(com));
  if (post_getType(question)) return (0);

  LONG_USER user;
  long score = 0;
  long bestAnswer = 0;
  long result = 0;
  int max = post_getNumAnswers(question);

  for (int i = 0; i < max; i++) {
    POST p = post_getNAnswer(question,i);
    user = (LONG_USER) hash_get(post_getCreatorId(p),tad_getUsersByHash(com));
    score = post_getScore(p)*0.65 + long_user_getReputation(user)*0.25 + post_getNumComments(p)*0.1;
    if (score > bestAnswer) {
      bestAnswer = score;
      result = post_getId(p);
    }
  }
  return result;
}
// *************************** QUERY 11 ***************************

void insert_postSortedByMostUsedTags (POST p, ARRAY_POINTERS aop) {
  if (!post_getType(p) && elem_list(aop_getPointer(aop,2), post_getCreatorId(p)))
    linked_insert_tags_hash(post_getTags(p), aop);
}

LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end) {
  DateTime d1 = date_to_date_time(begin);
  DateTime d2 = date_to_date_time(end);
  SEQUENCE seq = tad_getPostsBySequence(com);
  HASHTABLE tags = tad_getTagsByHash(com);

  LONG_list result = NULL;
  HEAP h = tad_getUsersByReputation(com);
  h = heap_clone(h);
  LONG_USER heapElem;
  long listElem;
  int i, maxSize;
  maxSize = heap_getUsed(h) > N ? N : heap_getUsed(h);
  result = create_list(maxSize);
  for(i = 0; i < maxSize; i++) {
    heapElem = heap_remove(h);
    listElem = long_user_getId(heapElem);
    set_list(result, i, listElem);
    inc_occupied(result);
  }
  heap_free(h);

  HASHTABLE post_count = hash_new(free, 0);
  ARRAY_POINTERS aop = aop_create(3);
  aop_addPointer(aop,post_count);
  aop_addPointer(aop,tags);
  aop_addPointer(aop,result);
  seq_inBetweenDates(seq, d1, d2, (GFunc) insert_postSortedByMostUsedTags, aop);
  aop_free(aop);
  LONG_list final_list = create_list(N);
  LIST keys_hash = hash_getKeys(post_count);
  linked_foreachIdInsert(keys_hash, post_count, final_list);

  hash_freeTable(post_count);
  hash_freeKeysList(keys_hash);
  free_list(result);
  return final_list;
}

// CLEAN MEMORY

TAD_community clean(TAD_community com) {
  hash_freeTable(tad_getUsersByHash(com));
  hash_freeTable(tad_getPostsByHash(com));
  hash_freeTable(tad_getTagsByHash(com));
  heap_free(tad_getUsersByReputation(com));
  heap_free(tad_getUsersByNumberOfPosts(com));
  seq_free(tad_getPostsBySequence(com));
  free(com);
  return com;
}
