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

std::string readFileIntoString(const std::string& path){
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
    std::replace(query_upper.begin(), query_upper.end(), '\n', ' ');

    


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
}


int main(){
    //
    std::string file_contents;
    std::vector <std::string> out;

    file_contents = readFileIntoString("sense_and_sensibility.txt"); //reads file to string as file_contents
        std::transform(file_contents.begin(), file_contents.end(),file_contents.begin(), ::toupper); //makes all caps

    out = tokenise(file_contents); //tokenise file string
    //

    //topvec function:
    int x = 15; //top x most used words
    int rx = 14; //real x as 0 is included in functions
    std::string samp = "qqqqqq"; //placeholder string which would not be used at all in text file
    std::vector <std::string> topvec(x, samp); //fill topvec vector with placeholder
    std::vector <std::string> badvec;  //list of words to words to ignore as disqualified
    badvec.push_back ("");
    int botcount = 0; //number of appearances of last word in topvec


    for(int i=0;i<out.size();++i){ //iterate through each word in file

        if(std::count(badvec.begin(), badvec.end(), out[i]) > 0){} //check if already disqualified
        else if(std::count(topvec.begin(), topvec.end(), out[i]) > 0){ //check if already in topvec
            badvec.push_back (out[i]); //disqualify
        }
        else if(std::count(out.begin(), out.end(), out[i]) < botcount){ //check if qualifies at all
            badvec.push_back (out[i]); //disqualify
        }
    
        else{ //if qualifies
            badvec.push_back (out[i]);
            for(int t=0;t<x;t++){ //iterate through topvec from right to left
                if(std::count(out.begin(), out.end(), out[i]) > std::count(out.begin(), out.end(), topvec[t])){ //check against
                    if(t == rx){ //if at last topvec value, replace topvec with candidate
                        topvec[rx] = out[i];
                    }
                    else{
                        for(int f=0;f<rx-t;f++){ //if not at last topvec value, each topvec value until current is replaced by the one before
                            topvec[rx-f] = topvec[rx-f-1];
                        }
                        topvec[t] = out[i]; //appropriate value in topvec replaced by candidate
                    }
                    break; //breaks loop once topvec updated
                }
            }
            botcount = std::count(out.begin(), out.end(), topvec[rx]); //new botcount value assigned
        }
    }
    printvector(topvec);

    return 0;
}