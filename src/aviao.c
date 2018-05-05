#include "aviao.h"
#include <stdlib.h>
#include <time.h>
#include "aeroporto.h"




/**
 * aviao.c
 * Implementação das funções do aviao.h
 * Descrições em aviao.h
 **/
int id = 0;
aviao_t* aloca_aviao (size_t combustivel, size_t id) {
  aviao_t* aviao = (aviao_t*) malloc (sizeof(aviao_t));
  aviao->combustivel = combustivel;
  aviao->id = id;
  pthread_mutex_init(&aviao->mutexAviao, NULL);
  pthread_mutex_lock(&aviao->mutexAviao);
  //pthread_create(aviao->thread, NULL, aproximar, parametros_aviao);
  return aviao;
}

void desaloca_aviao(aviao_t* aviao) {
  free(aviao);
}

void* inicia_aproximacao(void* args) {
	parametros_aviao* parametros = (parametros_aviao*)args;
	aproximacao_aeroporto(parametros->aeroporto, parametros->aviao);
	free(args);
}