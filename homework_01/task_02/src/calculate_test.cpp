#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "utils.hpp"

TEST_CASE("Calculate", "[simple_sum]") {
  CHECK(Calculate("1+2") == 3);
  CHECK(Calculate("2+2") == 4);
  CHECK(Calculate("1+0") == 1);
  CHECK(Calculate("0+0") == 0);
}

TEST_CASE("Calculate", "[simple_difference]") {
  CHECK(Calculate("5-2") == 3);
  CHECK(Calculate("2-2") == 0);
  CHECK(Calculate("1-0") == 1);
  CHECK(Calculate("0-0") == 0);
}

TEST_CASE("Calculate", "[simple_multiply]") {
  CHECK(Calculate("5*2") == 10);
  CHECK(Calculate("2*2") == 4);
  CHECK(Calculate("1*0") == 0);
  CHECK(Calculate("1*3") == 3);
}

TEST_CASE("Calculate", "[strange]") {
  REQUIRE_THAT(Calculate("2*4-8+11/3"),
               Catch::Matchers::WithinRel(11.0 / 3.0, 0.001));
  REQUIRE_THAT(Calculate("6*(7-2)-8"), Catch::Matchers::WithinRel(22, 0.001));
  REQUIRE_THAT(Calculate("2*(12-2*(4+5/2)-8)+1"),
               Catch::Matchers::WithinRel(
                   2 * (12 - 2.0 * (4 + 5.0 / 2.0) - 8) + 1, 0.001));
  REQUIRE_THAT(
      Calculate("3*(12-2*(4+5/2-(8+3)/2)-8)+1"),
      Catch::Matchers::WithinRel(
          3 * (12 - 2 * (4 + 5.0 / 2 - (8 + 3) / 2.0) - 8) + 1, 0.001));
}
