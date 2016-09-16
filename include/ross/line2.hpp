#pragma once

namespace ross
{
/**
 * Immutable POD 2D Line Segment between points u and v
 */
template<typename T>
class line2
{
public:
    const vector2<T> u;
    const vector2<T> v;
    
    /**
     * The length of this line
     *
     * @returns the length of this line
     */
    real_t magnitude() const
    {
        // TODO make constexpr
        return (v - u).magnitude();
    }
    
    /**
     * Get a normal vector of this line
     *
     * @returns one of the two possible normal vectors
     */
    constexpr vector2<real_t> normal() const noexcept
    {
        return {-(v.y-u.y), v.x-u.x};
    }
    
    constexpr line2 operator+(const line2& rhs) const noexcept
    {
        return line2{u + rhs.u, v + rhs.v};
    }
    
    constexpr line2 operator-(const line2& rhs) const noexcept
    {
        return line2{u - rhs.u, v - rhs.v};
    }
    
    constexpr line2 operator-() const noexcept
    {
        return line2{-u, -v};
    }
    
    constexpr line2 operator*(T d) const noexcept
    {
        return line2{u * d, v * d};
    }
    
    constexpr line2 operator/(T d) const noexcept
    {
        return line2{u / d, v / d};
    }
    
    constexpr bool operator!=(const line2& rhs) const noexcept
    {
        return !(*this==rhs);
    }
    
    constexpr bool operator==(const line2& rhs) const noexcept
    {
        return u == rhs.u && v == rhs.v;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const line2<T>& l)
{
    return os << "<" << l.u << ", " << l.v << ">";
}

}