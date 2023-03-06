#include "catch2/catch.hpp"
#include "sudoku/sudoku.hpp"

using namespace sudoku;

TEST_CASE("add_one", "[adder]") {
    REQUIRE(add_one(0) == 1);
    REQUIRE(add_one(123) == 124);
    REQUIRE(add_one(-1) == 0);
}
