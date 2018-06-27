#ifndef __USERS__
#define __USERS__

typedef struct users* USERS;

/**
* \brief Função que cria um USERS
* @param unsigned char* bio que recebe a short bio
* @param unsigned char* nickname que recebe o nickname
* @param unsigned char* ID que recebe a ID
* @param unsigned char* rep que recebe a reputação
* @return o USERS acabado de criado;
*/
USERS create_users(unsigned char* bio, unsigned char* nickname, unsigned char* id, unsigned char* rep);

/**
* \brief Função que cria um USERS só com o ID
* @param unsigned char* ID que recebe a ID
* @return o USERS com o parametro ID e com o resto da estrutra a NULL;
*/
USERS create_incomplete_users(unsigned char* id);

/**
* \brief Função que vai buscar o nickname de um USERS
* @param um USERS
* @return o nickname do USERS do tipo char*;
*/
char* get_users_nickname(USERS u);

/**
* \brief Função que vai buscar a short bio de um USERS
* @param um USERS
* @return a short bio do USERS do tipo char*;
*/
char* get_users_short_bio(USERS u);

/**
* \brief Função que vai buscar o ID de um USERS
* @param um USERS
* @return o ID do USERS do tipo long;
*/
long get_users_id(USERS u);

/**
* \brief Função que vai buscar o nickname de um USERS
* @param um USERS
* @return do pointer do ID do USERS do tipo long*;
*/
long* get_users_id_pointer(USERS u);

/**
* \brief Função que vai buscar o numero de posts do USERS
* @param um USERS
* @return o numero de posts do USERS do tipo char*
*/
int get_users_post_number(USERS u);

/**
* \brief Função que vai buscar a reputação de um USERS
* @param um USERS
* @return a reputação do USERS do tipo char*;
*/
int get_users_rep(USERS u);

/**
* \brief Função que muda o valor do numero de posts de um USERS
* @param um USERS que ira ser mudado o parametro
* @return void;
*/
void set_users_post_number(USERS u, int n);

/**
* \brief Função liberta a memoria allocada por um USERS
* @param um USERS
* @return void
*/
void free_users(void* u);

#endif
