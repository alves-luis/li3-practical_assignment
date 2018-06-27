#include <libxml/parser.h>
#include <stdio.h>
#include <date.h>
#include "parser.h"
#include <string.h>
#include <glib.h>
#include "pair.h"
#include "common.h"
#include "tag.h"
#include "interface.h"
#include "post.h"
#include "users.h"
#include "user.h"
#include "simple_list.h"
#include "post_time.h"



POST_TIME insert_date (long id, int year, int month, int day, int horas, POST_TIME* posts);
int insert_date_to_array (long sid,int sdata, SHORT_DATE day);

long get_hash_post_user_id(GHashTable* hash_post, long id) {
    return get_post_user_id(g_hash_table_lookup(hash_post,&id));
}

int get_hash_post_score(GHashTable* hash_post, long id){
 return get_post_score(g_hash_table_lookup(hash_post,&id));
}

int get_hash_post_type (GHashTable* hash_post, long id) {
  POST p = g_hash_table_lookup(hash_post, &id);

  if (get_post_parent_id(p) == -1) return 1;
  return 2;
}

char* get_hash_post_title(GHashTable* hash_post,long id) {
    return get_post_title(g_hash_table_lookup(hash_post,&id));
}

char* get_hash_post_tags(GHashTable* hash_post, long id) {
    return get_post_tags(g_hash_table_lookup(hash_post,&id));
}

int get_hash_post_reply_number(GHashTable* hash_post, long id){
  return get_post_reply_number(g_hash_table_lookup(hash_post,&id));
}


int parser_post (GHashTable* hash_post, GHashTable* hash_users, POST_TIME* posts, char* dump_path){
  xmlDocPtr doc = xmlParseFile(dump_path);
  xmlNodePtr cur = xmlDocGetRootElement(doc);

  int year, month, day, hour, min, sec, msec;
  unsigned int horas ;

  if (!cur)
    xmlFreeDoc (doc);
  else {
    cur = cur -> xmlChildrenNode;
    while (cur) {
      if (!xmlStrcmp(cur -> name, (const xmlChar * ) "row")) {

        unsigned char* title = xmlGetProp(cur, (const xmlChar *) "Title");
        unsigned char* tags = xmlGetProp(cur, (const xmlChar *) "Tags");
        unsigned char* date = xmlGetProp(cur, (const xmlChar *) "CreationDate");
        unsigned char* id = xmlGetProp(cur, (const xmlChar *) "Id");
        unsigned char* parent_id = xmlGetProp(cur, (const xmlChar *) "ParentId");
        unsigned char* user_id = xmlGetProp(cur, (const xmlChar *) "OwnerUserId");
        unsigned char* post_type_id = xmlGetProp(cur, (const xmlChar *) "PostTypeId"); // 1 resposta, 2 pergunta.
        unsigned char* score = xmlGetProp(cur, (const xmlChar *) "Score");
        unsigned char* comment_number = xmlGetProp(cur, (const xmlChar *) "CommentCount");

        if (atoi((const char*) post_type_id) == 1 || atoi((const char*) post_type_id)  == 2) {
          POST p = create_post(title, tags, id, parent_id, user_id, post_type_id, score, comment_number);

          if (date) sscanf((const char*)date, "%4d-%02d-%02dT%02d:%02d:%02d.%d", &year, &month, &day, &hour, &min, &sec, &msec);
          horas = (hour * 3600000) + (min * 60000) + (sec * 1000) + msec;

          (*posts) = insert_date(get_post_id(p), year, month, day, horas, posts);

          if (user_id) {
              USERS u = g_hash_table_lookup(hash_users, get_post_user_id_pointer(p));

              if (u) set_users_post_number(u, get_users_post_number(u)+1);
              else u = create_incomplete_users(user_id);
          }

          if (atoi((const char*)post_type_id) == 1) {
              POST aux = g_hash_table_lookup(hash_post, get_post_id_pointer(p));
              if (aux) complete_post(aux, p);
          }
          else {
            POST aux = g_hash_table_lookup(hash_post, get_post_parent_id_pointer(p));
            int answer_score = (get_post_score(p) * 65) + (get_users_rep(g_hash_table_lookup(hash_users, get_post_user_id_pointer(p))) * 25) + (get_post_reply_number(p) * 10);

            if (aux) {
              if (get_post_best_answer_score(g_hash_table_lookup(hash_post, get_post_parent_id_pointer(p))) < answer_score) {
                set_post_best_answer_id(g_hash_table_lookup(hash_post, get_post_parent_id_pointer(p)), get_post_id(p));
                set_post_best_answer_score(g_hash_table_lookup(hash_post, get_post_parent_id_pointer(p)), answer_score);
              }
            }
          }
          g_hash_table_insert (hash_post, get_post_id_pointer(p), p);
        }

        xmlFree(title);
        xmlFree(tags);
        xmlFree(date);
        xmlFree(id);
        xmlFree(user_id);
        xmlFree(post_type_id);
        xmlFree(score);
        xmlFree(comment_number);
        xmlFree(parent_id);
      }
      cur=cur->next;
    }
  }

  xmlFreeDoc(doc);
  return 0;
}

int parser_users (GHashTable* hash_users, char* dump_path){

  xmlDocPtr  doc = xmlParseFile(dump_path);
  xmlNodePtr cur = xmlDocGetRootElement(doc);

  if (!cur)
  xmlFreeDoc (doc);
  else {
    cur = cur -> xmlChildrenNode;
    while (cur) {
      if (!xmlStrcmp(cur -> name, (const xmlChar * ) "row")) {

        unsigned char* short_bio = xmlGetProp(cur, (const xmlChar *) "AboutMe");
        unsigned char* nickname = xmlGetProp(cur, (const xmlChar *) "DisplayName");
        unsigned char* id = xmlGetProp(cur, (const xmlChar *) "Id");
        unsigned char* rep = xmlGetProp(cur, (const xmlChar *) "Reputation");

        USERS u = create_users(short_bio, nickname, id, rep);

        g_hash_table_insert (hash_users, get_users_id_pointer(u), u);

        xmlFree(short_bio);
        xmlFree(nickname);
        xmlFree(id);
        xmlFree(rep);
      }
      cur=cur->next;
    }
  }
  xmlFreeDoc(doc);

  return 0;
}

int parser_tag (GHashTable* hash_tag, char* dump_path){

  xmlDocPtr  doc = xmlParseFile(dump_path);
  xmlNodePtr cur = xmlDocGetRootElement(doc);

  if (!cur)
  xmlFreeDoc (doc);
  else {
    cur = cur -> xmlChildrenNode;
    while (cur) {
      if (!xmlStrcmp(cur -> name, (const xmlChar * ) "row")) {

        unsigned char* tagname = xmlGetProp(cur, (const xmlChar *) "TagName");
        unsigned char* id = xmlGetProp(cur, (const xmlChar *) "Id");
        unsigned char* count = xmlGetProp(cur, (const xmlChar *) "Count");

        TAG t = create_tag(tagname, id, count);

        g_hash_table_insert(hash_tag, get_tag_name(t), t);

        xmlFree(tagname);
        xmlFree(id);
        xmlFree(count);

      }
      cur=cur->next;
    }
  }

  xmlFreeDoc(doc);

  return 0;
}
