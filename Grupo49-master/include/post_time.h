#ifndef __POST_TIME__
#define __POST_TIME__

typedef struct post_time* POST_TIME;

typedef struct short_date* SHORT_DATE;

/**
* \brief Função que cria um novo elemento do tipo POST_TIME
* @param POST_TIME que vai ser inserido no novo ano
* @param int year que vai indicar o ano novo a criar
* @return devolve a estrutura com mais elementos
*/
POST_TIME create_year (POST_TIME posts, int year);

/**
* \brief Função que cria um POST_TIME
* @return do POST_TIME sem elementos
*/
POST_TIME create_post_time();

/**
* \brief Função que cria uma short_date
* @return da SHORT_DATE acabado de ser criado;
*/
SHORT_DATE create_short_date();

/**
* \brief Função que vai buscar o ano do elemento atual da Lista ligada POST_TIME
* @param POST_TIME , a lista para ser percorrida
* @return devolve o ano no elemento atual do tipo int
*/
int get_posts_year(POST_TIME posts);

/**
* \brief Função que vai buscar o proximo elemento da Lista ligada POST_TIME
* @param POST_TIME , a lista para ser percorrida
* @return devolve a estrutura no proximo elemento do tipo POST_TIME
*/
POST_TIME get_posts_next(POST_TIME posts);

/**
* \brief Função que vai buscar o ano do elemento atual da Lista ligada POST_TIME
* @param POST_TIME , a lista para ser percorrida
* @return devolve o ano no elemento atual
*/
long get_new_day_id(SHORT_DATE new_date);

/**
* \brief Função que vai buscar a hora numa SHORT_DATE
* @param uma SHORT_DATE para ir buscar a informação
* @return devolve a hora da short date
*/
int get_new_day_hour(SHORT_DATE new_date);

/**
* \brief Função que vai buscar o ano do elemento atual da Lista ligada POST_TIME
* @param uma SHORT_DATE para ir buscar a informação
* @return devolve a hora da short date
*/
SHORT_DATE get_new_day_next(SHORT_DATE new_date);

/**
* \brief Função que vai buscar a informação relativa a um determinado dia
* @param POST_TIME a estrutra onde se encontra a informação
* @return devolve a estrutura que representa o dia , do tipo SHORT_DATE
*/
SHORT_DATE get_new_date_from_post(POST_TIME posts, int indice);

/**
* \brief Função que muda o dia na POST_TIME
* @param POST_TIME representa a estrutura principal com as datas
* @param int indice para saber que dia tem que mudar
* @param SHORT_DATE é o dia a inserir na POST_TIME
* @return void;
*/
void set_posts_day_indice(POST_TIME posts, int indice, SHORT_DATE day);

/**
* \brief Função que muda o valor do ano na POST_TIME
* @param POST_TIME representa a estrutura principal com as datas
* @param int year representa o ano a ser mudado
* @return void;
*/
void set_posts_year(POST_TIME posts, int year);

/**
* \brief Função que addiciona um valor a cauda da LISTA_LIGADA POST_TIME
* @param POST_TIME posts representa a estrutura principal com as datas
* @param POST_TIME year  representa a estrutura a addicionar a principal
* @return void;
*/
void set_posts_next(POST_TIME posts,POST_TIME next);

/**
* \brief Função que muda o id de uma short_date
* @param SHORT_DATE new_date representa estrutra onde se quer mudar o id
* @param long id representa o id a ser colocado na estrutura
* @return void;
*/
void set_new_date_id (SHORT_DATE new_date, long id);

/**
* \brief Função que muda a hora de uma short_date
* @param SHORT_DATE new_date representa estrutra onde se quer mudar a hora
* @param int hour representa a hora a ser colocado na estrutura SHORT_DATE
* @return void;
*/
void set_new_date_hour (SHORT_DATE new_date, int hour);

/**
* \brief Função que muda o valor a seguir numa SHORT_DATE
* @param SHORT_DATE new_date representa estrutra onde se quer mudar o valor seguinte
* @param SHORT_DATE next representa a estrutra para dar append
* @return void;
*/
void set_new_date_next (SHORT_DATE new_date, SHORT_DATE next);

/**
* \brief Função liberta a memoria allocada por um POST_TIME
* @param um POST
* @return void
*/
void free_year(POST_TIME year);

/**
* \brief Função liberta a memoria allocada por um SHORT_DATE
* @param um POST
* @return void
*/
void free_day (SHORT_DATE day);

/**
* \brief Função liberta a memoria allocada por um POST_TIME
* @param um POST
* @return void
*/
void free_post_by_time(POST_TIME postsT);
#endif
