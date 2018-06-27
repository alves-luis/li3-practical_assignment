#include <libxml/parser.h>
#include <stdio.h>
#include <date.h>
#include "interface.h"
#include "parser.h"
#include <string.h>
#include <glib.h>
#include "pair.h"
#include "post_time.h"
#include "post.h"
#include "users.h"
#include "user.h"
#include "tag.h"
#include "simple_list.h"

struct TCD_community{
  GHashTable* users;
  GHashTable* posts;
  GHashTable* tags;
  POST_TIME postsT;
  GArray* array;
};

gint arrayCompFun(gconstpointer a, gconstpointer b) {
  USERS* x = (USERS*) a;
  USERS* y = (USERS*) b;
  if (get_users_post_number(*x) > get_users_post_number(*y)) return -1;
  if (get_users_post_number(*x) < get_users_post_number(*y)) return 1;
  return 0;
}

void hash2array(gpointer key, gpointer value, gpointer data){
  g_array_append_val(data, value);
}

void create_array_top_users(TAD_community com){
  g_hash_table_foreach(com->users,hash2array,com->array);
  g_array_sort(com->array,arrayCompFun);

}

int verify_year (POST_TIME posts, int year) {
  if (!posts) return 0;
  POST_TIME aux = posts;
  int flag = 0;
  while (aux && !flag) {
    if (get_posts_year(aux) == year || get_posts_year(aux) == -1) {
      if (get_posts_year(aux) == -1) set_posts_year(aux,year);
      flag = 1;
    }
    aux = get_posts_next(aux);
  }
  return flag;
}

SHORT_DATE insert_date_to_array (long id, int hour, SHORT_DATE day){
  SHORT_DATE new_date = create_short_date();
  set_new_date_id(new_date,id);
  set_new_date_hour(new_date,hour);


  int flag = 0;
  if (!day) {
    set_new_date_next(new_date,NULL);

    return new_date;
  }
  else {
    if (get_new_day_hour(day) < hour){
      set_new_date_next(new_date,day);

      return new_date;
    }
    else {
      SHORT_DATE aux;
      aux = day;
      while (get_new_day_next(aux) && !flag) {
        if (get_new_day_hour(get_new_day_next(aux)) < hour){
          set_new_date_next(new_date,get_new_day_next(aux));
          set_new_date_next(aux,new_date);
          flag = 1;
        }
        aux = get_new_day_next(aux);
      }
      if (!flag) {
        set_new_date_next(new_date, NULL);
        set_new_date_next(aux, new_date) ;
      }

      return day;
    }
  }
}


POST_TIME insert_date (long id, int year, int month, int day, int hour, POST_TIME* posts){
    POST_TIME aux,aux1;
    int flag = 0;
    if (!verify_year((*posts), year)){
        (*posts) = create_year((*posts), year);
        }
    aux = (*posts);
    aux1=(*posts);
    while(aux1){
      aux1= get_posts_next(aux1);

    }
    while (aux && !flag) {
        if (get_posts_year(aux) == year)
            flag = 1;
        else
            aux = get_posts_next(aux);
    }

    set_posts_day_indice(aux,((month-1)*31) + day, insert_date_to_array (id, hour, get_new_date_from_post(aux,((month - 1)*31) + day)));
    return (*posts);
}

TAD_community init(){
    TAD_community total = malloc(sizeof(struct TCD_community));

    GHashTable* g_hash_table_posts = g_hash_table_new_full(g_int_hash, g_int_equal , NULL , &free_post);
    GHashTable* g_hash_table_users = g_hash_table_new_full(g_int_hash, g_int_equal , NULL,  &free_users );
    GHashTable* g_hash_table_tags = g_hash_table_new_full(g_str_hash, g_str_equal,NULL,&free_tags);
    POST_TIME temp = create_post_time();
    GArray * userPostCount = g_array_new(FALSE,FALSE,sizeof(USERS));


    total -> tags = g_hash_table_tags;
    total -> posts = g_hash_table_posts;
    total -> users = g_hash_table_users;
    total -> postsT = temp;
    total -> array = userPostCount;

    return total;
}


