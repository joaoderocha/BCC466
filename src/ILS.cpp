#include "ILS.h"
#include "Descida.h"
#include "Util.h"

float perturbacao(int n, vector<int> &s, vector<vector<float>> &d, float fo, int nivel) {
    vector<int> s_parc = s;
    int melhor_i, melhor_j;
    int cont = 0;
    int fo_aux = 0;
    while (cont <= nivel) {
        fo_aux = vizinho_aleatorio(n, s_parc, d, fo, &melhor_i, &melhor_j);
        if (fo_aux < fo) {
            swap(s_parc[melhor_i], s_parc[melhor_j]);
        }
        cont += 1;
    }

    return calcula_fo(n, s_parc, d);
}


float ILS(int n, vector<int> &s, vector<vector<float>> &d,
          int nivel, // nro de vezes sem melhora em um dado nivel
          int ILSmax) {
    int iter = nivel = 0;
    int miter = iter;
    float fo, fo_star = 0;
    vector<int> s_star = s;
    fo_star = descida_best_improvement(n, s, d);
    while (iter - miter < ILSmax) {
        iter += 1;
        perturbacao(n, s, d, fo, nivel);
        fo = descida_best_improvement(n, s, d);
        if (fo < fo_star) {
            s_star = s;
            fo_star = fo;
            miter = iter;
            nivel = 1;
        } else {
            nivel += 1;
        }
    }

    return fo_star;
}


float SmartILS(int n, vector<int> &s, vector<vector<float>> &d,
               int nivel,
               int nVezesNivel,
               int ILSMax) {
    int nvezes;
    int iter = nivel = 0;
    int miter = iter;
    float fo, fo_star = 0;
    vector<int> s_star = s;
    fo_star = descida_best_improvement(n, s, d);
    while (iter - miter < ILSMax) {
        iter += 1;
        perturbacao(n, s, d, fo, nivel);
        fo = descida_best_improvement(n, s, d);
        if (fo < fo_star) {
            s_star = s;
            fo_star = fo;
            miter = iter;
            nivel = 1;
            nvezes = 1;
        } else {
            if (nvezes >= nVezesNivel) {
                nivel += 1;
                nvezes = 1;
            } else {
                nvezes += 1;
            }
        }
    }

    return fo_star;
}

