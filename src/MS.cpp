//
// Created by Puca Penna on 13/09/19.
//


#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "Descida.h"
#include "Util.h"
#include "Construcao.h"
#include "Arquivos.h"
#include "MS.h"


float MS(int n, std::vector<int> &s, float **d, int iter_max)
{
    float fo_star, fo, fo_aux;
    clock_t inicio_CPU, fim_CPU;
    vector<int> s_star;

    fo = fo_star = INT_MAX;
    limpa_arquivo((char*)"MS.txt");
    inicio_CPU = fim_CPU = clock();
    imprime_fo((char*)"MS.txt", (fim_CPU - inicio_CPU)/CLOCKS_PER_SEC,fo_star,0);
    int iter_aux = 1;
    while(iter_aux <= iter_max){
        ++iter_aux;
        constroi_solucao_aleatoria(n,s,d);
        fo_aux = calcula_fo(n,s,d);
        fo = descida_best_improvement(n,s,d);
        if (fo < fo_star){
            fo_star = fo;
            printf("Solucao Inicial: %f\n", fo_aux);
            printf("Solucao Final: %f\n", fo_star);
            printf("Iteracao: %i\n", iter_aux);
        }
    }

    fim_CPU = clock();
    imprime_fo((char*)"MS.txt", (fim_CPU - inicio_CPU)/CLOCKS_PER_SEC,fo_star,0);

    // atualiza s
    s = s_star;
    return fo_star;
}








