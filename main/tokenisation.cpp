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


std::string readFileIntoString(const std::string& path) {
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



void printvector(std::vector <std::string> v){
	for(int i=0;i<v.size();++i)
		std::cout<<v[i]<<std::endl;
	std::cout<<"\n";
}



std::vector <std::string> r3_parse_tokenisation(std::vector <std::string> token){
    std::vector <std::string> r3_types;
    std::vector <std::string> type_position;

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


int main()
{
    std::string filename("sense_and_sensibility.txt");
    std::string file_contents;
    std::vector <std::string> out;

    file_contents = readFileIntoString(filename);
        std::transform(file_contents.begin(), file_contents.end(),file_contents.begin(), ::toupper);

    out = tokenise(file_contents);
    std::cout << "ff" << std::endl;
    printvector(out);

    exit(EXIT_SUCCESS);
}