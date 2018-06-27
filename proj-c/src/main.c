#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <glib.h>
#include <stdlib.h>

#include "common.h"
#include "date.h"
#include "pair.h"
#include "list.h"
#include "linked_list.h"
#include "post.h"
#include "answer.h"
#include "question.h"
#include "load.h"
#include "interface.h"
#include "heap.h"
#include "hash.h"
//#include "luis.h"

#define TESTSIZE 100

void miguel_load(TAD_community com) {
  clock_t start = clock();
  com = load(com, "./XML Files/ubuntu/");
  //com = load(com, "./XML Files/android/");
  clock_t end = clock();

  printf("Time taken: %fs\n",((float)(end-start) / CLOCKS_PER_SEC));
}

void miguel() {

  TAD_community com = init();
  puts("Inicialized!");

  miguel_load(com);

  Date sq3 = createDate(1, 1, 2014);
  Date eq3 = createDate(31, 12, 2014);

  Date sq4 = createDate(1, 3, 2013);
  Date eq4 = createDate(31, 3, 2013);

  Date sq6 = createDate(1, 5, 2013);
  Date eq6 = createDate(6, 5, 2013);

  Date sq7 = createDate(1, 1, 2012);
  Date eq7 = createDate(31, 12, 2012);

  Date sq11 = createDate(1, 1, 2014);
  Date eq11 = createDate(31, 12, 2014);

  clock_t t1 = clock();
  LONG_pair pair3 = total_posts(com, sq3, eq3);
  clock_t t2 = clock();
  LONG_list list4 = questions_with_tag(com, "package-management", sq4, eq4);
  clock_t t3 = clock();
  LONG_list list6 = most_voted_answers(com, 50, sq6, eq6);
  clock_t t4 = clock();
  LONG_list list7 = most_answered_questions(com, 100, sq7, eq7);
  clock_t t5 = clock();
  LONG_list list11 = most_used_best_rep(com, 10, sq11, eq11);
  clock_t t6 = clock();

  printf("Time Q3: %fs\n",((float)(t2-t1) / CLOCKS_PER_SEC));
  printf("Time Q4: %fs\n",((float)(t3-t2) / CLOCKS_PER_SEC));
  printf("Time Q6: %fs\n",((float)(t4-t3) / CLOCKS_PER_SEC));
  printf("Time Q7: %fs\n",((float)(t5-t4) / CLOCKS_PER_SEC));
  printf("Time Q11: %fs\n",((float)(t6-t5) / CLOCKS_PER_SEC));

  puts("::::::::::::::::::::::::: QUERY 3 ::::::::::::::::::::::::::");
  print_pair(pair3);
  puts("::::::::::::::::::::::::: QUERY 4 ::::::::::::::::::::::::::");
  print_list(list4);
  puts("::::::::::::::::::::::::: QUERY 6 ::::::::::::::::::::::::::");
  print_list(list6);
  puts("::::::::::::::::::::::::: QUERY 7 ::::::::::::::::::::::::::");
  print_list(list7);
  puts("::::::::::::::::::::::::: QUERY 11 ::::::::::::::::::::::::::");
  print_list(list11);

  free_date(sq3);
  free_date(eq3);
  free_date(sq4);
  free_date(eq4);
  free_date(sq6);
  free_date(eq6);
  free_date(sq7);
  free_date(eq7);
  free_date(sq11);
  free_date(eq11);

  free_long_pair(pair3);
  free_list(list4);
  free_list(list6);
  free_list(list7);
  free_list(list11);

  clean(com);
}

int main(int argc, char * argv[]){
    //if(argc > 1) luis();
    miguel();
    //miguel_test();
    return 0;
}
