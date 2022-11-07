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
    //outvec("sense_and_sensibility.txt");
    //
    std::string file_contents;
    std::vector <std::string> out;
    std::vector <std::string> realout;

    file_contents = readFileIntoString("sense_and_sensibility.txt");
        std::transform(file_contents.begin(), file_contents.end(),file_contents.begin(), ::toupper);

    out = tokenise(file_contents);
    //


    int x = 15;
    int rx = 14;
    std::string samp = "qqqqqq";
    std::vector <std::string> topvec(x, samp);
    std::vector <std::string> badvec;
    badvec.push_back ("");
    int botcount = 0;


    for(int i=0;i<out.size();++i){

        if(std::count(badvec.begin(), badvec.end(), out[i]) > 0){}
        else if(std::count(topvec.begin(), topvec.end(), out[i]) > 0){
            badvec.push_back (out[i]);
        }
        else if(std::count(out.begin(), out.end(), out[i]) < botcount){
            badvec.push_back (out[i]);
        }
    
        else{
            badvec.push_back (out[i]);
            for(int t=0;t<x;t++){
                if(std::count(out.begin(), out.end(), out[i]) > std::count(out.begin(), out.end(), topvec[t])){
                    if(t == rx){
                        topvec[rx] = out[i];
                    }
                    else{
                        for(int f=0;f<rx-t;f++){
                            topvec[rx-f] = topvec[rx-f-1];
                        }
                        topvec[t] = out[i];
                    }
                    break;
                }
            }
            botcount = std::count(out.begin(), out.end(), topvec[rx]);
        }
    }
    printvector(topvec);

    //for(int g=0;g<topvec.size();g++){
    //    std::cout << topvec[g] << std::endl;
    //}
    //outvec("sense_and_sensibility.txt");
    return 0;
}