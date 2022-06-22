//
// Created by joao on 21/04/2022.
//


#include <catch2/catch.hpp>
#include <BT.h>
#include <Descida.h>


TEST_CASE("Caso de teste para metodos descida") {
    vector<vector<float>> d{{0,       13.8924, 21.0238, 32.5576, 17.2047},
                            {13.8924, 0,       12.3693, 19.2094, 31.0644},
                            {21.0238, 12.3693, 0,       15.2971, 37.0135},
                            {32.5576, 19.2094, 15.2971, 0}};

    SECTION("descida_best_improvement") {
        int n = d.size();
        vector<int> s{0, 1, 2, 3};
        vector<int> e{0, 1, 3, 2};
        float fo = descida_best_improvement(n, s, d);
        REQUIRE_THAT(s, Catch::Approx(e));
        CHECK(fo == 69.4227f);
    }

    SECTION("descida_randomica") {
        srand(0);
        int n = d.size();
        vector<int> s{0, 1, 2, 3};
        vector<int> e{1, 0, 2, 3};
        float fo = descida_randomica(n, s, d, n ^ 2);
        REQUIRE_THAT(s, Catch::Approx(e));
        CHECK(fo == 69.4227f);
    }

    SECTION("descida_first_improvement") {
        int n = d.size();
        vector<int> s{0, 1, 2, 3};
        vector<int> e{0, 1, 2, 3};
        float fo = descida_first_improvement(n, s, d);
        REQUIRE_THAT(s, Catch::Approx(e));
        CHECK(fo == Approx(74.11639f).margin(0.2));
    }
}
