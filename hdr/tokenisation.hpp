#ifndef TOKENISATION_H
#define TOKENISATION_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Tokenisation containers
extern std::string query_upper;
extern std::vector <std::string> type_position;
extern std::vector <std::string> token;

// Tokenisation functions
extern std::vector <std::string> r3_parse_tokenisation(std::vector <std::string> token);
extern std::vector <std::string> tokenise(std::string query_upper);

#endif