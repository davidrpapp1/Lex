// Libraries
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

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
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), '('), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), ')'), query_upper.end());
    query_upper.erase(remove(query_upper.begin(), query_upper.end(), ':'), query_upper.end());
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


void printvector (std::vector <std::string> v){
	for(int i=0;i<v.size();++i)
		std::cout<<v[i]<<std::endl;
}

std::vector <std::string> dedup (std::vector <std::string> textvec){ //deduplicate function for text vector
    std::vector <std::string> nodup;
    for(int l=0;l<textvec.size();++l){
        if(std::count(nodup.begin(), nodup.end(), textvec[l]) < 1){
            nodup.push_back(textvec[l]);
        }
    }
    return nodup;
}


std::vector <std::vector <std::string>> surround (std::string word, std::vector <std::string> textvec, int num){ //neighbour gathering function for defined word for defined number of neighbours
    std::vector <std::vector <std::string>> all; //vector of vectors containing {position, word, count}
    std::vector <std::string> header = {"position", "word", "count"}; //header vector to be added at end
    std::vector <std::string> currentrow; //vector for current neighbour
    std::vector <std::vector <std::string>> neighbourflist; //vector of vectors for + neighbours at each position
    std::vector <std::vector <std::string>> neighbourblist; //vector of vectors for - neighbours at each position
    std::string neighbourf; //current + neighbour
    std::string neighbourb; //current - neighbour

    for(int t=0;t<num+1;++t){ //adds filler NULLs for first and last words in text
        textvec.insert(textvec.begin(), "NULL");
        textvec.insert(textvec.end(), "NULL");
        neighbourflist.push_back({}); //adds empty vector for each possible + position
        neighbourblist.push_back({}); //adds empty vector for each possible - position
    }

    for(int i=0;i<textvec.size();++i){ //iterate for each word in text
        if(textvec[i] == word){
            for(int position=1;position<num+1;++position){ //iterates for each position (+1 and -1), (+2 and -2) ....
                neighbourf = textvec[i+position];
                neighbourb = textvec[i-position];
                if(std::count(neighbourflist[position-1].begin(), neighbourflist[position-1].end(), neighbourf)>0){ //if neighbour already exists for same position, increase count
                    for(int l=0;l<all.size();++l){
                        if(neighbourf == all[l][1]){
                            if(position == stoi(all[l][0])){
                                all[l][2] = std::to_string(stoi(all[l][2])+1);
                            }
                        }
                    }
                }
                else{ //if new neighbour and position, add to list
                    currentrow.clear();
                    currentrow.push_back(std::to_string(position));
                    currentrow.push_back(neighbourf);
                    currentrow.push_back("1");
                    all.push_back(currentrow);
                    neighbourflist[position-1].push_back(neighbourf);
                }
                if(std::count(neighbourblist[position-1].begin(), neighbourblist[position-1].end(), neighbourb)>0){ //repeat for - positions
                    for(int l=0;l<all.size();++l){
                        if(neighbourb == all[l][1]){
                            if(-position == stoi(all[l][0])){
                                all[l][2] = std::to_string(stoi(all[l][2])+1);
                            }
                        }
                    }
                }
                else{
                    currentrow.clear();
                    currentrow.push_back(std::to_string(-position));
                    currentrow.push_back(neighbourb);
                    currentrow.push_back("1");
                    all.push_back(currentrow);
                    neighbourblist[position-1].push_back(neighbourb);
                }
            }
        }
    }
    all.insert(all.begin(), header); //add header
return all;
}

void writecsv (std::vector <std::vector <std::string>> allvec, std::string word){ //save to csv file
    std::ofstream myFile(word + ".csv");
    for(int i=0;i<allvec.size();++i){
        for(int j=0;j<allvec[i].size();++j){
            myFile << allvec[i][j];
            if(j != allvec[i].size()-1){
                myFile << ",";
            }
        }
        myFile <<std::endl;
    }
    myFile.close();
}


int main(){
    //
    std::string file_contents;
    std::vector <std::string> out;
    std::vector <std::string> outnodup;

    file_contents = readFileIntoString("sense_and_sensibility.txt"); //reads file to string as file_contents
        std::transform(file_contents.begin(), file_contents.end(),file_contents.begin(), ::toupper); //makes all caps

    out = tokenise(file_contents); //tokenise file string
    remove(out.begin(), out.end(), ""); //remove ""
    outnodup = dedup(out); //vector containing every word in text once
    remove(outnodup.begin(), outnodup.end(), ""); //remove ""

    std::vector <std::vector <std::string>> nword; //iterate for word in the text
    for(int i=0;i<outnodup.size();++i){
        if(outnodup[i] != ""){ //prevents ".csv" file 
            nword = surround(outnodup[i], out, 3); //neighbour positions adjustable
            writecsv(nword, outnodup[i]);
        }
    }

    //printvector(outnodup);

    return 0;
}