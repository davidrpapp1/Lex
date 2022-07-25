// Libraries
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>

// Header files
#include "../hdr/hash_table.hpp"
#include "../hdr/tokenisation.hpp"
#include "../hdr/raw_hash_table.hpp"

std::vector <std::string> r3_tokenise(std::string query_upper){

    // Remove potential inconsistencies from input string
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '?'), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), ','), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '.'), query_upper.end());

    // Intermediate tokenisation container
    std::stringstream tokenisation(query_upper);
    std::string intermediate;
                
    // Tokenise and vectorise string
    while(getline(tokenisation, intermediate, ' ')){
        token.push_back(intermediate);
    }

    return token;

}

std::vector <std::string> r3_parse_tokenisation(std::vector <std::string> token){

    // Look for string vector match
    for(int i=0; i<token.size(); i++){
                    
        // Comparison with rank 3 factual type functions
        for(int n=0; n<r3_types::factual_type.size(); n++){

            if(token[i]==r3_types::factual_type[n]){
                            
                type_position.push_back("f"); // Factual

            }

        }

        // Comparison with rank 3 connector type functions
        for(int n=0; n<r3_types::connector_type.size(); n++){

            if(token[i]==r3_types::connector_type[n]){
                            
                type_position.push_back("c"); // Connector

            }

        }

        // Comparison with rank 3 subject type functions
        for(int n=0; n<r3_types::subject_type.size(); n++){

            if(token[i]==r3_types::subject_type[n]){
                            
                type_position.push_back("s"); // Subject
                
            }

        }

    }

    return type_position;

}