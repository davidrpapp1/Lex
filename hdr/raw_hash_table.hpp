#ifndef RAW_HASH_TABLE_H
#define RAW_HASH_TABLE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

// Raw hash tables
extern std::string simple_query[6];

extern std::string debug_table[6];

// Word type categories
namespace r3_types{

    extern std::vector <std::string> factual_type;

    extern std::vector <std::string> connector_type;

    extern std::vector <std::string> subject_type;

} // End of namespace r3_categories

// Rank 3 responses
namespace r3_responses{
    
    // Continuation flag for r3 responses enumerated by commented numbers
    extern std::vector <bool> continuation_flag;

    // 1
    extern std::vector <std::string> fcs_how_you;

    // 2
    extern std::vector <std::string> fcs_what_you;

    // 3
    extern std::vector <std::string> fcs_who_you;

    // 4
    extern std::vector <std::string> fcs_where_you;

    // 5
    extern std::vector <std::string> fcs_when_you;

    // 6
    extern std::vector <std::string> fcs_how_it;

} // End of namespace r3_responses

#endif