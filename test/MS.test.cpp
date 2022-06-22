//
// Created by joao on 21/06/2022.
//


#include <catch2/catch.hpp>
#include <MS.h>
#include <unordered_set>


TEST_CASE("Caso de teste para Multi Start") {
    std::vector<std::vector<float>> d{{0,       13.8924, 21.0238, 32.5576, 17.2047},
                                      {13.8924, 0,       12.3693, 19.2094, 31.0644},
                                      {21.0238, 12.3693, 0,       15.2971, 37.0135},
                                      {32.5576, 19.2094, 15.2971, 0}};

    SECTION("MS") {
        int n = d.size();
        std::vector<int> s;
        std::vector<int> e{3, 2, 0, 1};
        MS(n, s, d, 10 * n);
        std::unordered_set<int> t(s.begin(), s.end());
        REQUIRE(t.size() == n);
    }
}
