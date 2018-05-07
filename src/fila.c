#include "fila.h"
#include <stdlib.h>
#include   	<stdio.h>

/**
 * fila.c
 * Implementação das funções da fila.h
 * Descrições em fila.h
 **/

 elemento_t * aloca_elemento (aviao_t * dado) {
    
    elemento_t* elemento = (elemento_t*) malloc(sizeof(elemento_t));
    
    elemento->anterior = NULL;
    elemento->proximo = NULL;
    elemento->dado = dado;

    return elemento;
 }

 void desaloca_elemento (elemento_t * elemento) {
    free(elemento);
 }

fila_ordenada_t * criar_fila () {
    fila_ordenada_t* fila = (fila_ordenada_t*) malloc(sizeof(fila_ordenada_t));

    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->n_elementos = 0;

    return fila;
    
}

void desaloca_fila (fila_ordenada_t * fila) {
    free(fila);
}

void inserir (fila_ordenada_t * fila, aviao_t * dado) {
    elemento_t* adicionado = aloca_elemento(dado);
    adicionado->dado = dado;
    if (fila->n_elementos == 0)
    {	
    	fila->primeiro = adicionado;
    	fila->ultimo = adicionado;
    	fila->primeiro->proximo = NULL;
    	fila->primeiro->anterior = NULL;
    	pthread_mutex_unlock(&fila->primeiro->dado->mutexAviao);
    	fila->n_elementos = 1;
    	printf("%s inserindo o primeiro %d \n",fila->nome_fila ,adicionado->dado->id);
    } else {
    	adicionado->proximo = fila->ultimo;
    	fila->ultimo->anterior = adicionado;
    	fila->ultimo = adicionado;
    	fila->n_elementos++;
    	//printf("%s inserindo %d \n", fila->nome_fila, adicionado->dado->id);

    }
}

aviao_t * remover (fila_ordenada_t * fila) {
    if (fila->n_elementos == 0) {
         printf("%s impossivel retirar, fila vazia",fila->nome_fila);
         return NULL;
    }
   
    elemento_t* removido = fila->primeiro;

    if (fila->n_elementos == 1)
    {	
        fila->primeiro = NULL;
        fila->ultimo = NULL;
        fila->n_elementos = 0;
    	printf("%s removendo unico %d \n", fila->nome_fila, removido->dado->id);

    } else {
    	fila->primeiro = removido->anterior;
    	fila->primeiro->proximo = NULL;
    	pthread_mutex_unlock(&fila->primeiro->dado->mutexAviao);
    	//fila->primeiro->mutexAviao
        fila->n_elementos--;
    	printf("%s removendo %d \n", fila->nome_fila, removido->dado->id );
    }
        
    aviao_t* aviao = removido->dado;
  
    free(removido);
    return aviao;
}
