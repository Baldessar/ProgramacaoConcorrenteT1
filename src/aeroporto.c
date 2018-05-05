#include <stdlib.h>
#include <stdio.h>
#include "aeroporto.h"
#include "semaphore.h"

/**
 * aeroporto.c
 * Implementação das funções do aeroporto.h
 * Descrições em aeroporto.h
 **/

aeroporto_t* iniciar_aeroporto (size_t* args, size_t n_args) {
    aeroporto_t* aeroporto = (aeroporto_t*) malloc (sizeof(aeroporto_t));
    aeroporto->sem_pistas =(sem_t*) malloc(sizeof(sem_t));
    aeroporto->sem_portoes =(sem_t*) malloc(sizeof(sem_t));
    aeroporto->sem_esteiras =(sem_t*) malloc(sizeof(sem_t));
    printf("1\n");
    aeroporto->n_pistas = args[1];
    printf("2\n");
    aeroporto->n_portoes = args[2];
    printf("3\n");
    aeroporto->n_esteiras = args[3];
    printf("4\n");
    aeroporto->n_max_avioes_esteira = args[4];
    printf("5\n");
    aeroporto->t_pouso_decolagem = args[5];
    printf("6\n");
    aeroporto->t_remover_bagagens = args[6];
    printf("7\n");
    aeroporto->t_inserir_bagagens = args[7];
    printf("8\n");
    aeroporto->t_bagagens_esteira = args[8];
    printf("9\n");
    aeroporto->fila_pista = criar_fila();
    printf("10\n");
    aeroporto->fila_portao = criar_fila();
    printf("11\n");
    aeroporto->fila_esteira = criar_fila();
    printf("12\n");
    sem_init(aeroporto->sem_pistas, 0, aeroporto->n_pistas);
    printf("13\n");
    sem_init(aeroporto->sem_portoes, 0, aeroporto->n_portoes);
    printf("14\n");
    sem_init(aeroporto->sem_esteiras, 0, (aeroporto->n_esteiras * aeroporto->n_max_avioes_esteira));
    printf("fim\n");
    return aeroporto;

}



void aproximacao_aeroporto (aeroporto_t* aeroporto, aviao_t* aviao) {

    inserir(aeroporto->fila_pista,aviao);
    pthread_mutex_lock(&aviao->mutexAviao);
    pousar_aviao(aeroporto,aviao);
}

void pousar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {
    
}

void acoplar_portao (aeroporto_t* aeroporto, aviao_t* aviao) {
    
}

void transportar_bagagens (aeroporto_t* aeroporto, aviao_t* aviao) {
    
}

void adicionar_bagagens_esteira (aeroporto_t* aeroporto, aviao_t* aviao) {
    
}

void decolar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {
    
}

int finalizar_aeroporto (aeroporto_t* aeroporto) {
    free(aeroporto);
}
