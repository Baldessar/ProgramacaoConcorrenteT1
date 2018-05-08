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
    aeroporto->mutexFilaPouso = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    aeroporto->mutexFilaPortao = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    aeroporto->mutexFilaEsteira = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    aeroporto->mutexFilaDecolagem = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    aeroporto->n_pistas = args[0];
    aeroporto->n_portoes = args[1];
    aeroporto->n_esteiras = args[2];
    aeroporto->n_max_avioes_esteira = args[3];
    aeroporto->t_pouso_decolagem = args[4];
    aeroporto->t_remover_bagagens = args[5];
    aeroporto->t_inserir_bagagens = args[6];
    aeroporto->t_bagagens_esteira = args[7];
    aeroporto->fila_pouso = criar_fila();
    aeroporto->fila_portao = criar_fila();
    aeroporto->fila_esteira = criar_fila();
    aeroporto->fila_decolagem = criar_fila();
    aeroporto->fila_pouso->nome_fila = "Pouso: ";
    aeroporto->fila_portao->nome_fila = "Portoes: ";
    aeroporto->fila_esteira->nome_fila = "Esteiras: ";
    aeroporto->fila_decolagem->nome_fila = "Decolagem: ";
    sem_init(aeroporto->sem_pistas, 0, aeroporto->n_pistas);
    sem_init(aeroporto->sem_portoes, 0, aeroporto->n_portoes);
    sem_init(aeroporto->sem_esteiras, 0, (aeroporto->n_esteiras * aeroporto->n_max_avioes_esteira));
    pthread_mutex_init(aeroporto->mutexFilaPouso, NULL);
    pthread_mutex_init(aeroporto->mutexFilaPortao, NULL);
    pthread_mutex_init(aeroporto->mutexFilaEsteira, NULL);
    pthread_mutex_init(aeroporto->mutexFilaDecolagem, NULL);
    return aeroporto;

}



void aproximacao_aeroporto (aeroporto_t* aeroporto, aviao_t* aviao) {
    printf("Aviao %d se aproximando\n",aviao->id);
    pthread_mutex_lock(&aviao->mutexAviao);
    sem_wait(aeroporto->sem_pistas);
    printf("Aviao %d liberado para pouso\n",aviao->id);
    pousar_aviao(aeroporto,aviao);
}

void pousar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {
    printf("Aviao %d pousando\n",aviao->id);
    aviao->combustivel = 10;
    usleep(aeroporto->t_pouso_decolagem);
    pthread_mutex_lock(aeroporto->mutexFilaPouso);
    remover(aeroporto->fila_pouso);
    pthread_mutex_unlock(aeroporto->mutexFilaPouso);
    pthread_mutex_lock(aeroporto->mutexFilaPortao);
    inserir(aeroporto->fila_portao,aviao);
    pthread_mutex_unlock(aeroporto->mutexFilaPortao);
    sem_post(aeroporto->sem_pistas);
    pthread_mutex_lock(&aviao->mutexAviao);
    sem_wait(aeroporto->sem_portoes);
    printf("Aviao %d liberado engate no portao\n",aviao->id);
    acoplar_portao(aeroporto,aviao);
}

void acoplar_portao (aeroporto_t* aeroporto, aviao_t* aviao) {
    printf("Aviao %d acoplado no portao\n",aviao->id);
    pthread_mutex_lock(aeroporto->mutexFilaPortao);
    remover(aeroporto->fila_portao);
    pthread_mutex_unlock(aeroporto->mutexFilaPortao);
    pthread_mutex_lock(aeroporto->mutexFilaEsteira);
    inserir(aeroporto->fila_esteira,aviao);
    pthread_mutex_unlock(aeroporto->mutexFilaEsteira);
    sem_post(aeroporto->sem_portoes);
    pthread_mutex_lock(&aviao->mutexAviao);
    sem_wait(aeroporto->sem_esteiras);
    printf("Aviao %d liberado uso das esteiras\n",aviao->id);
    transportar_bagagens(aeroporto,aviao);
}

void transportar_bagagens (aeroporto_t* aeroporto, aviao_t* aviao) {
    printf("Aviao %d transportando bagagens para as esteiras\n",aviao->id);
    usleep(aeroporto->t_remover_bagagens);
    adicionar_bagagens_esteira(aeroporto,aviao);
}

void adicionar_bagagens_esteira (aeroporto_t* aeroporto, aviao_t* aviao) {
    printf("Aviao %d adicionando bagagens as esteiras\n",aviao->id);
    pthread_mutex_lock(aeroporto->mutexFilaEsteira);
    remover(aeroporto->fila_esteira);
    pthread_mutex_unlock(aeroporto->mutexFilaEsteira);
    usleep(aeroporto->t_inserir_bagagens + aeroporto->t_bagagens_esteira);
    sem_post(aeroporto->sem_esteiras);
    decolar_aviao(aeroporto,aviao);
}

void decolar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {
    printf("Aviao %d aguardando permissão para decolar\n",aviao->id);
    pthread_mutex_lock(aeroporto->mutexFilaDecolagem);
    inserir(aeroporto->fila_decolagem,aviao);
    pthread_mutex_unlock(aeroporto->mutexFilaDecolagem);
    pthread_mutex_lock(&aviao->mutexAviao);
    sem_wait(aeroporto->sem_pistas);
    printf("Aviao %d decolando\n",aviao->id);
    usleep(aeroporto->t_pouso_decolagem);
    pthread_mutex_lock(aeroporto->mutexFilaDecolagem);
    remover(aeroporto->fila_decolagem);
    pthread_mutex_unlock(aeroporto->mutexFilaDecolagem);
    sem_post(aeroporto->sem_pistas);
    free(aviao);
}

int finalizar_aeroporto (aeroporto_t* aeroporto) {
    free(aeroporto);
}
