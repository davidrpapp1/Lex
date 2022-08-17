#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Header files
#include "../hdr/if_multiple_processor.hpp"

// For if conditions with 'or' as a seperator
bool if_or_processor_hashtable(std::string variable, std::vector <std::string> comparison){

    bool check=false;
    for (int i=0; i<comparison.size(); i++){
        if(variable==comparison[i]){
            check=true;
        }
    }
    return check;

}

// For if conditions with 'and' as a seperator. This uses a vector as a variable.
bool if_aa_processor_vect(std::vector <std::string> vect_variable, std::vector <std::string> comparison){

    bool check=false;
    int checksum=0;
    for (int i=0; i<comparison.size(); i++){
        if(vect_variable[i]==comparison[i]){
            checksum++;
        }
    }
    if(checksum==comparison.size()){
        check=true;
    }
    return check;

}