#include "hash.h"

HASHTABLE hash_new(GDestroyNotify func, int type) {
  HASHTABLE t;
  if (type)
    t = g_hash_table_new_full((GHashFunc) g_long_hash, (GEqualFunc) g_long_equal, g_free, func);
  else
    t = g_hash_table_new_full((GHashFunc) g_str_hash, (GEqualFunc) g_str_equal, free, g_free);
  return t;
}

// Inserts a key and a value
int hash_insert(long key, void * value, HASHTABLE h) {
  glong * gkey = g_new(glong,1);
  *gkey = key;
  gboolean flag = g_hash_table_insert(h,gkey,value);
  return flag;
}

int str_hash_insert(char * key, long * value, HASHTABLE h) {
  gboolean flag = g_hash_table_insert(h,key,value);
  return flag;
}

long * str_hash_get(char * key, HASHTABLE h) {
  long * result = g_hash_table_lookup(h,key);
  return result;
}

// Get content from Hash
void * hash_get(long id, HASHTABLE h) {
  glong * key = g_new(glong,1);
  *key = id;
  void * temp = g_hash_table_lookup(h,key);
  g_free(key);
  return temp;
}

void hash_toHeap(gpointer key, gpointer value, gpointer user_data) {
  LONG_USER u = (LONG_USER) value;
  HEAP h = (HEAP) user_data;
  heap_insert(h,u);
}

void hash_freeTable(HASHTABLE h) {
  g_hash_table_destroy(h);
}

void hash_forEach(HASHTABLE h, void * func, void * data) {
  g_hash_table_foreach(h,func,data);
}

gboolean g_long_equal (gconstpointer v1, gconstpointer v2) {
  return (*((glong *)v1) == (*(glong *)v2));
}

glong g_long_hash (gconstpointer v) {
  return (*(glong *)v);
}

void hash_increment(HASHTABLE h, long key) {
  int* temp = (int*) hash_get(key, h);

  int* n = (int*) malloc (sizeof(int));

  if (n) {
    if (temp) *n = *temp + 1;
    else *n = 1;

    hash_insert(key, n, h);
  }
}

LIST hash_getKeys(HASHTABLE h) {
  return (LIST) g_hash_table_get_keys(h);
}

void hash_freeKeysList (LIST l) {
  g_list_free((GList *) l);
}
