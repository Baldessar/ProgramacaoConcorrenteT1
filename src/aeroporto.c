#include "aeroporto.h"
#include "semaphore.h"
/**
 * aeroporto.c
 * Implementação das funções do aeroporto.h
 * Descrições em aeroporto.h
 **/


typedef struct
{
    aeroporto_t aeroporto;
    aviao_t aviao;
}argumentos;


aeroporto_t* iniciar_aeroporto (size_t* args, size_t n_args) {
    aeroporto_t* aeroporto = (struct aeroporto_t*) malloc (sizeof(aeroporto_t));

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
    sem_init(sem_pistas, 0, aeroporto->n_pistas);
    sem_init(sem_portoes, 0, aeroporto->n_portoes);
    sem_init(sem_esteiras, 0, (aeroporto->n_esteiras * aeroporto->n_max_avioes_esteira));

    return aeroporto;

}

void aproximacao_aeroporto (aeroporto_t* aeroporto, aviao_t* aviao) {

    inserir(aeroporto->fila_pista,aviao);
    pthread_mutex_lock(&args->aviao->mutexAviao);
    pousar_aviao(aeroporto,aviao);
}

void pousar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(aeroporto->sem_pistas);
    aviao_t aviao_pousar = remover(args->aeroporto->fila_pista);
    aviao_pousar->combustivel = 100;
    usleep(TEMPO_POUSO_DECOLAGEM);
    inserir(aeroporto->fila_portao,aviao_pousar);
    sem_post(aeroporto->sem_pistas);
    acoplar_portao(aeroporto,aviao);
}

void acoplar_portao (aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(aeroporto->sem_portoes);
    aviao_t aviao_portao = remover(aeroporto->fila_portao);
    inserir(aeroporto->fila_portao,aviao_portao);
    sem_post(aeroporto->sem_portoes);
    transportar_bagagens(aeroporto,aviao);
}

void transportar_bagagens (aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(aeroporto->sem_esteiras);
    aviao_t aviao_bagagem = remover(aeroporto->fila_portao);
    usleep(TEMPO_REMOVER_BAGAGENS);
    usleep(TEMPO_INSERIR_BAGAGENS);
    adicionar_bagagens_esteira(aeroporto,aviao);
}

void adicionar_bagagens_esteira (aeroporto_t* aeroporto, aviao_t* aviao) {
    usleep(TEMPO_BAGAGENS_ESTEIRA);
    inserir(aeroporto->fila_pista,args->aviao);
    sem_post(aeroporto->sem_esteiras)
    decolar_aviao(aeroporto,aviao);  
}

void decolar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(aeroporto->sem_pistas);
    aviao_t aviao_decolar = remover(aeroporto->fila_pista);
    usleep(TEMPO_POUSO_DECOLAGEM);
    sem_post(aeroporto->sem_pistas);
    free(aviao);
}

int finalizar_aeroporto (aeroporto_t* aeroporto) {
    free(aeroporto);
}
