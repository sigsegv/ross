#include <cmath>
#include "test_util.hpp"
#include <ross/ross.hpp>

TEST_CASE( "Test Line2 class", "[line2]" )
{
    // need to investigate why POD vector2f member variables is causing problem
    //REQUIRE(std::is_trivially_copyable<ross::line2f>::value);
    //REQUIRE(std::is_trivial<ross::line2f>::value);
    REQUIRE(std::is_standard_layout<ross::line2f>::value);
    //REQUIRE(std::is_pod<ross::line2f>::value);
    
    ross::line2f l0{{1.0, 1.0}, {2.0, 2.0}};
    ross::line2f l1 = l0 * 4.0;
    REQUIRE(l1.u.x == 4.0);
    REQUIRE(l1.u.y == 4.0);
    REQUIRE(l1.v.x == 8.0);
    REQUIRE(l1.v.y == 8.0);
    
    ross::line2f l2 = l0 + l1;
    REQUIRE(l2.u.x == 5.0);
    REQUIRE(l2.u.y == 5.0);
    REQUIRE(l2.v.x == 10.0);
    REQUIRE(l2.v.y == 10.0);
    
    ross::line2f l3{{0.0,0.0}, {10.0, 0.0}};
    REQUIRE(l3.magnitude() == Approx(10.0));
    ross::vector2f l3_normal = l3.normal().normalized();
    ross::vector2f l3_expected_normal{0.0, 1.0};
    REQUIRE(l3_normal == l3_expected_normal);
}
