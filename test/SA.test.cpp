//
// Created by joao on 21/06/2022.
//


#include <catch2/catch.hpp>
#include <MS.h>
#include <unordered_set>
#include <SA.h>


TEST_CASE("Caso de teste para SA") {
    std::vector<std::vector<float>> d{{0,       13.8924, 21.0238, 32.5576, 17.2047},
                                      {13.8924, 0,       12.3693, 19.2094, 31.0644},
                                      {21.0238, 12.3693, 0,       15.2971, 37.0135},
                                      {32.5576, 19.2094, 15.2971, 0}};

    SECTION("SA") {
        int n = d.size();
        std::vector<int> s{0, 1, 2, 3};
        float temp = temperaturaInicial(n, s, d, 2, 0.95, 10 * n, 10);
        CHECK(temp == 80.0f);
        std::vector<int> e{2, 0, 1, 3};
        float fo = SA(n, s, d, 0.98, 50 * n, temp, 0.001);
        CHECK(fo == 69.42209f);
        REQUIRE_THAT(s, Catch::Approx(e));
    }
}
