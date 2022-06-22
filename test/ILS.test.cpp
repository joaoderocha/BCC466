//
// Created by joao on 21/04/2022.
//


#include <catch2/catch.hpp>
#include <ILS.h>


TEST_CASE("Caso de teste para ILS") {
    std::vector<std::vector<float>> d{{0,       13.8924, 21.0238, 32.5576, 17.2047},
                                      {13.8924, 0,       12.3693, 19.2094, 31.0644},
                                      {21.0238, 12.3693, 0,       15.2971, 37.0135},
                                      {32.5576, 19.2094, 15.2971, 0}};

    SECTION("ILS") {
        int n = d.size();
        std::vector<int> s{0, 1, 2, 3};
        std::vector<int> e{0, 1, 3, 2};
        float fo = ILS(n, s, d, 5, 10);
        CHECK(fo == 69.4227f);
        REQUIRE_THAT(s, Catch::Approx(e));
    }

    SECTION("SmartILS") {
        int n = d.size();
        std::vector<int> s{0, 1, 2, 3};
        std::vector<int> e{0, 1, 3, 2};
        float fo = SmartILS(n, s, d, 5, 5, 10);
        CHECK(fo == 69.4227f);
        REQUIRE_THAT(s, Catch::Approx(e));
    }
}
