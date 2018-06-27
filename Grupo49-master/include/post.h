#include <date.h>

#ifndef __POST__
#define __POST__

typedef struct post* POST;

typedef struct short_post* SHORT_POST;

/**
* \brief Função que cria um POST
* @param unsigned char* title que ira ser o titulo do POST
* @param unsigned char* tags que ira ser as TAGS de um POST
* @param unsigned char* id que ira ser o ID do POST
* @param unsigned char* parentId que ira ser o ID da pergunta do POST (Este parametro é -1 quando for um pergunta)
* @param unsigned char* userId que ira ser o ID do utilizador que criou o POST
* @param unsigned char* postTypeId que ira indicar se o POST é uma pergunta ou é uma resposta
* @param unsigned char* score que ira ser o score obtido pelo POST
* @param unsigned char* reply_number que ira ser o numero de respostas que o POST obteve
* @return o POST acabado de criar
*/
POST create_post(unsigned char* title, unsigned char* tags, unsigned char* id, unsigned char* parentId, unsigned char* userId, unsigned char* postTypeId, unsigned char* score, unsigned char* reply_number);

/**
* \brief Função que cria um POST incompleto, ou seja, nao contem toda a informação em relação aos posts
* @param long id que ira ser o ID do POST
* @param long best_answer_id que ira ser o ID da melhor resposta ao POST
* @param int best_answer_score que ira ser o score da melhor resposta ao POST
* @return o POST acabado de criar
*/
POST create_incomplete_post(long id, long best_answer_id ,int best_answer_score);

/**
* \brief Função que vai buscar o ID de um POST
* @param um POST
* @return o ID do POST do tipo long
*/
long get_post_id(POST p);

/**
* \brief Função que vai buscar o pointer do ID de um POST
* @param um POST
* @return o pointer do titulo do POST do tipo long*
*/
long* get_post_id_pointer(POST p);

/**
* \brief Função que vai buscar o ID do criador de um POST
* @param um POST
* @return o ID do criador do POST do tipo long
*/
long get_post_user_id(POST p);

/**
* \brief Função que vai buscar o pointer do ID do criador de um POST
* @param um POST
* @return o pointer do ID do criador do POST do tipo long*
*/
long* get_post_user_id_pointer(POST p);

/**
* \brief Função que vai buscar o ID da pergunta de um POST a que este ID é resposta
* @param um POST
* @return o ID da pergunta a que este ID é reposta (caso o POST seja uma pergunta retorna -1)
*/
long get_post_parent_id(POST p);

/**
* \brief Função que vai buscar o pointer do ID da pergunta de um POST a que este ID é resposta
* @param um POST
* @return o pointer do ID da pergunta a que este ID é reposta (caso o POST seja uma pergunta esta retorna NULL)
*/
long* get_post_parent_id_pointer(POST p);

/**
* \brief Função que vai buscar o titulo de um POST
* @param um POST
* @return o titulo do POST do tipo char*
*/
char* get_post_title(POST p);

/**
* \brief Função que vai buscar as TAGS de um POST
* @param um POST
* @return as tags do POST do tipo char*
*/
char* get_post_tags(POST p);

/**
* \brief Função que vai buscar o ID da melhor resposta ao POST p
* @param um POST
* @return o ID da melhor resposta do tipo long
*/
long get_post_best_answer_id(POST p);

/**
* \brief Função que vai buscar o tipo de um POST
* @param um POST
* @return o tipo do POST do tipo int (1 == pergunta , 2 == resposta)
*/
int get_post_type (POST p);

/**
* \brief Função que vai buscar o score da melhor resposta ao POST p
* @param um POST
* @return o score da melhor resposta do tipo int
*/
int get_post_best_answer_score(POST p);

/**
* \brief Função que vai buscar o score do POST
* @param um POST
* @return o score do POST do tipo int
*/
int get_post_score(POST p);

/**
* \brief Função que vai buscar numero de respostas ao POST
* @param um POST
* @return o numero de respostas ao POST do tipo int
*/
int get_post_reply_number(POST p);

/**
* \brief Função que vai incrementar por 1 o numero de respostas
* @param um POST
* @return void
*/
void increment_post_reply_number(POST p);

/**
* \brief Função que vai mudar o id da melhor resposta
* @param um POST
* @param long id , representa o ID da nova melhor resposta
* @return void
*/
void set_post_best_answer_id(POST p, long id);

/**
* \brief Função que vai mudar o score da melhor resposta
* @param um POST
* @param int id , representa o score da nova melhor resposta
* @return void
*/
void set_post_best_answer_score(POST p, int score);

/**
* \brief Função que vai completar o POST
* @param POST p , indica o post incompleto
* @param POST aux , indica o post que contem o resto da informação em relação ao post
* @return void
*/
void complete_post(POST p, POST aux);


/**
* \brief Função que cria um SHORT_POST incompleto, ou seja, nao contem toda a informação em relação aos SHORT_POST
* @param long id que ira ser o ID do POST
* @param long id1 que ira ser o ID de um utilizador
* @return o SHORT_POST acabado de criar
*/
SHORT_POST create_incomplete_short_post_user1(long id,long id1);

/**
* \brief Função que cria um SHORT_POST incompleto, ou seja, nao contem toda a informação em relação aos SHORT_POST
* @param long id que ira ser o ID do POST
* @param long id2 que ira ser o ID de um utilizador
* @return o SHORT_POST acabado de criar
*/
SHORT_POST create_incomplete_short_post_user2(long id, long id2);

/**
* \brief Função que vai buscar o id do utilizador 1;
* @param um SHORT_POST
* @return o ID do utilizador1 do tipo long
*/
long get_short_post_user1_id(SHORT_POST s);

/**
* \brief Função que vai buscar o id do utilizador 2;
* @param um SHORT_POST
* @return o ID do utilizador1 do tipo long
*/
long get_short_post_user2_id(SHORT_POST s);

/**
* \brief Função que vai mudar o utilizador1 na estrutura SHORT_POST
* @param um POST
* @param int id , representa o id do utilizador1;
* @return void
*/
void set_short_post_user1_id(SHORT_POST s, long id1);

/**
* \brief Função que vai mudar o utilizador2 na estrutura SHORT_POST
* @param um POST
* @param int id , representa o id do utilizador2;
* @return void
*/
void set_short_post_user2_id(SHORT_POST s, long id2);

/**
* \brief Função liberta a memoria allocada por um SHORT_POST
* @param um POST
* @return void
*/
void free_short_post(void* s);

/**
* \brief Função liberta a memoria allocada por um POST
* @param um POST
* @return void
*/
void free_post(void* rip);


#endif
