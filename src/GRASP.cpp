//
// Created by Puca Penna on 03/10/19.
//

#include <cmath>
#include <iostream>
#include <ctime>
#include "GRASP.h"
#include "Construcao.h"
#include "Util.h"
#include "Descida.h"
#include "Arquivos.h"

float GRASP(int n, std::vector<int> &s, vector<vector<float>>& d, float alpha, int GRASP_max, void (*funcao_construcao)(int, std::vector<int>&, vector<vector<float>>&, float)) {
    vector<int> s_star;
    int iter = 0;
    float fo_star = INT16_MAX;
    float fo;

    while (iter < GRASP_max) {
        ++iter;
        funcao_construcao(n, s, d, alpha);
        fo = descida_best_improvement(n, s, d);
        if (fo < fo_star) {
            fo_star = fo;
            s_star = s;
            printf("Melhor solução: %f \n", fo_star);
        }
    }


    s = s_star;

    return fo_star;
}

/* ainda nao funciona */
float R_GRASP(int n, std::vector<int> &s, vector<vector<float>>& d, float alpha, int GRASP_max, void (*funcao_construcao)(int, std::vector<int>&, vector<vector<float>>&, float)){
    vector<int> s_star;
    int iter = 0;
    float fo_star = INT16_MAX;
    float novo_alpha = alpha;
    float fo, delta;


    while (iter < GRASP_max) {
        ++iter;
        funcao_construcao(n, s, d, novo_alpha);
        fo = descida_best_improvement(n, s, d);
        if (fo < fo_star) {
            delta = fo_star - fo;
            novo_alpha = exp(-delta/novo_alpha);
            fo_star = fo;
            s_star = s;
            printf("Delta: %f \n", delta);
            printf("Alpha: %f \n ", novo_alpha);
            printf("Melhor solução: %f \n \n", fo_star);
        }else{
            delta = fo - fo_star;
            printf("Delta: %f \n", delta);
            printf("Alpha: %f \n ", novo_alpha);
        }
    }

    s = s_star;
    return fo_star;
}