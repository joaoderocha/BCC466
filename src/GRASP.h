//
// Created by Puca Penna on 03/10/19.
//

#ifndef _PCV_GRASP_H_
#define _PCV_GRASP_H_

#include <vector>

using namespace std;

float GRASP(int n, std::vector<int> &s, vector<vector<float>> &d, float alpha, int GRASP_max,
            void (*funcao_construcao)(int, std::vector<int> &, vector<vector<float>> &, float));

/* GRASP REATIVO */
float R_GRASP(int n, std::vector<int> &s, vector<vector<float>> &d, float alpha, int GRASP_max,
              void (*funcao_construcao)(int, std::vector<int> &, vector<vector<float>> &, float));

#endif //_PCV_C_GRASP_H_