TAD_community load(TAD_community com, char* dump_path){
      char buffer[200];

      sprintf(buffer,"%s/Users.xml",dump_path);
      parser_users(com->users,buffer);
      sprintf(buffer,"%s/Posts.xml",dump_path);
      parser_post(com->posts,com->users,&(com->postsT),buffer);
      sprintf(buffer,"%s/Tags.xml",dump_path);
      parser_tag(com->tags,buffer);
      create_array_top_users(com);
      return com;
}

//QUERY 1
STR_pair info_from_post(TAD_community com, long id){
    POST p = g_hash_table_lookup(com->posts,&id);
    if(!p) return NULL;
    if(get_post_type(p) == 2){
       id = get_post_parent_id(p);
       p = g_hash_table_lookup(com->posts,&id);
       if(!p) return NULL;
    }
    char* titulo = get_post_title(p);
    long t = get_post_user_id(p);
    USERS u = g_hash_table_lookup(com->users,&t);
    char *nome = get_users_nickname(u);
    STR_pair final = create_str_pair(titulo,nome);

  return final;
}

//QUERY 2
LONG_list top_most_active(TAD_community com,  int N){
  LONG_list final = create_list(N);
  int i;
  for (i = 0; i <N && i<g_hash_table_size(com->users); i++)
    set_list(final,i,get_users_id(g_array_index(com->array, USERS, i)));
  for (; i < N ; i++)
    set_list(final,i,-1);
  return final;
}

//QUERY3
LONG_pair total_posts(TAD_community com, Date dataI, Date dataF){
    POST_TIME aux = com -> postsT;
    LONG_pair final = create_long_pair(0,0);
    long prim = 0;
    long sec = 0;


    if(get_year(dataF) < get_posts_year(aux)){
      while(aux && get_posts_year(aux) != get_year(dataF)){
        aux = get_posts_next(aux);
      }
    }

    SHORT_DATE auxSD;
    int i;
    int max;


    while(aux && get_posts_year(aux) >= get_year(dataI) && get_posts_year(aux) <= get_year(dataF)){

      i = get_posts_year(aux) == get_year(dataF) ? (((get_month(dataF)-1)* 31 ) + get_day(dataF)) : 372;
      max = get_posts_year(aux) == get_year(dataI) ? ((get_month(dataI)-1)*31 + get_day(dataI)) : 0 ;

      for(; i >= max; i--){

        auxSD = get_new_date_from_post(aux,i);
          while(auxSD){

            if(get_hash_post_type(com -> posts,get_new_day_id(auxSD)) == 1)
                prim ++;
            else if(get_hash_post_type(com -> posts,get_new_day_id(auxSD)) == 2)
                sec ++;

            auxSD = get_new_day_next(auxSD);
          }
      }
      aux = get_posts_next(aux);
    }


    set_fst_long(final,prim);
    set_snd_long(final,sec);
    return final;
}

//QUERY4
LONG_list questions_with_tag (TAD_community com, char* tag, Date dataI, Date dataF){
    TAG t = g_hash_table_lookup(com->tags,tag);
    if(!t) return NULL;
    POST_TIME aux = com -> postsT;
    int indice = 0;
    long array[get_tag_count(t)];
    char* postsTags;
    char buf[100];
    SHORT_DATE auxSD;
    int i;
    int max;

    if(get_year(dataF) < get_posts_year(aux)){
      while(aux && get_posts_year(aux) != get_year(dataF))
        aux = get_posts_next(aux);
    }

    while(aux && get_posts_year(aux) >= get_year(dataI) && get_posts_year(aux) <= get_year(dataF)){

      i = get_posts_year(aux) == get_year(dataF) ? (((get_month(dataF)-1)* 31 ) + get_day(dataF)) : 372;
      max = get_posts_year(aux) == get_year(dataI) ? ((get_month(dataI)-1)*31 + get_day(dataI)) : 0 ;

      for(; i >= max; i--){

      auxSD = get_new_date_from_post(aux,i);
          while(auxSD){

            postsTags = get_hash_post_tags(com -> posts,get_new_day_id(auxSD));

            if(postsTags){
              snprintf(buf, sizeof buf, "<%s>", tag);
              if(strstr(postsTags,buf)){
                array[indice] = get_new_day_id(auxSD);
                indice++;
              }
            }
            auxSD = get_new_day_next(auxSD);
          }
       }
      aux = get_posts_next(aux);
    }

    LONG_list final = create_list(indice);
    for ( i = indice-1 ; i >= 0 ; i--)
      set_list (final,i, array[i]);

    return final;
}

