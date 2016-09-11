#pragma once

#include <type_traits>
#include "catch.hpp"

template<typename T>
void require_pod_trivial()
{
    REQUIRE(std::is_constructible<T>::value);
    REQUIRE(std::is_trivially_constructible<T>::value);
    REQUIRE(std::is_nothrow_constructible<T>::value);
    
    
    REQUIRE(std::is_trivially_copyable<T>::value);
    REQUIRE(std::is_trivial<T>::value);
    REQUIRE(std::is_standard_layout<T>::value);
    REQUIRE(std::is_pod<T>::value);
}