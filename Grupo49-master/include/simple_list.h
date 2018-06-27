#ifndef __SIMPLE_LIST__
#define __SIMPLE_LIST__

#include "parser.h"

typedef struct simple_list* SIMPLE_LIST;

/**
* \brief Função que vai buscar o proximo elemento de uma SIMPLE_LIST
* @param um SIMPLE_LIST
* @return a proxima SIMPLE_LIST
*/
SIMPLE_LIST get_simple_list_next(SIMPLE_LIST sp);

/**
* \brief Função que vai buscar o ID de uma SIMPLE_LIST
* @param um POST
* @return o ID da SIMPLE_LIST do tipo long
*/
long get_simple_list_id(SIMPLE_LIST sp);

/**
* \brief Função que vai buscar o parametro de uma SIMPLE_LIST
* @param um POST
* @return o parametro da SIMPLE_LIST do tipo int
*/
int get_simple_list_param(SIMPLE_LIST sp);

/**
* \brief Função que vai mudar o o proximo elemento para a estrutura SIMPLE_LIST
* @param uma SIMPLE_LIST
* @param uma SIMPLE_LIST para ser a seguinte
* @return void
*/
void set_simple_list_next(SIMPLE_LIST sp, SIMPLE_LIST prox);

/**
* \brief Função que vai mudar o parametro da estrutura SIMPLE_LIST
* @param uma SIMPLE_LIST
* @param int param que representa o paramentro a mudar na estrutra
* @return void
*/
void set_simple_list_param(SIMPLE_LIST sp, int param);

/**
* \brief Função que vai mudar o id da estrutura SIMPLE_LIST
* @param uma SIMPLE_LIST
* @param int id que representa o id a mudar na estrutra
* @return void
*/
void set_simple_list_id(SIMPLE_LIST sp, long id);

/**
* \brief Função que cria uma SIMPLE_LIST
* @return o SIMPLE_LIST acabado de criar
*/
SIMPLE_LIST create_simple_list();

/**
* \brief Função que insere numa lista ligada do tipo SIMPLE_LIST segundo o param
* @param uma SIMPLE_LIST para percorrer
* @param int id o id do parametro
* @param int param para ser utilizado para inserir
* @param int N delimita o numero total de elementos
* @return a SIMPLE_LIST acabado de inserir um elemento novo
*/
SIMPLE_LIST insere_lista_score(SIMPLE_LIST lista,long id, int param, int N);

/**
* \brief Função liberta a memoria allocada por uma SIMPLE_LIST
* @param uma SIMPLE_LIST
* @return void
*/
void free_lista_score(SIMPLE_LIST rip);

#endif
