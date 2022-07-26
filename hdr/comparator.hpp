#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Comparator variable declarations
extern std::vector <std::string> c_token;
extern std::string word_f;
extern std::string word_s;
extern bool tf;

// Comparator function declarations
extern bool fcs_comparator(std::vector <std::string> c_token,
                           std::string word_f, std::string word_s);

extern bool s_comparator(std::vector <std::string> c_token, std::string word_s);

#endif