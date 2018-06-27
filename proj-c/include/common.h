#ifndef __MY_COMMON__
#define __MY_COMMON__
#include <glib.h>
char * mystrdup (const char *s);

/**
	* Opaque data struct that points to a struct post
*/
typedef struct post * POST;
typedef GSList * LIST;
typedef GSequence * SEQUENCE;
typedef struct long_user* LONG_USER;
typedef GHashTable *HASHTABLE;
typedef struct to_search *Search;
typedef struct to_search_tag *SEARCH_TAG;
typedef struct to_search_hash_long *SEARCH_HASH_LONG;
typedef struct to_search_hash_hash_long *SEARCH_2HASH_LONG;

#endif
