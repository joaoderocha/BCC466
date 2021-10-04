#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <utility> //funcao swap (para versao anterior a C11 usar <algorithm>)
#include <chrono>
#include "Arquivos.h"
#include "Construcao.h"
#include "Descida.h"
#include "Util.h"

using namespace std;

float calcula_delta(int n, vector<int> &s, float **d, int i, int j) {
    int i_antes, i_depois, j_antes, j_depois;

    i_antes = i - 1;
    i_depois = i + 1;
    j_antes = j - 1;
    j_depois = j + 1;
    if (i == 0) i_antes = n - 1;
    if (i == n - 1) i_depois = 0;
    if (j == 0) j_antes = n - 1;
    if (j == n - 1) j_depois = 0;

    float delta = d[s[i_antes]][s[i]] + d[s[i]][s[i_depois]] +
                  d[s[j_antes]][s[j]] + d[s[j]][s[j_depois]];
    return delta;


}

// Encontra o melhor vizinho utilizando o movimento de troca de posicao de duas cidades
float melhor_vizinho(int n, vector<int> &s, float **d, float fo, int *melhor_i, int *melhor_j) {
    float fo_melhor_viz = fo;

    float fo_viz;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // Calcula a variacao de custo com a realizacao do movimento
            float delta1 = calcula_delta(n, s, d, i, j);

            // Faz o movimento
            swap(s[i], s[j]);

            float delta2 = calcula_delta(n, s, d, i, j);

            // Calcular a nova distancia
            fo_viz = fo - delta1 + delta2;

            // Armazenar o melhor movimento (melhor troca)
            if (fo_viz < fo_melhor_viz) {
                *melhor_i = i;
                *melhor_j = j;
                fo_melhor_viz = fo_viz;
            }

            // desfaz o movimento
            swap(s[i], s[j]);
        }
    }
    // retornar a distancia do melhor vizinho
    return fo_melhor_viz;

}//melhor_vizinho

float first_improvement(int n, vector<int> &s, float **d, float fo, const int i, int *melhor_j) {
    float fo_melhor_viz = fo;

    float fo_viz;
    for (int j = i + 1; j < n; j++) {
        // Calcula a variacao de custo com a realizacao do movimento
        float delta1 = calcula_delta(n, s, d, i, j);

        // Faz o movimento
        swap(s[i], s[j]);

        float delta2 = calcula_delta(n, s, d, i, j);

        // Calcular a nova distancia
        fo_viz = fo - delta1 + delta2;

        // Armazenar o melhor movimento (melhor troca)
        if (fo_viz < fo_melhor_viz) {
            *melhor_j = j;
            return fo_viz;
        }

        // desfaz o movimento
        swap(s[i], s[j]);
    }

    return fo_melhor_viz;
}

//Vizinho aleatorio usado nas descidas e algumas meta-heurisiticas
float vizinho_aleatorio(int n, vector<int> &s, float **d, float fo, int *melhor_i, int *melhor_j) {
    float fo_viz;
    int i, j;
    float delta1, delta2;
    i = rand() % (n - 1);
    j = rand() % (n - 1);
    while(i == j)
        j = rand() % (n - 1);
    delta1 = calcula_delta(n, s, d, i, j);

    // Faz o movimento
    swap(s[i], s[j]);

    delta2 = calcula_delta(n, s, d, i, j);

    // Calcular a nova distancia
    fo_viz = fo - delta1 + delta2;

    // desfaz o movimento
    swap(s[i], s[j]);

    *melhor_j = j;
    *melhor_i = i;

    return fo_viz;

}//vizinho_aleatorio 

float best_improvement(int n, vector<int> &s, float **d, float fo, const int i, int *melhor_j) {
    float fo_melhor_viz = fo;

    float fo_viz;


    for (int j = i + 1; j < n; j++) {
        // Calcula a variacao de custo com a realizacao do movimento
        float delta1 = calcula_delta(n, s, d, i, j);

        // Faz o movimento
        swap(s[i], s[j]);

        float delta2 = calcula_delta(n, s, d, i, j);

        // Calcular a nova distancia
        fo_viz = fo - delta1 + delta2;

        // Armazenar o melhor movimento (melhor troca)
        if (fo_viz < fo_melhor_viz) {
            *melhor_j = j;
            fo_melhor_viz = fo_viz;
        }

        // desfaz o movimento
        swap(s[i], s[j]);
    }

    return fo_melhor_viz;
}

