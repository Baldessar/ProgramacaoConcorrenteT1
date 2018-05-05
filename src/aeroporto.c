#include <stdlib.h>
#include "aeroporto.h"
#include "semaphore.h"

/**
 * aeroporto.c
 * Implementação das funções do aeroporto.h
 * Descrições em aeroporto.h
 **/

aeroporto_t* iniciar_aeroporto (size_t* args, size_t n_args) {
    aeroporto_t* aeroporto = (aeroporto_t*) malloc (sizeof(aeroporto_t));

    aeroporto->n_pistas = args[1];
    aeroporto->n_portoes = args[2];
    aeroporto->n_esteiras = args[3];
    aeroporto->n_max_avioes_esteira = args[4];
    aeroporto->t_pouso_decolagem = args[5];
    aeroporto->t_remover_bagagens = args[6];
    aeroporto->t_inserir_bagagens = args[7];
    aeroporto->t_bagagens_esteira = args[8];
    aeroporto->fila_pista = criar_fila();
    aeroporto->fila_portao = criar_fila();
    aeroporto->fila_esteira = criar_fila();
    sem_init(aeroporto->sem_pistas, 0, aeroporto->n_pistas);
    sem_init(aeroporto->sem_portoes, 0, aeroporto->n_portoes);
    sem_init(aeroporto->sem_esteiras, 0, (aeroporto->n_esteiras * aeroporto->n_max_avioes_esteira));

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
