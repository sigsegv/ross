#include "test_util.hpp"
#include <ross/ross.hpp>

TEST_CASE( "Test Color class", "[color]" )
{
    require_pod_trivial<ross::color_rgb>();
    ross::color_rgb magenta{ {1.0, 0.0, 1.0} };
    REQUIRE(magenta.size() == 3);
    REQUIRE(magenta[0] == 1.0);
    REQUIRE(magenta[1] == 0.0);
    REQUIRE(magenta[2] == 1.0);
}
