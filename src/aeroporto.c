#include "aeroporto.h"
#include "semaphore.h"
/**
 * aeroporto.c
 * Implementação das funções do aeroporto.h
 * Descrições em aeroporto.h
 **/

sem_t aproximacao;


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

	return aeroporto;

}

void aproximacao_aeroporto (aeroporto_t* aeroporto, aviao_t* aviao) {
    
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
	return 0;
}
