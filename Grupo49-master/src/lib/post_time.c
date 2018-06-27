#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "post_time.h"


struct post_time {
    int year;
    SHORT_DATE day[373];
    struct post_time* next;
};

struct short_date {
    long id;
    int hour;
    struct short_date* next;
};

POST_TIME create_year (POST_TIME posts, int year) {
    POST_TIME new_posts = malloc(sizeof(struct post_time));
    int i;
    int flag = 0;
    POST_TIME aux;

    new_posts->year = year;
    aux = posts;

    for (i=0; i<373; i++)
        new_posts->day[i] = NULL;

    if (posts-> year < year) {
        new_posts -> next = posts;
        return new_posts;
        flag = 1;
    }
    else {
        while (aux->next && !flag) {
            if(aux->next->year < year){
                new_posts->next = aux->next;
                aux->next = new_posts;
                flag = 1;
            }
            aux = aux->next;
        }
        if (!flag) {
          new_posts->next = NULL;
          aux->next = new_posts;
          flag = 1;
        }
        return posts;
    }
    return NULL;
}

POST_TIME create_post_time(){
    POST_TIME new_posts = malloc(sizeof(struct post_time));

    new_posts -> year = -1;
    new_posts -> next = NULL;

    return new_posts;
}

SHORT_DATE create_short_date(){
    SHORT_DATE new_date = malloc(sizeof(struct short_date));

    return new_date;
}

int get_posts_year(POST_TIME posts){
    return (posts->year);
}

POST_TIME get_posts_next(POST_TIME posts){
    return (posts->next) ;
}

long get_new_day_id(SHORT_DATE new_date){
    return (new_date -> id);
}

int get_new_day_hour(SHORT_DATE new_date){
    return (new_date -> hour);
}

SHORT_DATE get_new_day_next(SHORT_DATE new_date){
    return (new_date -> next);
}

SHORT_DATE get_new_date_from_post(POST_TIME posts, int indice){
    return (posts->day[indice]);
}

void set_posts_day_indice(POST_TIME posts, int indice, SHORT_DATE day){
      posts -> day[indice] = day;
}

void set_posts_year(POST_TIME posts, int year){
    posts -> year = year;
}

void set_posts_next(POST_TIME posts,POST_TIME next){
    posts -> next = next ;
}

void set_new_date_id (SHORT_DATE new_date, long id){
    new_date -> id = id;
}

void set_new_date_hour (SHORT_DATE new_date, int hour){
    new_date -> hour = hour;
}

void set_new_date_next (SHORT_DATE new_date, SHORT_DATE nextq){
    new_date -> next = nextq;
}

void free_day (SHORT_DATE day){
  SHORT_DATE aux = day;
  SHORT_DATE auxfree;

  while(aux){
    auxfree = aux;
    aux = aux -> next;
    free(auxfree);
  }
}

void free_year(POST_TIME year){

  for(int i = 0; i < 373 ; i++)
    free_day(year->day[i]);

}

void free_post_by_time(POST_TIME postsT){
    POST_TIME aux = postsT;
    POST_TIME auxfree;
    
    while(aux){
      auxfree = aux;
      aux = aux -> next;
      free_year(auxfree);
      free(auxfree);
    }
}
