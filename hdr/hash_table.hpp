#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

// Namespace r4_vectors
namespace r4_vectors{

    // Hash table for response type position vectors
    extern std::vector <std::string> fccs;

    extern std::vector <std::string> fscs;

} // End of r4_vectors namespace

// Namespace r3_vectors
namespace r3_vectors{

    // Hash table for response type position vectors
    extern std::vector <std::string> fcs;

} // End of r3_vectors namespace

// Namespace r1_vectors
namespace r1_vectors{

    // Hash table for response type position vectors
    extern std::vector <std::string> s;

} // End of r1_vectors namespace

#endif