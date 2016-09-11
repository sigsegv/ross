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
//    const vector2<T> u;
//    const vector2<T> v;
    
    /**
     * The length of this line
     *
     * @returns the length of this line
     */
//    real_t magnitude() const
//    {
//        // TODO make constexpr
//        return (v - u).magnitude();
//    }
    
    /**
     * Get a normal vector of this line
     *
     * @returns one of the two possible normal vectors
     */
//    vector2<real_t> normal() const
//    {
//        return {v.x-u.x, v.y-u.y};
//    }
};

//template<typename T>
//std::ostream& operator<<(std::ostream& os, const line2<T>& l)
//{
//    return os << "<" << l.v << ", " << l.u << ">";
//}

}