//QUERY5
USER get_user_info (TAD_community com,long id){
    USERS u = g_hash_table_lookup(com->users,&id);
    if(!u) return NULL;
    POST_TIME aux = com -> postsT;
    int indice = 0;
    int count = 0;
    long array[10];
    SHORT_DATE auxSD;
    int i;

    while(aux){
      for(i = 372; i >= 0; i--){
        auxSD = get_new_date_from_post(aux,i);
          while(auxSD){
            if(get_hash_post_user_id(com->posts,get_new_day_id(auxSD)) == id){
              if (count < 10)  {
                array[indice++] = get_new_day_id(auxSD);
                count++;
              }
            }
            auxSD = get_new_day_next(auxSD);
          }
      }
      aux = get_posts_next(aux);
    }

    for(i=indice;i<10;i++)
        array[i] = -1;

    char* bio = get_users_short_bio(u);
    USER final = create_user(bio,array);

    return final;
}

//QUERY6
LONG_list most_voted_answers (TAD_community com, int N, Date dataI, Date dataF){
  POST_TIME aux = com -> postsT;

  long id;
  SHORT_DATE auxSD ;
  int i;
  int max;

  SIMPLE_LIST lista = create_simple_list();
  set_simple_list_id(lista,-2);
  set_simple_list_param(lista,-2);
  set_simple_list_next(lista, NULL);

  if(get_year(dataF) < get_posts_year(aux)){
    while(aux && get_posts_year(aux) != get_year(dataF)){
      aux = get_posts_next(aux);
    }
  }

  while(aux && get_posts_year(aux) >= get_year(dataI) && get_posts_year(aux) <= get_year(dataF)){

    i = get_posts_year(aux) == get_year(dataF) ? (((get_month(dataF)-1)* 31 ) + get_day(dataF)) : 372;
    max = get_posts_year(aux) == get_year(dataI) ? ((get_month(dataI)-1)*31 + get_day(dataI)) : 0 ;

    for(; i >= max; i--){

      auxSD = get_new_date_from_post(aux,i);
      while(auxSD){
        id = get_new_day_id(auxSD);
        if(get_hash_post_type(com->posts,id) == 2){

          lista = insere_lista_score(lista,id,get_hash_post_score(com->posts,id),N);
        }
        auxSD = get_new_day_next(auxSD);
      }
    }

    aux = get_posts_next(aux);
  }

  SIMPLE_LIST auxS = lista;
  LONG_list final = create_list(N);
  int in = 0;
  while(auxS && in < N){
    set_list(final,in,get_simple_list_id(auxS));
    auxS = get_simple_list_next(auxS);
    in++;
  }
  free_lista_score(lista);

  return final;

}

