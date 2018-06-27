#ifndef __PARSER_H__
#define __PARSER_H__
#include "interface.h"
#include "post_time.h"
#include <glib.h>

//****************** FUNÇÕES ************//




/**
* \brief Função que vai buscar a GHashTable o user_id, ou seja, o id do utilizador que escreveu o post
* @param GHashTable* hash_post representa a hash_table que tem os posts todos
* @return long id representa o ID do post que contem a informação que queremos
*/
long get_hash_post_user_id(GHashTable* hash_post, long id);

/**
* \brief Função que vai buscar a GHashTable o score de um post apartir de um ID
* @param GHashTable* hash_post representa a hash_table que tem os posts todos
* @return long id representa o ID do post que contem a informação que queremos
*/
int get_hash_post_score(GHashTable* hash_post, long id);

/**
* \brief Função que vai buscar a GHashTable o tipo de post apartir de um ID (2 == resposta , 1 == pergunta)
* @param GHashTable* hash_post representa a hash_table que tem os posts todos
* @return long id representa o ID do post que contem a informação que queremos
*/
int get_hash_post_type (GHashTable* hash_post, long id);

/**
* \brief Função que vai buscar a GHashTable o titulo de um post apartir de um ID
* @param GHashTable* hash_post representa a hash_table que tem os posts todos
* @return long id representa o ID do post que contem a informação que queremos
*/
char* get_hash_post_title(GHashTable* hash_post, long id);

/**
* \brief Função que vai buscar a GHashTable as tags de um post apartir de um ID
* @param GHashTable* hash_post representa a hash_table que tem os posts todos
* @return long id representa o ID do post que contem a informação que queremos
*/
char* get_hash_post_tags(GHashTable* hash_post, long id);

/**
* \brief Função que vai buscar a GHashTable uma pergunta e indica o numero de resposta dessa pergunta
* @param GHashTable* hash_post representa a hash_table que tem os posts todos
* @return long id representa o ID do post que contem a informação que queremos
*/
int get_hash_post_reply_number(GHashTable* hash_post, long id);

/**
* \brief Função que cria as estrutras de dados para ser usado no programa em relação as posts
* @param GHashTable* hash_post representa a hash que ira ter os posts
* @param GHashTable* hash_users representa a hash que ira ter os USERS
* @param POST_TIME* posts_time representa as estruturas para inserir os posts por datas
* @param char* dump_path representao caminho onde os ficheiros xml se encontram
* @return um inteiro para verificação de erros (== 0 indica que correu tudo bem)
*/
int parser_post (GHashTable* hash_post, GHashTable* hash_users, POST_TIME* posts_time, char* dump_path);

/**
* \brief Função que cria as estrutras de dados para ser usado no programa em relação aos USERS
* @param GHashTable* hash_users representa a hash que ira ter os USERS
* @param char* dump_path representao caminho onde os ficheiros xml se encontram
* @return um inteiro para verificação de erros (== 0 indica que correu tudo bem)
*/
int parser_users (GHashTable* hash_users, char* dump_path);

/**
* \brief Função que cria as estrutras de dados para ser usado no programa em relação as tags
* @param GHashTable* hash_tag representa a hash que ira ter as tags
* @param char* dump_path representao caminho onde os ficheiros xml se encontram
* @return um inteiro para verificação de erros (== 0 indica que correu tudo bem)
*/
int parser_tag (GHashTable* hash_tag, char* dump_path);

#endif
