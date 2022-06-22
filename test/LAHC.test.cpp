//
// Created by joao on 21/04/2022.
//


#include <catch2/catch.hpp>
#include <LAHC.h>


TEST_CASE("Caso de teste para LAHC", "[ALL]") {
    std::vector<std::vector<float>> d{{0,       13.8924, 21.0238, 32.5576, 17.2047},
                                      {13.8924, 0,       12.3693, 19.2094, 31.0644},
                                      {21.0238, 12.3693, 0,       15.2971, 37.0135},
                                      {32.5576, 19.2094, 15.2971, 0}};

    SECTION("LAHC") {
        int n = d.size();
        std::vector<int> s{0, 1, 2, 3};
        std::vector<int> e{1, 0, 2, 3};
        float fo = LAHC(n, s, d, 5, 10000);
        CHECK(fo == Approx(69.4227f).margin(0.1));
        REQUIRE_THAT(s, Catch::Approx(e));
    }

}
