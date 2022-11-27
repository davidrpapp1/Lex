#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

// Variable declarations
std::string query, query_upper;
extern bool c_tf;
int layer;

// Token parsing
std::vector <std::string> token;
std::string intermediate;

// Word position vectors
std::vector <std::string> type_position;

// String called 'line' holds instantaneous strings of text from the reservoir
std::string line;

#endif 