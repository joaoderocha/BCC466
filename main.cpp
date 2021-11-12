//---------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <ctime>
#include <iomanip>
#include <vector>
#include "src/Util.h"
#include "src/Arquivos.h"
#include "src/Construcao.h"
#include "src/Menus.h"
#include "src/Descida.h"
#include "src/MS.h"
#include "src/SA.h"
#include "src/GRASP.h"
#include "src/ILS.h"
#include "src/LAHC.h"

//---------------------------------------------------------------------------
using namespace std;

char *nome_arquivo_info = (char *) "/home/joao/CLionProjects/BCC466/data/c50info.txt";
char *nome_arquivo_data = (char *) "/home/joao/CLionProjects/BCC466/data/c50.txt";


int main(int argc, char *argv[]) {
    int n;                    // numero de cidades
    vector<int> s;            // vetor solucao corrente
    float **d,                // matriz de distancias entre as cidades
    fo,                 // funcao objetivo corrente
    melhor_fo_lit;      // melhor fo da literatura
    clock_t inicio_CPU,       // clock no inicio da aplicacao do metodo
    fim_CPU;          // clock no final da aplicacao do metodo
    int iterMax;

    int nind;
    float max_desvio;
    double prob_crossover;
    double prob_mutacao;
    float alpha = 0;

    float temp;

    //srand(1000); // pega o numero 1000 como semente de numeros aleatorios
    srand((unsigned) time(NULL)); // pega a hora do relogio como semente


    obter_parametros_pcv(nome_arquivo_info, &n, &melhor_fo_lit);
    d = cria_matriz_float(n, n); // matriz de distancias
    le_arq_matriz(nome_arquivo_data, n, d);


    int escolha = 0;
    do {
        escolha = menu_principal();
        switch (escolha) {
            case 0:
                printf("\n\nBye bye!!!\n\n");
                break;
            case 1: /* Geracao de uma solucao inicial */
                switch (menu_solucao_inicial()) {
                    case 1: /* Geracao gulosa de uma solucao inicial via metodo do vizinho mais proximo */
                        constroi_solucao_gulosa_vizinho_mais_proximo(n, s, d);
                        fo = calcula_fo(n, s, d);
                        printf("\nSolucao construida de forma gulosa (Vizinho Mais Proximo):\n");
                        imprime_rota(s, n);
                        printf("Funcao objetivo = %f\n", fo);
                        break;
                    case 2: /* Geracao parcialmente gulosa de uma solucao inicial via metodo do vizinho mais proximo */
                        alpha = 0.1;
                        constroi_solucao_parcialmente_gulosa_vizinho_mais_proximo(n, s, d, alpha);
                        fo = calcula_fo(n, s, d);
                        printf("\nSolucao construida de forma parcialmente gulosa (Vizinho Mais Proximo):\n");
                        imprime_rota(s, n);
                        printf("Funcao objetivo = %f\n", fo);
                        break;
                    case 3: /* Geracao gulosa de uma solucao inicial via metodo da insercao mais barata */
                        constroi_solucao_gulosa_insercao_mais_barata(n, &s, d);
                        fo = calcula_fo(n, s, d);
                        printf("\nSolucao construida de forma gulosa (Insercao Mais Barata):\n");
                        imprime_rota(s, n);
                        printf("Funcao objetivo = %f\n", fo);
                        break;
                    case 4: /* Geracao parcialmente gulosa de uma solucao inicial via insercao mais barata */
                        printf("Ainda nao implementado...\n");
                        break;
                    case 5: /* Geracao aleatoria de uma solucao inicial */
                        constroi_solucao_aleatoria(n, s, d);
                        fo = calcula_fo(n, s, d);
                        printf("\nSolucao construida de forma aleatoria:\n");
                        imprime_rota(s, n);
                        printf("Funcao objetivo = %f\n", fo);
                        break;
                }
                break;
            case 2: /* Descida com estrategia best improvement*/
                inicio_CPU = clock();
                fo = descida_best_improvement(n, s, d);
                fim_CPU = clock();
                printf("\nSolucao obtida usando a estrategia Best Improvement do Metodo da Descida:\n");
                imprime_rota(s, n);
                printf("Funcao objetivo = %f\n", fo);
                printf("Tempo de CPU = %f segundos:\n", (double) (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC);
                break;

            case 3: /* Descida Randomica */
                inicio_CPU = clock();
                fo = descida_randomica(n, s, d, n ^ 2);
                fim_CPU = clock();
                printf("\nSolucao obtida usando a estrategia First Improvement do Metodo da Descida:\n");
                imprime_rota(s, n);
                printf("Funcao objetivo = %f\n", fo);
                printf("Tempo de CPU = %f segundos:\n", (double) (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC);
                break;

            case 4: /* Descida com primeiro de melhora */
                inicio_CPU = clock();
                fo = descida_first_improvement(n, s, d);
                fim_CPU = clock();
                printf("\nSolucao obtida usando a estrategia First Improvement do Metodo da Descida:\n");
                imprime_rota(s, n);
                printf("Funcao objetivo = %f\n", fo);
                printf("Tempo de CPU = %f segundos:\n", (double) (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC);
                break;

            case 5: /* Multi-Start */
                inicio_CPU = clock();
                fo = MS(n, s, d, 10 * n);
                fim_CPU = clock();
                printf("\nSolucao obtida usando a estrategia Multi-Start:\n");
                imprime_rota(s, n);
                printf("Funcao objetivo = %f\n", fo);
                printf("Tempo de CPU = %f segundos:\n", (double) (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC);
                break;

            case 6: /* Simulated Annealing */
                inicio_CPU = clock();
                temp = temperaturaInicial(n, s, d, 2, 0.95, 10 * n, 10);
                printf("tempo: %f ", temp);
                fo = SA(n, s, d, 0.98, 50 * n, temp, 0.001);
                fim_CPU = clock();
                printf("\nSolucao obtida usando a estrategia Simulated Annealing:\n");
                imprime_rota(s, n);
                printf("Funcao objetivo = %f\n", fo);
                printf("Tempo de CPU = %f segundos:\n", (double) (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC);
                break;

            case 7: /* Busca Tabu */
                printf("Nao implementado\n");
                break;

            case 8: /* Iterated Local Search */
                switch (menu_ILS()) {
                    case 1:
                        inicio_CPU = clock();
                        fo = ILS(n,s,d, 5,10);
                        fim_CPU = clock();
                        printf("\nSolucao obtida usando a estrategia Iterated Local Search:\n");
                        break;
                    case 2:
                        inicio_CPU = clock();
                        fo = SmartILS(n,s,d, 5,5,10);
                        fim_CPU = clock();
                        printf("\nSolucao obtida usando a estrategia Smart Iterated Local Search:\n");
                        break;
                }
                imprime_rota(s, n);
                printf("Funcao objetivo = %f\n", fo);
                printf("Tempo de CPU = %f segundos:\n", (double) (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC);
                break;

            case 9: /* GRASP */
                void (*funcao_construcao)(int, vector<int> &, float**, float);
                float (*funcao_grasp)(int, std::vector<int> &, float **, float , int , void (*)(int, std::vector<int>&, float**, float));
                switch (menu_GRASP_2()) {
                    case 1:
                        funcao_grasp = &GRASP;
                        break;
                    case 2:
                        funcao_grasp = &R_GRASP;
                        break;
                }
                switch (menu_GRASP()) {
                    case 1:
                        funcao_construcao = &constroi_solucao_parcialmente_gulosa_vizinho_mais_proximo;
                        break;
                    case 2:
                        funcao_construcao = &constroi_solucao_parcialmente_gulosa_insercao_mais_barata;
                        break;
                }
                inicio_CPU = clock();
                fo = funcao_grasp(n, s, d, 0.40, n * 10, funcao_construcao);
                fim_CPU = clock();
                printf("\nSolucao obtida usando a estrategia GRASP:\n");
                imprime_rota(s, n);
                printf("Funcao objetivo = %f\n", fo);
                printf("Tempo de CPU = %f segundos:\n", (double) (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC);
                break;

            case 10: /* VND */
                printf("Nao implementado\n");
                break;

            case 11: /* VNS */
                printf("Nao implementado\n");
                break;

            case 12: /* Algoritmos Geneticos */
                switch (menu_AG()) {
                    case 1: /* Algoritmos Geneticos usando operador OX */
                        printf("Nao implementado\n");
                        break;
                    case 2: /* Algoritmos Geneticos usando operador ERX */
                        printf("Nao implementado\n");
                        break;
                }
                break;

            case 13: /* LAHC */
                inicio_CPU = clock();
                printf("tempo: %f ", temp);
                fo = LAHC(n,s,d,5,10000);
                fim_CPU = clock();
                printf("\nSolucao obtida usando a estrategia Simulated Annealing:\n");
                imprime_rota(s, n);
                printf("Funcao objetivo = %f\n", fo);
                printf("Tempo de CPU = %f segundos:\n", (double) (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC);
                break;

            case 14: /* Algoritmos Memeticos */
                printf("\n Algoritmos Memeticos ainda nao implementado ... \n");
                break;

            case 15: /* Colonia de Formigas */
                printf("\n Colonia de Formigas ainda nao implementado ... \n");
                break;

            default:
                printf("\n Opcao invalida ... \n");
                break;
        }
    } while (escolha != 0);


    //libera_vetor(s);
    libera_matriz_float(d, n);
    return 0;
}


//---------------------------------------------------------------------------
