#include <date.h>
#include <stdio.h>
#include <parser.h>
#include <interface.h>
#include <glib.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pair.h>
#include "user.h"
#include "simple_list.h"
#include "post_time.h"


void testes(TAD_community com){

	Date Q3T1i = createDate(1,7,2016);
	Date Q3T1f = createDate(31,7,2016);
	Date Q3T2i = createDate(1,1,2014);
	Date Q3T2f = createDate(31,12,2014);
	Date Q4T1i = createDate(1,3,2013);
	Date Q4T1f = createDate(31,3,2013);
	Date Q4T2i = createDate(1,1,2014);
	Date Q4T2f = createDate(31,1,2014);
	Date Q6T1i = createDate(1,11,2015);
	Date Q6T1f = createDate(30,11,2015);
	Date Q6T2i = createDate(1,5,2013);
	Date Q6T2f = createDate(6,5,2013);
	Date Q7T1i = createDate(1,8,2014);
	Date Q7T1f = createDate(11,8,2014);
	Date Q7T2i = createDate(1,1,2012);
	Date Q7T2f = createDate(31,12,2012);
	Date Q11T1i = createDate(1,11,2013);
	Date Q11T1f = createDate(30,11,2013);
	Date Q11T2i = createDate(1,1,2014);
	Date Q11T2f = createDate(31,12,2014);

	printf("---------- QUERY 1-------\n");

	STR_pair query1a = info_from_post(com,801049);
	STR_pair query1b = info_from_post(com,796430);
	//printf("v1 -> %s\n", get_fst_str(query1a));
	//printf("v1 -> %s\n", get_snd_str(query1a));
	//printf("v2 -> %s\n", get_fst_str(query1b));
	//printf("v2 -> %s\n", get_snd_str(query1b));
	free_str_pair(query1a);
	free_str_pair(query1b);

	printf("---------- QUERY 2-------\n");

	LONG_list query2a =  top_most_active(com, 10);
	LONG_list query2b =  top_most_active(com, 100);
	//for(int i = 0; i<10;i++) printf("v1 -> %ld\n",get_list(query2a,i));
	//for(int i = 0; i<100;i++) printf("v2 -> %ld\n",get_list(query2b,i));
	free_list(query2a);
	free_list(query2b);


	printf("---------- QUERY 3-------\n");

	LONG_pair query3a = total_posts(com,Q3T1i,Q3T1f);
	LONG_pair query3b = total_posts(com,Q3T2i,Q3T2f);
	//printf("v1 -> PERGUNTAS %ld RESPOSTAS %ld\n", get_fst_long(query3a),get_snd_long(query3a));
	//printf("v2 -> PERGUNTAS %ld RESPOSTAS %ld\n", get_fst_long(query3b),get_snd_long(query3b));
	free_long_pair(query3a);
	free_long_pair(query3b);

	printf("---------- QUERY 4-------\n");

	LONG_list query4a = questions_with_tag(com,"package-management",Q4T1i,Q4T1f);
	LONG_list query4b = questions_with_tag(com,"nautilus"          ,Q4T2i,Q4T2f);
	//for(int i = 0;i<10;i++) printf("v1 -> %ld\n", get_list(query4a,i));
	//for(int i = 0;i<10;i++) printf("v2 -> %ld\n", get_list(query4b,i));
	free_list(query4a);
	free_list(query4b);

	printf("---------- QUERY 5-------\n");

	USER u1 = get_user_info(com,15811);
	USER u2 = get_user_info(com,449);
	long* query5a = get_10_latest_posts(u1);
	long* query5b = get_10_latest_posts(u2);
	//printf("v1 -> %s\n", get_bio(u1));
	//for(int i = 0; i<10; i++) printf("v1 -> %ld\n", query5a[i]);
	//printf("v2 -> %s\n", get_bio(u2));
	//for(int i = 0; i<10; i++) printf("v2 -> %ld\n", query5b[i]);
	free(query5a);
	free(query5b);
	free_user(u1);
	free_user(u2);

	printf("---------- QUERY 6-------\n");

	LONG_list query6a = most_voted_answers(com,5,Q6T1i,Q6T1f);
	LONG_list query6b = most_voted_answers(com,50,Q6T2i,Q6T2f);
	//for(int i = 0;i<5;i++)	printf("v1 -> %ld\n",get_list(query6a,i));
	//for(int i = 0;i<50;i++)	printf("v2 -> %ld\n",get_list(query6b,i));
	free_list(query6a);
	free_list(query6b);

	printf("---------- QUERY 7-------\n");

	LONG_list query7a = most_answered_questions(com,10,Q7T1i,Q7T1f);
	LONG_list query7b = most_answered_questions(com,100,Q7T2i,Q7T2f);
	//for(int i = 0;i<10;i++) 	printf("v1 -> %ld\n",get_list(query7a,i));
	//for(int i = 0;i<100;i++)  printf("v2 -> %ld\n",get_list(query7b,i));
	free_list(query7a);
	free_list(query7b);

	printf("---------- QUERY 8-------\n");

	LONG_list query8a = contains_word(com , "kde" , 10);
	LONG_list query8b = contains_word(com , "glib" , 10);
	//for(int i = 0;i<10;i++)	printf("v1 -> %ld\n",get_list(query8a,i));
	//for(int i = 0;i<10;i++)	printf("v2 -> %ld\n",get_list(query8b,i));
	free_list(query8a);
	free_list(query8b);

	printf("---------- QUERY 9-------\n");

	LONG_list query9a = both_participated(com , 87 , 5691 , 10);
	LONG_list query9b = both_participated(com , 455, 253 , 5);
	//for(int i = 0;i<10;i++)	printf("v1 -> %ld\n",get_list(query9a,i));
	//for(int i = 0;i<5;i++)	printf("v2 -> %ld\n",get_list(query9b,i));
	free_list(query9a);
	free_list(query9b);

	printf("---------- QUERY 10-------\n");

	long query10a = better_answer(com,30334);
	long query10b = better_answer(com,5942);
	//printf("v1 ->  %ld\n", query10a);
	//printf("v1 ->  %ld\n", query10b);

	printf("---------- QUERY 11-------\n");

	LONG_list query11a = most_used_best_rep(com,5,Q11T1i,Q11T1f);
	LONG_list query11b = most_used_best_rep(com,10,Q11T2i,Q11T2f);
	//for(int i = 0;i<5;i++)	printf("v1 -> %ld\n",get_list(query11a,i));
	//for(int i = 0;i<10;i++)	printf("v2 -> %ld\n",get_list(query11b,i));
	free_list(query11a);
	free_list(query11b);

	printf("-------------------------\n");

	free_date(Q3T1i);
	free_date(Q3T1f);
	free_date(Q3T2i);
	free_date(Q3T2f);
	free_date(Q4T1i);
	free_date(Q4T1f);
	free_date(Q4T2i);
	free_date(Q4T2f);
	free_date(Q6T1i);
	free_date(Q6T1f);
	free_date(Q6T2i);
	free_date(Q6T2f);
	free_date(Q7T1i);
	free_date(Q7T1f);
	free_date(Q7T2i);
	free_date(Q7T2f);
	free_date(Q11T1i);
	free_date(Q11T1f);
	free_date(Q11T2i);
	free_date(Q11T2f);
}

int main(){
	TAD_community com = init();


	com = load(com,"./ubuntu");


	testes(com);




	com = clean(com);
	free(com);


  return 0;
}