//QUERY7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end) {
  POST_TIME aux = com -> postsT;
  long id;
  SHORT_DATE auxSD ;
  int i;
  int max;
  SIMPLE_LIST lista = create_simple_list();
  set_simple_list_id(lista,-2);
  set_simple_list_param(lista,-2);
  set_simple_list_next(lista, NULL);

  if (get_year(end) < get_posts_year(aux)){
    while (aux && get_posts_year(aux) != get_year(end)) {
      aux = get_posts_next(aux);
    }
  }

  while (aux && get_posts_year(aux) >= get_year(begin) && get_posts_year(aux) <= get_year(end)) {
    i = get_posts_year(aux) == get_year(end) ? (((get_month(end)-1)* 31 ) + get_day(end)) : 372;
    max = get_posts_year(aux) == get_year(begin) ? ((get_month(begin)-1)*31 + get_day(begin)) : 0 ;
    for (; i >= max; i--) {
      auxSD = get_new_date_from_post(aux,i);
      while(auxSD) {
        id = get_new_day_id(auxSD);
        if (get_hash_post_type(com->posts, id) == 1) {
          lista = insere_lista_score(lista,id, get_hash_post_reply_number(com->posts,id), N);
        }
        else {
          increment_post_reply_number(g_hash_table_lookup(com->posts, get_post_parent_id_pointer(g_hash_table_lookup(com->posts, &id))));
        }
        auxSD = get_new_day_next(auxSD);
      }
    }
    aux = get_posts_next(aux);
  }
  SIMPLE_LIST auxS = lista;
  LONG_list final = create_list(N);
  int in = 0;
  while(auxS && in < N){
    set_list(final,in,get_simple_list_id(auxS));
    auxS = get_simple_list_next(auxS);
    in++;
  }
  free_lista_score(lista);

  return final;
}

//QUERY8
LONG_list contains_word (TAD_community com, char* word, int N){

      POST_TIME aux = com -> postsT;
      int indice = 0;
      int count = 0;
      long array[N];
      int id;
      SHORT_DATE auxSD ;
      int i;



      while(aux){
        for(i = 372; i >= 0; i--){

        auxSD = get_new_date_from_post(aux,i);
            while(auxSD){
              id = get_new_day_id(auxSD);
              if(get_hash_post_type(com->posts,id) == 1){
              if(strstr (get_hash_post_title(com->posts,id), word)){
              if (count < N) {
                array[indice++] = get_new_day_id(auxSD);
                count++;
              }
              }
            }
              auxSD = get_new_day_next(auxSD);
            }
            }

            aux = get_posts_next(aux);
         }

         LONG_list final = create_list(N);
         for ( i = indice-1 ; i >= 0 ; i--){
           set_list (final,i, array[i]);
         }


        for (int j = indice ; j < N ; j++) {
              set_list (final,j, -1);
          }

         return final;
}

//QUERY9
LONG_list both_participated(TAD_community com, long id1, long id2, int N) {
  GHashTable* query9 = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, &free_short_post);
  POST p;
  SHORT_POST s;
  POST_TIME aux = com -> postsT;
  SHORT_DATE aux2;
  long temp[N], id;
  int i, counter = 0, user_id;
  while(aux && counter < N) {
  i = 372;
    for(get_new_date_from_post(aux,i);i > 0 && counter < N;i--){
      aux2 = get_new_date_from_post(aux,i);
      while(aux2 && counter < N) {
        id = get_new_day_id(aux2);
        p = g_hash_table_lookup(com->posts, &id);
        user_id = get_post_user_id(p);
        if (get_post_type(p) == 1) {
          s = g_hash_table_lookup(query9, &id);
          if (s) {
            if (user_id == id1) {
              set_short_post_user1_id(s, id1);
            }
            else if (user_id == id2) {
              set_short_post_user2_id(s, id2);
            }
            if (get_short_post_user1_id(s) == id1 && get_short_post_user2_id(s) == id2) {
              temp[counter] = id;
              counter++;
            }
          }
        }
        else {
          s = g_hash_table_lookup(query9, get_post_parent_id_pointer(p));
          if (s) {
            if (user_id == id1) {
              set_short_post_user1_id(s, id1);
            }
            else if (user_id == id2) {
              set_short_post_user2_id(s, id2);
            }
          }
          else {
            if (user_id == id1) {
              s = create_incomplete_short_post_user1(get_post_parent_id(p), id1);
              g_hash_table_insert(query9, get_post_parent_id_pointer(p), s);
            }
            else if (user_id == id2) {
              s = create_incomplete_short_post_user2(get_post_parent_id(p), id2);
              g_hash_table_insert(query9, get_post_parent_id_pointer(p), s);
            }
          }
        }
        aux2 = get_new_day_next(aux2);
      }
    }
    aux = get_posts_next(aux);
  }
  LONG_list l = create_list(N);
  for(i = 0; i < counter; i++) {
    set_list(l, i, temp[i]);
  }
  for (; i < N ; i++) {
    set_list (l,i, -1);
  }
  g_hash_table_destroy(query9);

  return l;
}

