#include "aviao.h"
#include <stdlib.h>
#include <time.h>
/**
 * aviao.c
 * Implementação das funções do aviao.h
 * Descrições em aviao.h
 **/
int id = 0;
aviao_t * aloca_aviao (size_t combustivel, size_t id) {
  aviao_t aviao = (struct aviao_t*) malloc (sizeof(aviao_t));
  aviao->combustivel = (rand() % 100)+1;
  aviao->id = ++i;
  pthread_create(aviao->thread, NULL, aproximacao_aeroporto, NULL);
  return aviao;
}

void desaloca_aviao(aviao_t* aviao) {

}
