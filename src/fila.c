#include "fila.h"
#include <stdlib.h>

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
    elemento_t* elemento = aloca_elemento(dado);
    elemento->dado = dado;
    if (fila->n_elementos == 0)
    {
        elemento->proximo = elemento;
        elemento->anterior = elemento;
        pthread_mutex_unlock(&elemento->dado->mutexAviao); 
        fila->primeiro = elemento;
        fila->ultimo = elemento;
        fila->n_elementos = 1;
    } else {
    	if (dado->combustivel <= 10)
    	{	
            elemento->proximo = fila->ultimo;
            elemento->anterior = fila->primeiro;
            fila->primeiro->proximo = elemento;
            fila->primeiro = elemento;
    	} else {
            elemento->proximo = fila->ultimo;
            elemento->anterior = fila->primeiro;
            fila->primeiro->proximo = elemento;
            fila->ultimo->anterior = elemento;
            fila->ultimo = elemento;
    	}
        fila->n_elementos++;
    }
}

aviao_t * remover (fila_ordenada_t * fila) {
    elemento_t* removido = fila-> primeiro;
    if (removido->anterior == removido)
    {
    	fila->primeiro = NULL;
    	fila->ultimo = NULL;
    } else {
    	
        fila->primeiro = removido->anterior;
        fila->primeiro->proximo = removido->proximo;
        pthread_mutex_unlock(&fila->primeiro->dado->mutexAviao);
    }
    fila->n_elementos--;
    aviao_t* aviao = removido->dado;
    //free(remover);
    return aviao;
}
