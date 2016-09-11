#pragma once

#include <iostream>
#include <typeinfo>
#include <type_traits>
#include "catch.hpp"

template<typename T>
void log_type_properties()
{
    std::cout /*<< T::typeinfo::name() << "\n"*/ << std::boolalpha
    << "is_constructible " << std::is_constructible<T>::value << "\n"
    << "is_trivially_constructible " << std::is_trivially_constructible<T>::value << "\n"
    << "is_nothrow_constructible " << std::is_nothrow_constructible<T>::value << "\n"
    
    << "is_default_constructible " << std::is_default_constructible<T>::value << "\n"
    << "is_trivially_default_constructible " << std::is_trivially_default_constructible<T>::value << "\n"
    << "is_nothrow_default_constructible " << std::is_nothrow_default_constructible<T>::value << "\n"
    
    << "is_copy_constructible " << std::is_copy_constructible<T>::value << "\n"
    << "is_trivially_copy_constructible " << std::is_trivially_copy_constructible<T>::value << "\n"
    << "is_nothrow_copy_constructible " << std::is_nothrow_copy_constructible<T>::value << "\n"
    
    << "is_move_constructible " << std::is_move_constructible<T>::value << "\n"
    << "is_trivially_move_constructible " << std::is_trivially_move_constructible<T>::value << "\n"
    << "is_nothrow_move_constructible " << std::is_nothrow_move_constructible<T>::value << "\n"
    
    << "is_assignable " << std::is_assignable<T, T>::value << "\n"
    << "is_trivially_assignable " << std::is_trivially_assignable<T, T>::value << "\n"
    << "is_nothrow_assignable " << std::is_nothrow_assignable<T, T>::value << "\n"
    
    << "is_copy_assignable " << std::is_copy_assignable<T>::value << "\n"
    << "is_trivially_copy_assignable " << std::is_trivially_copy_assignable<T>::value << "\n"
    << "is_nothrow_copy_assignable " << std::is_nothrow_copy_assignable<T>::value << "\n"
    
    << "is_move_assignable " << std::is_move_assignable<T>::value << "\n"
    << "is_trivially_move_assignable " << std::is_trivially_move_assignable<T>::value << "\n"
    << "is_nothrow_move_assignable " << std::is_nothrow_move_assignable<T>::value << "\n"
    
    << "is_destructible " << std::is_destructible<T>::value << "\n"
    << "is_trivially_destructible " << std::is_trivially_destructible<T>::value << "\n"
    << "is_nothrow_destructible " << std::is_nothrow_destructible<T>::value << "\n"
    
    << "is_trivial " << std::is_trivial<T>::value << "\n"
    << "is_trivially_copyable " << std::is_trivially_copyable<T>::value << "\n"
    << "is_standard_layout " << std::is_standard_layout<T>::value << "\n"
    << "is_pod " << std::is_pod<T>::value << "\n";
}

template<typename T>
void require_pod_trivial()
{
    REQUIRE(std::is_trivially_copyable<T>::value);
    REQUIRE(std::is_trivial<T>::value);
    REQUIRE(std::is_standard_layout<T>::value);
    REQUIRE(std::is_pod<T>::value);
}