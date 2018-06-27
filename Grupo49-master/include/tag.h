#ifndef __TAG__
#define __TAG__
#include "simple_list.h"
//****************** STRUCTS ************//

typedef struct tag* TAG;
typedef struct top_tag* TOP_TAG;

//****************** FUNÇÕES ************//

/**
* \brief Função que cria uma TAG
* @param unsigned char* tag_name que recebe o nome da TAG
* @param unsigned char* ID que recebe a ID da TAG
* @param unsigned char* count que recebe o numero de vezes que uma TAG apareceu
* @return o USERS acabado de criado;
*/
TAG create_tag(unsigned char* tag_name, unsigned char* id, unsigned char* count);


/**
* \brief Função que vai buscar o pointer do ID de uma TAG
* @param uma TAG
* @return o pointer do ID da TAG do tipo long
*/
long* get_tag_id_pointer(TAG t);

/**
* \brief Função que vai buscar o nome de uma TAG
* @param uma TAG
* @return o o nome da TAG do tipo char*
*/
char* get_tag_name(TAG t);

/**
* \brief Função que vai buscar o ID de uma TAG
* @param uma TAG
* @return o ID da TAG do tipo long
*/
long get_tag_id(TAG t);

/**
* \brief Função que vai buscar o nmero de vezes que uma TAG aparece
* @param uma TAG
* @return o nmero de vezes que uma TAG aparece do tipo int;
*/
int get_tag_count(TAG t);

/**
* \brief Função liberta a memoria allocada por uma TAG
* @param um void* que deve ser do tipo TAG
* @return void
*/
void free_tags(void* rip);

/**
* \brief Função que cria uma tag, com dados incompletos
* @param string com o nome da tag
* @param long com o id da tag
* @return void
*/
TAG create_incomplete_tag(char* tag,long id);

/**
* \brief Função que que incrementa o numero de aparições da tag
* @param tag a ser incrementa
* @return void
*/
void increment_tag (TAG t);

/**
* \brief Função que obtem a simple_list com o top N tags dos top N users
* @param estrutura com a hash das tags(query11)
* @return void
*/
SIMPLE_LIST get_top_tag_list(TOP_TAG t);

/**
* \brief Função que cria a TOP_TAG com o N da query e a lista das suas tags
* @param estrutura com a hash das tags(query11)
* @return void
*/
TOP_TAG create_top_tag(int size, SIMPLE_LIST list);


/**
* \brief Função que obtem o N pedido na query
* @param estrutura com a hash das tags(query11)
* @return void
*/
int get_top_tag_size(TOP_TAG t);

/**
* \brief Função que obtem a lista de tags da query
* @param estrutura com a hash das tags(query11)
* @return void
*/
void set_top_tag_list(TOP_TAG t, SIMPLE_LIST list);

#endif
