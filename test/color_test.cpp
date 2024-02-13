#include "lib/doctest/doctest.hpp"
#include "test/test_utils.hpp"

TEST_SUITE ("Color Tests") {

    Color expected_white = {{255.0 / 256, 255.0 / 256, 255.0 / 256}};
    Color expected_black = {{0.0, 0.0, 0.0}};
    Color expected_silver = {{0.75, 0.75, 0.75}};
    Color expected_maroon {{0.5, 0.0, 0.0}};
    Color expected_beige = {{245.0 / 256, 245.0 / 256, 220.0 / 256}};

    TEST_CASE ("white") {
        CHECK_COLOR(expected_white, WHITE);
    }

    TEST_CASE ("black") {
        CHECK_COLOR(expected_black, BLACK);
    }

    TEST_CASE ("silver") {
        CHECK_COLOR(expected_silver, SILVER);
    }

    TEST_CASE ("maroon") {
        CHECK_COLOR(expected_maroon, MAROON);
    }

    TEST_CASE ("beige") {
        CHECK_COLOR(expected_beige, BEIGE);
    }
}