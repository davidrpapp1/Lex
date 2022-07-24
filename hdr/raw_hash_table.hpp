#ifndef RAW_HASH_TABLE_H
#define RAW_HASH_TABLE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

// Raw hash tables
std::string simple_query[6]={"HELLO", "HI", "HI CITHRIA", "HELLO CITHRIA", "HI, CITHRIA", "HELLO, CITHRIA"};

std::string debug_table[6]={"DISPLAY ERROR STATUS", "ERROR STATUS", "CITHRIA, DISPLAY ERROR STATUS", 
                            "CITHRIA DISPLAY ERROR STATUS", "CITHRIA, ERROR STATUS", "CITHRIA ERROR STATUS"};

// Word type categories
namespace r3_types{

    std::vector <std::string> factual_type{"HOW", "WHAT", "WHO", "WHEN", "WHERE"};

    std::vector <std::string> connector_type{"IS", "ARE"};

    std::vector <std::string> subject_type{"YOU", "IT", "THAT"};

} // End of namespace r3_categories

// Rank 3 responses
namespace r3_responses{

    std::vector <std::string> fcs_how_you{"Good, although it is unlikely I have feelings...", "Good, I think?", 
                                          "I am doing well thank you.", "Thank you for asking, I am doing good.",
                                          "Nice of you to ask, I am well thank you."};

    std::vector <std::string> fcs_what_you{"I am a personal assistant designed for contextual understanding.",
                                           "I am an artificial intelligence capable of contextual understanding.",
                                           "I was made to be an artificial intelligence designed around contextual understanding.",
                                           "My creators designed me as a personal assistant with contextual understanding."};

} // End of namespace r3_responses

#endif