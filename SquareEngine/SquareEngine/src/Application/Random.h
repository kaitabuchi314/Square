#pragma once

#include <random>

namespace Square
{
    // Function to generate a random integer within a given range
    inline uint32_t RandomEntityUUID()
    {
        // Random device and generator
        std::random_device rd;  // Obtain a random number from hardware
        std::mt19937 gen(rd()); // Seed the generator
        std::uniform_int_distribution<uint64_t> distr((uint32_t)0, (uint32_t)4294967295); // Define the range

        return distr(gen);
    }
}