//QUERY10
long better_answer(TAD_community com, long n) {
  return get_post_best_answer_id(g_hash_table_lookup(com->posts, &n));
}


TAD_community clean(TAD_community com){
  g_hash_table_destroy(com->users);
  g_hash_table_destroy(com->posts);
  g_hash_table_destroy(com->tags);
  free_post_by_time(com->postsT);
  g_array_free(com->array,TRUE);
  return com;
}


























SIMPLE_LIST organiza_top_users(SIMPLE_LIST lista,long id, int param, int N){
  SIMPLE_LIST novo = create_simple_list();
  set_simple_list_id(novo,id);
  set_simple_list_param(novo, param);
  int count = 0;
  int flag = 0;

  if(get_simple_list_param(lista) == -2 && get_simple_list_id(lista) == -2){
    free_lista_score(lista);
    set_simple_list_next(novo,NULL);
    return novo;
  }
  if(get_simple_list_param(lista) < param){
    set_simple_list_next(novo,lista);
    return novo;
  }
  else{
    SIMPLE_LIST aux = lista;
    while(get_simple_list_next(aux) && !flag && count < N){
      if(get_simple_list_param(get_simple_list_next(aux)) < param) {
        set_simple_list_next(novo,get_simple_list_next(aux));
        set_simple_list_next(aux,novo);
        flag = 1;
      }
      count++;
      aux = get_simple_list_next(aux);
    }
    if(!flag && count < N){
      set_simple_list_next(novo,NULL);
      set_simple_list_next(aux,novo);
      flag = 1;
    }
    if (!flag) {
      free(novo);
    }
    return lista;

  }
}

int existeTopUser(SIMPLE_LIST lista,long id){
    SIMPLE_LIST aux = lista;
    while(aux){
      if(get_simple_list_id(aux) == id) return 1;
      aux = get_simple_list_next(aux);
    }
    return 0;
}

SIMPLE_LIST top_users (TAD_community com, int N, Date dataI, Date dataF){
  POST_TIME aux = com -> postsT;

  SHORT_DATE auxSD ;
  int i;
  int max;
  long pid;

  SIMPLE_LIST lista = create_simple_list();
  set_simple_list_id(lista,-2);
  set_simple_list_param(lista,-2);
  set_simple_list_next(lista, NULL);

  if(get_year(dataF) < get_posts_year(aux)){
    while(aux && get_posts_year(aux) != get_year(dataF)){
      aux = get_posts_next(aux);
    }
  }

  while(aux && get_posts_year(aux) >= get_year(dataI) && get_posts_year(aux) <= get_year(dataF)){

    i = get_posts_year(aux) == get_year(dataF) ? (((get_month(dataF)-1)* 31 ) + get_day(dataF)) : 372;
    max = get_posts_year(aux) == get_year(dataI) ? ((get_month(dataI)-1)*31 + get_day(dataI)) : 0 ;

    for(; i >= max; i--){

      auxSD = get_new_date_from_post(aux,i);
      while(auxSD){
         pid = get_new_day_id(auxSD);
         POST p = g_hash_table_lookup(com->posts , &pid );
         USERS u = g_hash_table_lookup(com->users, get_post_user_id_pointer(p));

         if(!existeTopUser(lista,get_users_id(u)))
          lista = insere_lista_score(lista,get_users_id(u),get_users_rep(u),N);

        auxSD = get_new_day_next(auxSD);
      }
    }

    aux = get_posts_next(aux);
  }

  SIMPLE_LIST auxS = lista;
  int in = 0;
  while(auxS && in < N){
    auxS = get_simple_list_next(auxS);
    in++;
  }


  return lista;
}


