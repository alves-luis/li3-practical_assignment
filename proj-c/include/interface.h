#include "answer.h"
#include "array_pointers.h"
#include "common.h"
#include "community.h"
#include "date_time.h"
#include "date.h"
#include "hash.h"
#include "heap.h"
#include "list.h"
#include "linked_list.h"
#include "load.h"
#include "long_user.h"
#include "pair.h"
#include "parser.h"
#include "post.h"
#include "question.h"
#include "sequence.h"
#include "user.h"

typedef struct TCD_community * TAD_community;


TAD_community init();

// *************************** QUERY 0 ***************************
TAD_community load(TAD_community com, char* dump_path);  //diretoria onde estarão os ficheiros do dump

/**
  *************************** QUERY 1 ***************************
  * Dado o identificador de um post, a função deve retornar
  * o título do post e o nome (não o ID) de utilizador do autor;
*/
STR_pair info_from_post(TAD_community com, long id);

/**
  *************************** QUERY 2 ***************************
  * Pretende obter o top N utilizadores com maior número
  * de posts de sempre. Para isto, devem ser considerados tanto perguntas
  * quanto respostas dadas pelo respectivo utilizador;
*/
LONG_list top_most_active(TAD_community com, int N);

/**
  *************************** QUERY 3 ***************************
  * Dado um intervalo de tempo 2 arbitrário, obter o número
  * total de posts (identificando perguntas e respostas separadamente) neste
  * período;
*/
LONG_pair total_posts(TAD_community com, Date begin, Date end);

/**
  *************************** QUERY 4 ***************************
  * Dado um intervalo de tempo arbitrário, retornar todas
  * as perguntas contendo uma determinada tag. O retorno da função deverá ser
  * uma lista com os IDs das perguntas ordenadas em cronologia inversa;
*/
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end);

/**
  *************************** QUERY 5 ***************************
  * Dado um ID de utilizador, devolver a informação do
  * seu perfil (short bio) e os IDs dos seus 10 últimos posts (perguntas ou res-
  * postas), ordenados por cronologia inversa;
*/
USER get_user_info(TAD_community com, long id);

/**
  *************************** QUERY 6 ***************************
  * Dado um intervalo de tempo arbitrário, devolver os IDs
  * das N respostas com mais votos, em ordem decrescente do número de votos;
*/
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);

/**
  *************************** QUERY 7 ***************************
  * Dado um intervalo de tempo arbitrário, devolver as
  * IDs das N perguntas com mais respostas, em ordem decrescente do número
  * de votos;
*/
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end);

/**
  *************************** QUERY 8 ***************************
  * Dado uma palavra, devolver uma lista com os IDs de
  * N perguntas cujos títulos a contenham, ordenados por cronologia inversa;
*/
LONG_list contains_word(TAD_community com, char* word, int N);

/**
  *************************** QUERY 9 ***************************
  * Dados os IDs de dois utilizadores, devolver as últimas
  * N perguntas (cronologia inversa) em que participaram dois utilizadores
  * específicos. Note que os utilizadores podem ter participado via pergunta ou
  * respostas;
*/
LONG_list both_participated(TAD_community com, long id1, long id2, int N);

/**
  * --QUERY 10--
  * Dado ID de uma pergunta, obter a melhor resposta.
  * Usando a função de média:
  * (Scr*0.45) + (Rep*0.25) + (Vot*0.2) + (Comt*0.1)
*/
long better_answer(TAD_community com, long id);

/**
  *************************** QUERY 10 ***************************
  * Dado um intervalo arbitrário de tempo, devolver as
  * N tags mais usadas pelos N utilizadores com melhor reputação. Em ordem
  * decrescente do número de vezes em que a tag foi usada.
*/
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);

/**
*************************** QUERY 11 ***************************
  * Dá free a toda a memória alocada pela TAD_community
*/
TAD_community clean(TAD_community com);
