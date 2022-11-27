#ifndef RAW_HASH_TABLE_H
#define RAW_HASH_TABLE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

// Raw hash tables
extern std::vector <std::string> simple_query;

extern std::vector <std::string> debug_table;

// Word type categories
namespace types{

    extern std::vector <std::string> factual_type;

    extern std::vector <std::string> connector_type;
    
    extern std::vector <std::string> contextual_type;

    // Contextual flags
    extern bool your_flag;
    extern bool this_flag;
    extern bool current_flag;
    extern bool the_flag;

    extern std::vector <std::string> subject_type;

} // End of namespace types

// Rank 3 responses
namespace r3_responses{

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
    extern int fcs_how_it_cont_flag;

} // End of namespace r3_responses

// Namespace g_responses
namespace g_responses{

    extern std::vector <std::string> s_fcs_your_day;

    extern std::vector <std::string> s_fcs_the_day;

    extern std::vector <std::string> s_fcs_it;

    extern std::vector <std::string> s_fcs_that;

    extern std::vector <std::string> s_fcs_your_life;

    extern std::vector <std::string> s_fcs_the_life;

    extern std::vector <std::string> s_fcs_experience;

} // End of namespace g_responses

#endif