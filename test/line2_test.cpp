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
    
    ross::line2f l0{{1.0,1.0}, {1.0, 1.0}};
    ross::line2f l1{{2.0,2.0}, {1.0, 1.0}};
    ross::line2f l2{{3.0,0.0}, {0.0, 1.0}};
    ross::line2f::line_intersect_result result0 = l0.intersect(l1);
    ross::line2f::line_intersect_result result1 = l0.intersect(l2);
    
    REQUIRE(!result0.valid);
    REQUIRE(result1.valid);
    ross::vector2f expected_intersect{3.0,3.0};
    REQUIRE(result1.point == expected_intersect);
    
    ross::line2f l3{{0.0,0.0}, {10.0, 0.0}};
    ross::vector2f l3_normal = l3.normal().unit();
    ross::vector2f l3_expected_normal{0.0, 1.0};
    REQUIRE(l3_normal == l3_expected_normal);
}
