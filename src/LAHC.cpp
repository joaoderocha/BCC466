//
// Created by joao on 12/11/2021.
//

#include <tuple>
#include "LAHC.h"
#include "Util.h"
#include "Descida.h"

using namespace std;

float LAHC(int n, vector<int> &s, float **d,
           int l,
           int m) {
    vector<tuple<float, vector<int>>> listaF(l);
    for (auto &it: listaF) {
        it = pair<float, vector<int>>(calcula_fo(n, s, d), s);
    }
    vector<int> s_star;
    int p = 0;
    int r = 0;
    int melhor_i = 0;
    int melhor_j = 0;

    float fo_s = calcula_fo(n, s, d);
    float fo = fo_s;

    while (r <= m) {
        fo = vizinho_aleatorio(n, s, d, fo, &melhor_i, &melhor_j);
        if (fo <= fo_s || fo < get<0>(listaF[p])) {
            if (fo < fo_s) {
                r = 0;
            }
            swap(s[melhor_i], s[melhor_j]);
            if (fo < fo_s) {
                s_star = s;
                fo_s = fo;
            }
        }
        listaF[p] = pair<float, vector<int>>(calcula_fo(n, s, d), s);
        p = (p + 1) % l;
        r += 1;
    }

    s = s_star;
    return fo_s;
}
