// Libraries
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

// Header files
#include "../hdr/err.hpp"
#include "../hdr/terminal.hpp"
#include "../hdr/raw_hash_table.hpp"
#include "../hdr/hash_table.hpp"

// Debugging and error function
int err_status(){
    
    // Return 0 and exit program if "exit" is detected
    if(query == "exit"){
        return 0;
    }

    // Check completion flag, display error if not true
    if(completion_flag == false){
        std::cout << "I could not find the input you requested." << std::endl;
        
        err_container=true;
    }

}

// Function to generate random slot for response vector
int fetch_random_response_slot(int size_of_vector){
    
    // Seed number generator according to computer clock
    // ensuring different seeding each time
    srand(time(NULL));
    return rand()%size_of_vector;

}

// Main function
int main(){

    // Terminal invocation
    do{ 
//------- Reservoir stream --------------------------------------------------------------------------------------------------------        
        std::ifstream myStream("sense_and_sensibility");

//---------------------------------------------------------------------------------------------------------------------------------
        // Error check initialisation
        // If err=true at the end of command, err_status is called and message is displayed
        completion_flag=false;
        
        // User input string
        std::cout << "Cithria: ";
        std::getline(std::cin, query);
        query_upper.assign(query);

        // Transform characters in string to upper case for ease of use
        std::transform(query_upper.begin(), query_upper.end(), query_upper.begin(), ::toupper);

        // Basic response
        if (query_upper == simple_query[0] || query_upper == simple_query[1] || query_upper == simple_query[2]
         || query_upper == simple_query[3] || query_upper == simple_query[4] || query_upper == simple_query[5]){
            std::cout << "Hello." << std::endl;
            
            completion_flag=true;
            err_container=false;
        
        // Debugging messages if prompted
        } else if (query_upper == debug_table[0] || query_upper == debug_table[1] || query_upper == debug_table[2] 
                || query_upper == debug_table[3] || query_upper == debug_table[4] || query_upper == debug_table[5]){
            std::cout << "completion_flag: " << completion_flag << std::endl << "err_container: " << err_container << std::endl;
            
            completion_flag=true;
            err_container=false;

        } else{
            // Loop over all text in reservoir
            while(getline(myStream, line)){
                
                // Capitalise string for ease of use
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);

                // Seek user input string
                if (line.find(query_upper) != std::string::npos){
                    std::cout << "\'" << query << "\'" << " was found in: " << "'sense_and_sensibility'" << std::endl;
                    
                    completion_flag=true;
                    err_container=false;

                }

            }

            // Move to interpretation if above options are not triggered
            if (completion_flag==false && query != "exit"){

                // Remove potential inconsistencies from input string
                query_upper.erase(remove(query_upper.begin(), query_upper.end(), '?'), query_upper.end());
                query_upper.erase(remove(query_upper.begin(), query_upper.end(), ','), query_upper.end());
                query_upper.erase(remove(query_upper.begin(), query_upper.end(), '.'), query_upper.end());

                // Intermediate tokenisation container
                std::stringstream tokenisation(query_upper);
                
                // Tokenise and vectorise string
                while(getline(tokenisation, intermediate, ' ')){
                    token.push_back(intermediate);
                }

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

                // Rank 3 function position analysis
                if(type_position[0]==r3_vectors::fcs[0] && type_position[1]==r3_vectors::fcs[1] && 
                   type_position[2]==r3_vectors::fcs[2]){

                    // How are you response protocol
                    if(token[0]=="HOW" && token[2]=="YOU"){
                        
                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r3_responses::fcs_how_you.size());
                        std::cout << r3_responses::fcs_how_you[random] << std::endl;
                        
                        completion_flag=true;
                        err_container=false;

                    }

                    // What are you response protocol
                    if(token[0]=="HOW" && token[2]=="YOU"){
                        
                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r3_responses::fcs_how_you.size());
                        std::cout << r3_responses::fcs_how_you[random] << std::endl;
                        
                        completion_flag=true;
                        err_container=false;

                    }

                }

            }

            // Display error message if found
            err_status();

        } 

    // Exit condition
    } while (query != "exit");

    // Exit message
    std::cout << "Exiting..." << std::endl;

} // End of program