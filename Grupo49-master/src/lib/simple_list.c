#include <libxml/parser.h>
#include <stdio.h>
#include <date.h>
#include "simple_list.h"

struct simple_list{
   long id;
   int param;
   struct simple_list* next;
};


SIMPLE_LIST get_simple_list_next(SIMPLE_LIST sp){
    return sp->next;
}

long get_simple_list_id(SIMPLE_LIST sp){
    return sp->id;
}

int get_simple_list_param(SIMPLE_LIST sp){
    return sp->param;
}

void set_simple_list_next(SIMPLE_LIST sp, SIMPLE_LIST prox){
    sp->next = prox;
}

void set_simple_list_param(SIMPLE_LIST sp, int param){
    sp->param = param;
}

void set_simple_list_id(SIMPLE_LIST sp, long id){
  sp->id = id;
}

SIMPLE_LIST create_simple_list(){
    SIMPLE_LIST novo = malloc (sizeof(struct simple_list));
    return novo;
}

void free_lista_score(SIMPLE_LIST rip){
  SIMPLE_LIST aux, auxfree;
  aux = rip;
  while (aux) {
    auxfree = aux;
    aux = get_simple_list_next(aux);
    free(auxfree);
  }
}


SIMPLE_LIST insere_lista_score(SIMPLE_LIST lista,long id, int param, int N){
  SIMPLE_LIST novo = create_simple_list();
  set_simple_list_id(novo,id);
  set_simple_list_param(novo, param);
  int count = 0;
  int flag = 0;

  if(get_simple_list_param(lista) == -2 && get_simple_list_id(lista) == -2){
    free_lista_score(lista);
    set_simple_list_next(novo,NULL);
    return novo;
  }
  if(get_simple_list_param(lista) < param){
    set_simple_list_next(novo,lista);
    return novo;
  }
  else{
    SIMPLE_LIST aux = lista;
    while(get_simple_list_next(aux) && !flag && count < N){
      if(get_simple_list_param(get_simple_list_next(aux)) < param){
        set_simple_list_next(novo,get_simple_list_next(aux));
        set_simple_list_next(aux,novo);
        flag = 1;
      }
      count++;
      aux = get_simple_list_next(aux);
    }
    if(!flag && count < N){
      set_simple_list_next(novo,NULL);
      set_simple_list_next(aux,novo);
      flag = 1;
    }
    if (!flag) {
      free(novo);
    }
    return lista;

  }
}
