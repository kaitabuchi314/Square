#pragma once

#include <random>

namespace Square
{
    // Function to generate a random integer within a given range
    inline uint64_t RandomEntityUUID()
    {
        // Random device and generator
        std::random_device rd;  // Obtain a random number from hardware
        std::mt19937 gen(rd()); // Seed the generator
        std::uniform_int_distribution<uint64_t> distr((uint64_t)0, (uint64_t)18446744073709551615); // Define the range

        return distr(gen);
    }
}