#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "aeroporto.h"
#include "aviao.h"

#define NOVO_AVIAO_MIN 30
#define NOVO_AVIAO_MAX 120
#define COMBUSTIVEL_MIN 1
#define COMBUSTIVEL_MAX 10
#define TEMPO_POUSO_DECOLAGEM 40
#define TEMPO_REMOVER_BAGAGENS 90
#define TEMPO_INSERIR_BAGAGENS 110
#define TEMPO_BAGAGENS_ESTEIRA 200
#define TEMPO_SIMULACAO 10000

int main (int argc, char** argv) {

    // Variáveis temporais (inicio t_)
    size_t t_novo_aviao_min, t_novo_aviao_max;
    size_t t_pouso_decolagem;
    size_t t_remover_bagagens, t_inserir_bagagens;
    size_t t_bagagens_esteira, t_simulacao;

    // Variáveis discretas (inicio n_)
    size_t n_pistas, n_portoes;
    size_t n_max_avioes_esteira, n_esteiras;
    size_t n_args;

    // Variáveis de prioridade (inicio p_)
    size_t p_combustivel_min, p_combustivel_max;

    if (argc == 5) { // Argumentos sem tempos de execução
        t_novo_aviao_min = NOVO_AVIAO_MIN;
        t_novo_aviao_max = NOVO_AVIAO_MAX;
        t_pouso_decolagem = TEMPO_POUSO_DECOLAGEM;
        t_remover_bagagens = TEMPO_REMOVER_BAGAGENS;
        t_inserir_bagagens = TEMPO_INSERIR_BAGAGENS;
        t_bagagens_esteira = TEMPO_BAGAGENS_ESTEIRA;
        t_simulacao = TEMPO_SIMULACAO;
        p_combustivel_min = COMBUSTIVEL_MIN;
        p_combustivel_max = COMBUSTIVEL_MAX;
        n_pistas = atoi(argv[1]);
        n_portoes = atoi(argv[2]);
        n_max_avioes_esteira = atoi(argv[3]);
        n_esteiras = atoi(argv[4]);

    } else if (argc == 14) { // Argumentos com tempos de execução
        int i = 0; // Este contador será incrementado antes de coletar um argumento
        t_novo_aviao_min = atoi(argv[++i]);
        t_novo_aviao_max = atoi(argv[++i]);
        p_combustivel_min = atoi(argv[++i]);
        p_combustivel_max = atoi(argv[++i]);
        t_pouso_decolagem = atoi(argv[++i]);
        n_pistas = atoi(argv[++i]);
        t_remover_bagagens = atoi(argv[++i]);
        t_inserir_bagagens = atoi(argv[++i]);
        n_portoes = atoi(argv[++i]);
        n_max_avioes_esteira = atoi(argv[++i]);
        t_bagagens_esteira = atoi(argv[++i]);
        n_esteiras = atoi(argv[++i]);
        t_simulacao = atoi(argv[++i]);

    } else { // Número incorreto de argumentos
        printf("Todas as entradas são inteiros positivos!!\nUso:\n");
        printf("./aeroporto  NOVO_AVIAO_MIN  NOVO_AVIAO_MAX\n");
        printf("COMBUSTIVEL_MIN COMBUSTIVEL_MAX\n");
        printf("TEMPO_POUSO_DECOLAGEM  NUMERO_PISTAS  TEMPO_REMOVER_BAGAGENS\n");
        printf("TEMPO_INSERIR_BAGAGENS  NUMERO_PORTOES  MAXIMO_AVIOES_ESTEIRA\n");
        printf("TEMPO_BAGAGENS_ESTEIRA  NUMERO_ESTEIRAS  TEMPO_SIMULACAO\n");
        printf("----------OU----------\n");
        printf("./airport  NUMERO_PISTAS  NUMERO_PORTOES  MAXIMO_AVIOES_ESTEIRA  NUMERO_ESTEIRAS\n");
        return 0;
    }

    // Impressão com os parâmetros selecionados para simulação
    printf("Simulação iniciada com tempo total: %lu\n", t_simulacao);
    printf("Tempo para criação de aviões: %lu - %lu\n", t_novo_aviao_min, t_novo_aviao_max);
    printf("Número de pistas de pouso: %lu\n", n_pistas);
    printf("Tempo de pouso e decolagem: %lu\n", t_pouso_decolagem);
    printf("Número de portões de embarque: %lu\n", n_portoes);
    printf("Tempo de inserção (%lu) e remoção (%lu) de bagagens\n", t_inserir_bagagens, t_remover_bagagens);
    printf("Número de esteiras: %lu, com %lu aviões por esteira\n", n_esteiras, n_max_avioes_esteira);
    printf("Tempo das bagagens nas esteiras: %lu\n", t_bagagens_esteira);
    // Inicialização do aeroporto
    n_args = 8;
    size_t args[8] = {n_pistas, n_portoes, n_esteiras,
                n_max_avioes_esteira,
                t_pouso_decolagem, t_remover_bagagens,
                t_inserir_bagagens, t_bagagens_esteira};

    aeroporto_t* meu_aeroporto = iniciar_aeroporto(args, n_args);

    // Descreve aqui sua simulação usando as funções definidas no arquivo "aeroporto.h"
    // Lembre-se de implementá-las num novo arquivo "aeroporto.c"
    srand(clock());
    int proxAviao = ((rand() % (NOVO_AVIAO_MAX- NOVO_AVIAO_MIN)) + NOVO_AVIAO_MIN);
    int chegadaAviao = 0;
    int idaviao = 0;
    int numero_max_threads = TEMPO_SIMULACAO/NOVO_AVIAO_MIN;
    pthread_t* threads = malloc(sizeof(pthread_t)*numero_max_threads);

    for (int i = 0; i < TEMPO_SIMULACAO; ++i)
    {       
        // printf("%d\n",i);
        // printf("chegadaAviao: %d\n",chegadaAviao);
        // printf("proxAviao: %d\n",proxAviao);
        if (chegadaAviao == proxAviao)
        {   idaviao++;
            int combustivel = ((rand() % (COMBUSTIVEL_MAX - COMBUSTIVEL_MIN)) + COMBUSTIVEL_MIN);
            aviao_t* novoAviao = aloca_aviao(combustivel,idaviao);
            //printf("aviaum %d \n",&novoAviao );
            parametros_aviao* params = (parametros_aviao*) malloc(sizeof(parametros_aviao));
            params->aviao = novoAviao;
            params->aeroporto = meu_aeroporto;
            //pthread_create(novoAviao->thread, NULL, inicia_aproximacao, params);
            pthread_mutex_lock(meu_aeroporto->mutexFilaPouso);
            inserir(meu_aeroporto->fila_pouso, novoAviao);
            pthread_mutex_unlock(meu_aeroporto->mutexFilaPouso);
            pthread_create(&novoAviao->thread, NULL, inicia_aproximacao, (void *)params);
            chegadaAviao = 0;
            proxAviao = ((rand() % (NOVO_AVIAO_MAX- NOVO_AVIAO_MIN)) + NOVO_AVIAO_MIN);
            threads[idaviao-1] = novoAviao->thread;
        }
        chegadaAviao++;
    }

    for(int i=0; i < idaviao; i++) {
        //printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa%d \n",i);
        pthread_join(threads[i], NULL);
        //printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB%d \n",i+1);
    }
    return 1;
}