void insert_tag_hash(TAD_community com, GHashTable* hash, char* string, int inicio, int fim){
  int i = 0, length = fim - inicio;
  char* tag = malloc(sizeof(char) * (length + 2));
  TAG t;
  while ( i <= length ) {
    tag[i] = string[inicio];
    i++;
    inicio++;
  }
  tag[i] = '\0';
  t = g_hash_table_lookup(hash, tag);
  if (t)
    increment_tag(t);
  else {
    t = create_incomplete_tag(tag,get_tag_id(g_hash_table_lookup(com->tags,tag)));
    g_hash_table_insert(hash, tag, t);
  }
  free(tag);
}

void insert_tags(TAD_community com, GHashTable* hash_tags, char* tags){
  int i = 1, flag = 0, inicio, fim, length = strlen(tags);
  while (tags[i] != '\0') {
    if (flag == 0) {
      inicio = i;
      flag = 1;
    }
    if (tags[i] == '>') {
      fim = i-1;
      insert_tag_hash(com,hash_tags, tags, inicio, fim);
      if (length > (i + 2)) {
        i++;
        flag = 0;
      }
      else return;
    }
  i++;
  }
}

void insert_tag_list(gpointer key, gpointer value, gpointer data){
      SIMPLE_LIST final = insere_lista_score(get_top_tag_list(data),get_tag_id(value),get_tag_count(value),get_top_tag_size(data));
      set_top_tag_list(data,final);


}

LONG_list most_used_best_rep(TAD_community com, int N, Date dataI, Date dataF){
  POST_TIME aux = com -> postsT;
  SHORT_DATE auxSD ;
  SIMPLE_LIST auxU, best_users = top_users(com,N,dataI,dataF);
  POST p;
  GHashTable* hash_tags = g_hash_table_new_full(g_int_hash, g_int_equal , NULL , &free_tags);

  long id;
  int i,flag,count;
  int max;
  if(get_year(dataF) < get_posts_year(aux)){
    while(aux && get_posts_year(aux) != get_year(dataF)){
      aux = get_posts_next(aux);
    }
  }
  while(aux && get_posts_year(aux) >= get_year(dataI) && get_posts_year(aux) <= get_year(dataF)){
    i = get_posts_year(aux) == get_year(dataF) ? (((get_month(dataF)-1)* 31 ) + get_day(dataF)) : 372;
    max = get_posts_year(aux) == get_year(dataI) ? ((get_month(dataI)-1)*31 + get_day(dataI)) : 0 ;
    for(; i >= max; i--){

      auxSD = get_new_date_from_post(aux,i);
      while(auxSD){
        flag=0;
        id = get_new_day_id(auxSD);
        p = g_hash_table_lookup(com->posts,&id);
        if(get_post_type(p) == 1){
          auxU = best_users;
          count = 0;
          while(auxU && count < N){
            if(get_post_user_id(p) == get_simple_list_id(auxU)) flag = 1;
            count++;
          }
          if(flag){
            insert_tags(com,hash_tags,get_post_tags(p));
          }
        }
        auxSD = get_new_day_next(auxSD);
      }
    }

    aux = get_posts_next(aux);
  }

  SIMPLE_LIST final = create_simple_list();
  set_simple_list_id(final,-2);
  set_simple_list_param(final,-2);
  set_simple_list_next(final, NULL);
  TOP_TAG t = create_top_tag(N,final);
  g_hash_table_foreach(hash_tags,insert_tag_list,t);

  SIMPLE_LIST auxaux = final;
  LONG_list pv = create_list(N);
  for(int i = 0; i< N;i++){
    if(auxaux){
      set_list(pv,i,get_simple_list_id(auxaux));
      auxaux = get_simple_list_next(auxaux);
    }
    else set_list(pv,i,-1);
  }
  free_lista_score(get_top_tag_list(t));
  free_lista_score(best_users);
  g_hash_table_destroy(hash_tags);
  free(t);
  return pv;
}