/* Método da descida com estrategia best improvement */
float descida_best_improvement(int n, vector<int> &s, float **d) {
    int melhor_i, melhor_j, iter;
    float fo_viz, fo;
    bool melhorou;
    clock_t inicio_CPU, fim_CPU;

    fo = fo_viz = calcula_fo(n, s, d);
    limpa_arquivo((char *) "DescidaBI.txt");
    inicio_CPU = fim_CPU = clock();
    iter = 0;
    imprime_fo((char *) "DescidaBI.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter);
    vector<int> nao_visitados;
    nao_visitados.reserve(n);
    for (int i = 0; i < n; ++i)
        nao_visitados.push_back(i);

    vector<int>::iterator ptr;
    for (ptr = nao_visitados.begin(); ptr < nao_visitados.end(); ptr++) {
        fo_viz = best_improvement(n, s, d, fo, *ptr, &melhor_j);
        if (fo_viz < fo) {
            swap(s[*ptr], s[melhor_j]);
        }
        nao_visitados.erase(ptr);
    }

    fo = calcula_fo(n, s, d);
    fim_CPU = clock();
    imprime_fo((char *) "DescidaBI.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter);
    return fo;
}//descida_best_improvement

float descida_randomica(int n, vector<int> &s, float **d, int IterMax) {
    int iter;
    float fo, fo_viz;

    int melhor_i, melhor_j;
    clock_t inicio_CPU, fim_CPU;

    fo = calcula_fo(n, s, d);
    iter = 0;
    limpa_arquivo((char *) "DescidaRandomica.txt");
    inicio_CPU = fim_CPU = clock();

    while (iter < IterMax) {
        iter++;
        fo_viz = vizinho_aleatorio(n,s,d,fo,&melhor_i,&melhor_j);
        if (fo > fo_viz){
            swap(s[melhor_i], s[melhor_j]);
        }
    }
    fo = calcula_fo(n, s, d);
    /* Implementar a impressão final (veja descida completa)*/
    fim_CPU = clock();
    imprime_fo((char *) "DescidaBI.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter);

    return fo;
}



float vizinho_first_improvement(int n, vector<int> &s, float **d, float fo, int *melhor_i, int *melhor_j) {
    float fo_melhor_viz = fo;
    bool melhorou = false;
    vector<int> vet;

    for (int i = 0; i < n; i++) vet.push_back(i);
    //Para c++ 11
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine r(seed);
    shuffle(vet.begin(), vet.end(), r);
    //Para c++ 98
    //random_shuffle ( vet.begin(), vet.end() );


    // retornar a distancia do melhor vizinho
    return fo_melhor_viz;

}//melhor_vizinho


float descida_first_improvement(int n, vector<int> &s, float **d) {
    int aux, melhor_i, melhor_j, iter;
    float fo_viz, fo;
    bool melhorou;
    clock_t inicio_CPU, fim_CPU;

    fo = fo_viz = calcula_fo(n, s, d);
    limpa_arquivo((char *) "DescidaFI.txt");
    inicio_CPU = fim_CPU = clock();
    iter = 0;
    imprime_fo((char *) "DescidaFI.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter);

    vector<int> nao_visitados;
    nao_visitados.reserve(n);
    for (int i = 0; i < n; ++i)
        nao_visitados.push_back(i);

    vector<int>::iterator ptr;
    for (ptr = nao_visitados.begin(); ptr < nao_visitados.end(); ptr++) {
        fo_viz = first_improvement(n, s, d, fo, *ptr, &melhor_j);
        if (fo_viz < fo) {
            swap(s[*ptr], s[melhor_j]);
        }
        nao_visitados.erase(ptr);
    }

    fo = calcula_fo(n, s, d);
    fim_CPU = clock();
    imprime_fo((char *) "DescidaBI.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter);


    fim_CPU = clock();
    imprime_fo((char *) "DescidaFI.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter);
    return fo;
}