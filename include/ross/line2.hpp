#pragma once

namespace ross
{
/**
 * Immutable POD 2D Line starting at U and in direction V
 */
template<typename T>
class line2
{
public:
    const vector2<T> u;
    const vector2<T> v;
    
    /**
     * Get a normal vector of this line
     *
     * @returns one of the two possible normal vectors
     */
    constexpr vector2<real_t> normal() const noexcept
    {
        return v.normal();
    }
    
//    constexpr line2 operator+(const line2& rhs) const noexcept
//    {
//        return line2{u + rhs.u, v + rhs.v};
//    }
//    
//    constexpr line2 operator-(const line2& rhs) const noexcept
//    {
//        return line2{u - rhs.u, v - rhs.v};
//    }
//    
//    constexpr line2 operator-() const noexcept
//    {
//        return line2{-u, -v};
//    }
//    
//    constexpr line2 operator*(T d) const noexcept
//    {
//        return line2{u * d, v * d};
//    }
//    
//    constexpr line2 operator/(T d) const noexcept
//    {
//        return line2{u / d, v / d};
//    }
    
    constexpr bool operator!=(const line2& rhs) const noexcept
    {
        return !(*this==rhs);
    }
    
    constexpr bool operator==(const line2& rhs) const noexcept
    {
        return u == rhs.u && v == rhs.v;
    }
    
    /**
     * Data structure returned from an intersection test.
     * point only valid if valid is true. If no intersection
     * at all, valid is false.
     */
    struct line_intersect_result
    {
        bool valid;
        vector2<T> point;
    };
    
    /**
     * Get intersection of two lines (planes)
     *
     * @param other line to find intersection of
     * @returns intersection result structure
     */
    constexpr line_intersect_result intersect(const line2<T>& other) const noexcept
    {
        const vector2<T> ln = normal();
        const real_t denom = ln.dot(other.v);
        if(denom == 0.0) return line_intersect_result{false, {0,0}};
        
        const T lc = get_implicit_c();
        const real_t d = ln.dot(other.u);
        const vector2<T> p = other.u - other.v * ((ln.dot(other.u)+lc)/denom);
        
        return line_intersect_result{true, p};
    }
    
private:
    constexpr T get_implicit_c() const noexcept
    {
        return normal().dot(u);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const line2<T>& l)
{
    return os << "<" << l.u << ", " << l.v << ">";
}

}