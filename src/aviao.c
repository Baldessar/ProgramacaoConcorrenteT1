#include "aviao.h"
#include <stdlib.h>
#include <time.h>
/**
 * aviao.c
 * Implementação das funções do aviao.h
 * Descrições em aviao.h
 **/
int id = 0;
aviao_t * aloca_aviao () {
  aviao_t* aviao = (struct aviao_t*) malloc (sizeof(aviao_t));
  aviao->combustivel = (rand() % 100)+1;
  aviao->id = ++i;
  pthread_mutex_init(&aviao->mutexAviao, NULL);
  pthread_mutex_lock(&aviao->mutexAviao);
  //pthread_create(aviao->thread, NULL, aproximar, parametros_aviao);
  return aviao;
}

void desaloca_aviao(aviao_t* aviao) {
  free(aviao);
}