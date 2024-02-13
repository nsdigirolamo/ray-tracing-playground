#include "lib/doctest/doctest.hpp"
#include "test/test_utils.hpp"

TEST_SUITE ("Color Tests") {

    Color expected_white = {{255.0 / 256, 255.0 / 256, 255.0 / 256}};
    Color expected_black = {{0.0, 0.0, 0.0}};
    Color expected_silver = {{0.75, 0.75, 0.75}};
    Color expected_maroon {{0.5, 0.0, 0.0}};
    Color expected_beige = {{245.0 / 256, 245.0 / 256, 220.0 / 256}};

    TEST_CASE ("white") {
        compare_color(expected_white, WHITE);
    }

    TEST_CASE ("black") {
        compare_color(expected_black, BLACK);
    }

    TEST_CASE ("silver") {
        compare_color(expected_silver, SILVER);
    }

    TEST_CASE ("maroon") {
        compare_color(expected_maroon, MAROON);
    }

    TEST_CASE ("beige") {
        compare_color(expected_beige, BEIGE);
    }
}