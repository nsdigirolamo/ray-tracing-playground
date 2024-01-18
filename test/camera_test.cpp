#include "camera.hpp"
#include "lib/catch2/catch.hpp"
#include "test/test_utils.hpp"

TEST_CASE ("camera initializes correctly") {
    SECTION ("camera initializes with the correct members calculated") {
        GIVEN ("a camera") {

                Point location {{0, 0, 0}};
                int image_height = 1080;
                int image_width = 1920;
                double horizontal_fov = 90;
                double yaw = 0;

                Camera camera {
                    location,
                    image_height,
                    image_width,
                    horizontal_fov,
                    yaw
                };

            WHEN ("the camera is initialized with a 90 degree FOV") {

                double vertical_fov = 58.71551;
                double view_width = 1.41421;
                double view_height = 0.79550;
                double focal_length = 0.70711;
                Matrix<3, 3> rotation_identity = identity(camera.rotation_matrix);

                THEN ("the vertical FOV is properly calculated") {

                    CHECK(camera.getVerticalFOV() == Approx(vertical_fov));

                } AND_THEN ("the view width is properly calculated") {

                    CHECK(camera.getViewWidth() == Approx(view_width));

                } AND_THEN ("the view height is properly calculated") {

                    CHECK(camera.getViewHeight() == Approx(view_height));

                } AND_THEN ("the focal length is properly calculated") {

                    CHECK(camera.getFocalLength() == Approx(focal_length));

                } AND_THEN ("the rotation matrix is the identity matrix") {

                    compare_matrix(camera.rotation_matrix, rotation_identity);

                }
            }
        }
    }
}