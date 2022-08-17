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


std::string file_to_string(const std::string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}



std::vector <std::string> tokenise(std::string query_upper){
    std::vector <std::string> token;

    // Remove potential inconsistencies from input string
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '?'), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), ','), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '.'), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), ';'), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '!'), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '"'), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '-'), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '\''), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '\n'), query_upper.end());

    // Intermediate tokenisation container
    std::stringstream tokenisation(query_upper);
    std::string intermediate;
                
    // Tokenise and vectorise string
    while(getline(tokenisation, intermediate, ' ')){
        token.push_back(intermediate);
    }

    return token;

}



void print_vector(std::vector <std::string> v){
	for(int i=0;i<v.size();++i)
		std::cout<<v[i]<<std::endl;
	std::cout<<"\n";
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
                type_pos_complete_flag = true; // Type position error flag

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
        // ---------------------------------------------------------------------
        // DO THESE FUNCTIONS NEED TO BE PINNED TO type_pos_completion_flag?
        // MAYBE SEPERATE FLAG IF ONLY A CONTEXTUAL EXPRESSION IS PRESENTED?
        // ---------------------------------------------------------------------
        for(int n=0; n<types::contextual_type.size(); n++){

            if(token[i]==types::contextual_type[n]){
                            
                if(n=0){

                    types::your_flag = true; // Your

                };

                if(n=1){

                    types::this_flag = true; // This

                };

                if(n=2){

                    types::current_flag = true; // Current

                };

                if(n=3){

                    types::the_flag = true; // The

                };
                
            }

        }

    }

    // If type position not detected, return error message via a key
    if (type_pos_complete_flag==true){
        return type_position;
    } else{
        std::vector <std::string> error_string{"query_error"};
        return error_string;
    }
}


void outvec(std::string filename)
{
    //std::string filename("sense_and_sensibility.txt");
    std::string file_contents;
    std::vector <std::string> out;

    file_contents = file_to_string(filename);
        std::transform(file_contents.begin(), file_contents.end(),file_contents.begin(), ::toupper);

    out = tokenise(file_contents);
    std::cout << "ff" << std::endl;
    print_vector(out);

    exit(EXIT_SUCCESS);
}