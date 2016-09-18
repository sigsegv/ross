#include <cmath>
#include "test_util.hpp"
#include <ross/ross.hpp>

TEST_CASE( "Test bbox class", "[bbox]" )
{
    ross::bboxui b0{{1, 1},{2,2}};
    ross::bboxui b1  = b0;
    
    REQUIRE(b0.left() == 1);
    REQUIRE(b0.top() == 1);
    REQUIRE(b0.right() == 2);
    REQUIRE(b0.bottom() == 2);
    
    ross::line2ui bottom_edge = b0.bottom_edge();
    REQUIRE(bottom_edge.u.x == 1);
    REQUIRE(bottom_edge.u.y == 2);
    REQUIRE(bottom_edge.v.x == 2);
    REQUIRE(bottom_edge.v.y == 2);
    
    ross::bboxui b2({3,3},{6,6});
    ross::bboxui b3({5,5},{7,7});
    ross::bboxui b4({7,7},{8,8});
    
    ross::bboxui b5 = b2.u(b3);
    REQUIRE(b5.left() == 3);
    REQUIRE(b5.top() == 3);
    REQUIRE(b5.right() == 7);
    REQUIRE(b5.bottom() == 7);
    
    ross::bboxui b6 = b5.intersect(b4);
    REQUIRE(b6.area() == 0);
    REQUIRE(b6.is_empty());
    REQUIRE(!b0.is_empty());
}
