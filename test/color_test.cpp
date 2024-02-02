#include "lib/catch2/catch.hpp"
#include "primitives/color.hpp"
#include "test/test_utils.hpp"

TEST_CASE ("Color initializes properly when given hex color val") {

    SECTION ("constructors") {

        Color white = {{255.0 / 256, 255.0 / 256, 255.0 / 256}};
        Color black = {{0.0, 0.0, 0.0}};
        Color silver = {{0.75, 0.75, 0.75}};
        Color maroon {{0.5, 0.0, 0.0}};
        Color beige = {{245.0 / 256, 245.0 / 256, 220.0 / 256}};

        GIVEN ("a color initialized with 0xFFFFFF") {
            WHEN ("the color is constructed") {
                Color color { 0xFFFFFF };
                THEN ("the color is white") { compare_color(color, white); }
            }
        }

        GIVEN ("a color initialized with 0xFFFFFF") {
            WHEN ("the color is constructed") {
                Color color { 0x000000 };
                THEN ("the color is white") { compare_color(color, black); }
            }
        }

        GIVEN ("a color initialized with 0xC0C0C0") {
            WHEN ("the color is constructed") {
                Color color { 0xC0C0C0 };
                THEN ("the color is silver") { compare_color(color, silver); }
            }
        }

        GIVEN ("a color initialized with 0x800000") {
            WHEN ("the color is constructed") {
                Color color { 0x800000 };
                THEN ("the color is maroon") { compare_color(color, maroon); }
            }
        }

        GIVEN ("a color initialized with 0xF5F5DC") {
            WHEN ("the color is constructed") {
                Color color { 0xF5F5DC };
                THEN ("the color is beige") { compare_color(color, beige); }
            }
        }
    }
}
