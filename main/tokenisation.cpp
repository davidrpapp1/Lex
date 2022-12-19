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

std::vector <std::string> tokenise(std::string query_upper, bool and_trigger){

    std::vector <std::string> return_token;

    // Remove potential inconsistencies from input string
                           query_upper.erase(remove(query_upper.begin(), query_upper.end(), '?'), query_upper.end());
                           query_upper.erase(remove(query_upper.begin(), query_upper.end(), '.'), query_upper.end());
    if(and_trigger==false) query_upper.erase(remove(query_upper.begin(), query_upper.end(), ','), query_upper.end());

    // Intermediate tokenisation container
    std::stringstream tokenisation(query_upper);
    std::string intermediate;

    // Tokenise and vectorise string
    const std::string space_container = " ";
    while(getline(tokenisation, intermediate, ' ')){
        if(intermediate.empty()){
            // Skip because spacebar
        } else{
            return_token.push_back(intermediate);
        }
    }

    return return_token;

}

std::vector <std::string> parse_tokenisation(std::vector <std::string> token){

    // Reset type postition vector and completion flag
    type_position.clear();
    bool type_pos_complete_flag = false;

    // Look for string vector match
    for(int i=0; i<token.size(); i++){
                    
        // Comparison with rank 3 factual type functions
        for(int n=0; n<types::factual_type.size(); n++){

            if(token[i]==types::factual_type[n]){
                            
                type_position.push_back("f"); // Factual
                type_pos_complete_flag = true; // Type position complete flag

            }

        }

        // Comparison with rank 3 connector type functions
        for(int n=0; n<types::connector_type.size(); n++){

            if(token[i]==types::connector_type[n]){
                            
                type_position.push_back("c"); // Connector
                type_pos_complete_flag = true;

            }

        }

        // Comparison with rank 3 subject type functions
        for(int n=0; n<types::subject_type.size(); n++){

            if(token[i]==types::subject_type[n]){
                            
                type_position.push_back("s"); // Subject
                type_pos_complete_flag = true;

            }

        }

        // Comparison with contextual type functions
        for(int n=0; n<types::contextual_type.size(); n++){

            if(token[i]==types::contextual_type[n]){
                            
                if(n==0) types::your_flag = true; // Your

                if(n==1) types::this_flag = true; // This

                if(n==2) types::the_flag = true; // The
                
                if(n==3) types::it_flag = true; // It

                if(n==4) types::current_flag = true; // Current

                if(n==5) types::currently_flag = true; // Currently

                if(n==6) types::today_flag = true; // Today

                if(n==7) types::todays_flag = true; // Today's

                if(n==8) types::now_flag = true; // Now
                
            }

        }

    }

    // If type position not detected, return error message via a key
    if (type_pos_complete_flag==true){
        return type_position;
    } else{

        // UPDATE THIS ERROR FORMATTING
        std::vector <std::string> error_string{"query_error"};
        return error_string;
    }
}