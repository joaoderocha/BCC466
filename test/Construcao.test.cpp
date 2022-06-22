//
// Created by joao on 21/06/2022.
//

#include <catch2/catch.hpp>
#include "vector"
#include <unordered_set>
#include "Construcao.h"


using namespace std;

TEST_CASE("Caso de teste para os métodos construtivos", "[ALL]") {
    vector<vector<float>> d{{0,       13.8924, 21.0238, 32.5576, 17.2047},
                            {13.8924, 0,       12.3693, 19.2094, 31.0644},
                            {21.0238, 12.3693, 0,       15.2971, 37.0135},
                            {32.5576, 19.2094, 15.2971, 0}};


    SECTION("constroi_solucao") {
        int n = 10;
        vector<int> s;
        constroi_solucao(n, s);
        REQUIRE(s.size() == n);
    };

    SECTION("constroi_solucao_gulosa_vizinho_mais_proximo") {

        int n = d.size();
        vector<int> s;
        vector<int> e{0, 2, 1, 3};
        constroi_solucao_gulosa_vizinho_mais_proximo(n, s, d);
        REQUIRE_THAT(s, Catch::Approx(e));
    }

    SECTION("constroi_solucao_aleatoria") {
        int n = 10;
        vector<int> s;
        constroi_solucao_aleatoria(n, s);

        unordered_set<int> t(s.begin(), s.end());
        REQUIRE(t.size() == n);
    };

    SECTION("constroi_solucao_parcialmente_gulosa_vizinho_mais_proximo") {

        int n = d.size();
        vector<int> s;
        vector<int> e{0, 1, 2, 3};
        constroi_solucao_parcialmente_gulosa_vizinho_mais_proximo(n, s, d, 0.1);
        REQUIRE_THAT(s, Catch::Approx(e));
    }

    SECTION("constroi_solucao_gulosa_insercao_mais_barata") {

        int n = d.size();
        vector<int> s;
        vector<int> e{0, 1, 3, 2};
        constroi_solucao_gulosa_insercao_mais_barata(n, &s, d);
        REQUIRE_THAT(s, Catch::Approx(e));
    };

    SECTION("constroi_solucao_parcialmente_gulosa_insercao_mais_barata") {

        int n = d.size();
        vector<int> s;
        vector<int> e{0, 1, 2, 3};
        constroi_solucao_parcialmente_gulosa_insercao_mais_barata(n, s, d, 0.1);
        REQUIRE_THAT(s, Catch::Approx(e));
    }
}