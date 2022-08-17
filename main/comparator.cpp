// Libraries
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

// Header files
#include "../hdr/tokenisation.hpp"
#include "../hdr/comparator.hpp"

// fcs comparator function. Seeks function and subject words
bool fcs_comparator(std::vector <std::string> c_token,
                    std::string word_f, std::string word_s){

    bool tf = false;

    if(std::find(c_token.begin(), c_token.end(), word_f) != c_token.end()){
        if(std::find(c_token.begin(), c_token.end(), word_s) != c_token.end()){
            tf = true;
        }
    }

    return tf;

}

// s comparator function. Seeks subject words
bool s_comparator(std::vector <std::string> c_token, 
                  std::string word_s){

    bool tf = false;

    if(std::find(c_token.begin(), c_token.end(), word_s) != c_token.end()){
        tf = true;
    }

    return tf;

}