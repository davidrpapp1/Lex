#ifndef IF_MULTIPLE_PROCESSOR_H
#define IF_MULTIPLE_PROCESSOR_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Declaration of if processing function for ease of use
extern std::string variable;
extern std::vector <std::string> vect_variable;
extern std::vector <std::string> comparison;

// For if conditions with 'or' as a seperator
extern bool if_or_processor_hashtable(std::string variable, std::vector <std::string> comparison);

// For if conditions with 'and' as a seperator
extern bool if_aa_processor_vect(std::vector <std::string> vect_variable, std::vector <std::string> comparison);

#endif