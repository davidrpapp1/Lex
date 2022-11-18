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

std::vector <std::vector <std::string>> surround (std::vector <std::string> top, std::vector <std::string> textvec, int num){
    int count;
    int countnew;
    std::string topw;
    std::vector <std::vector <std::string>> topneighbourstot;
    std::vector <std::vector <std::string>> neighbourstotal;
    std::vector <std::string> topneighbours;
    for(int t=0;t<top.size();++t){

        topneighbours.clear();
        neighbourstotal.clear();
        for(int m=0;m<num*2;++m){
            neighbourstotal.push_back({});
        }

        for(int i=0;i<textvec.size();++i){
            if(top[t] == textvec[i]){
                for(int n=0;n<num;++n){
                    neighbourstotal[n].push_back(textvec[i-num+n]);
                }
                for(int n=1;n<num+1;++n){
                    neighbourstotal[num+n].push_back(textvec[i+n]);
                }
            }
        }
        for(int n=0;n<num;n++){
            count = 0;
            topw = neighbourstotal[n][0];
            for(int c=0;c<neighbourstotal[n].size();++c){
                countnew = std::count(neighbourstotal[n].begin(), neighbourstotal[n].end(), neighbourstotal[n][c]);
                if(countnew > count){
                    count = countnew;
                    topw = neighbourstotal[n][c];
                }
            }
            topneighbours.push_back(topw);
        }

        topneighbours.push_back(top[t]);

        for(int n=1;n<num+1;++n){
            count = 0;
            topw = neighbourstotal[num+n][0];
            for(int c=0;c<neighbourstotal[num+n].size();++c){
                countnew = std::count(neighbourstotal[num+n].begin(), neighbourstotal[num+n].end(), neighbourstotal[num+n][c]);
                if(countnew > count){
                    count = countnew;
                    topw = neighbourstotal[num+n][c];
                }
            }
            topneighbours.push_back(topw);
        }
        topneighbourstot.push_back(topneighbours);
    }
    return topneighbourstot;
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



    int count;
    int countnew;
    std::string topw;
    std::vector <std::vector <std::string>> topneighbourstot; // vector of vectors containing top neighbours for every top word (returned vector)
    std::vector <std::vector <std::string>> neighbourstotal; // vector of vectors containing every instance of neighbours
    std::vector <std::string> topneighbours; //vector with top neighbour words
    
    //
    std::vector <std::string> top = topvec;
    std::vector <std::string> textvec = out;
    int num = 3; // number of neighbours on either side (adjust manually)
    //

    for(int t=0;t<top.size();t++){ //iterate across each top word

        topneighbours.clear(); //reset vectors
        neighbourstotal.clear();
        for(int m=0;m<num*2;m++){
            neighbourstotal.push_back({});
        }
 // if comment starts from here, topvec still has values
        for(int i=0;i<textvec.size();i++){ //iterate across each word in text
            if(top[t] == textvec[i]){ //check if word is a top word
                for(int n=0;n<num;n++){
                    neighbourstotal[n].push_back(textvec[i-num+n]); //add before neighbour words 
                }
                for(int n=1;n<num+1;n++){
                    neighbourstotal[num+n].push_back(textvec[i+n]); //add after neighbour words
                }
            }
            else{}
        }/*  //if comment starts from here, topvec has no values

        for(int n=0;n<num;n++){
            count = 0;
            topw = neighbourstotal[n][0];
            for(int c=0;c<neighbourstotal[n].size();++c){
                countnew = std::count(neighbourstotal[n].begin(), neighbourstotal[n].end(), neighbourstotal[n][c]);
                if(countnew > count){
                    count = countnew;
                    topw = neighbourstotal[n][c];
                }
                else{}
            }
            topneighbours.push_back(topw);
        }

        topneighbours.push_back(top[t]);

        for(int n=1;n<num+1;++n){
            count = 0;
            topw = neighbourstotal[num+n][0];
            for(int c=0;c<neighbourstotal[num+n].size();++c){
                countnew = std::count(neighbourstotal[num+n].begin(), neighbourstotal[num+n].end(), neighbourstotal[num+n][c]);
                if(countnew > count){
                    count = countnew;
                    topw = neighbourstotal[num+n][c];
                }
                else{}
            }
            topneighbours.push_back(topw);
        }
        topneighbourstot.push_back(topneighbours);
    }



    for(int n=0;n<topneighbourstot.size();++n){
        printvector(topneighbourstot[n]);
        std::cout << n << std::endl;
        */
    }




    printvector(topvec);

    return 0;
}