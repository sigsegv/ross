#pragma once

#include <cmath>
#include <ostream>
#include "ross.hpp"

namespace ross
{
    
/**
 * Immutable type to represent colors by various channels, each of which is measured in intensity from 0.0 to 1.0
 */
template<uint8_t kChannels>
class color
{
public:
    /**
     * Each channel is a value from 0.0 (minimum intensity) to 1.0 (maximum intensity) inclusive.
     */
    const real_t m_channels[kChannels];
    
    /**
     * Access channel
     */
    constexpr real_t operator[](uint8_t channel) const
    {
        return m_channels[channel];
    }
    /**
     * Get the number of channels in this color
     */
    constexpr uint8_t size() const
    {
        return kChannels;
    }
};
    
}