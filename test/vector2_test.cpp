#include <cmath>
#include "test_util.hpp"
#include <ross/ross.hpp>

TEST_CASE( "Test Vector2 class", "[vector2]" )
{
    log_type_properties<ross::vector2f>();
    
    require_pod_trivial<ross::vector2f>();
    
    ross::vector2f v0 {2.0, 0.0};
    ross::vector2f v1 {0.0, 3.0};
    ross::vector2f v2 {1.0, 1.0};
    ross::vector2f v3 {-1.0, -1.0};
    
    ross::vector2f v4 = v0 + v1;
    REQUIRE(v4.x == 2.0);
    REQUIRE(v4.y == 3.0);
    REQUIRE(v4.magnitude() == std::sqrt(std::pow(v4.x, 2.0) + std::pow(v4.y, 2.0)));
    
    ross::vector2f v4_unit = v4.normalized();
    REQUIRE(v4_unit.magnitude() == 1.0);
    
    REQUIRE(v4.dot(v2) == 5.0);
    
    REQUIRE(v2.distance(v3) == Approx(2.8284271247461903));
    
    REQUIRE(v2.angle(ross::vector2f{1.0, 0.0}) == Approx(ross::kPI_4));
    
}
