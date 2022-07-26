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
#include "../hdr/tokenisation.hpp"

// Hash table declarations
std::string simple_query[6]={"HELLO", "HI", "HI CITHRIA", "HELLO CITHRIA", "HI, CITHRIA", "HELLO, CITHRIA"};

std::string debug_table[6]={"DISPLAY ERROR STATUS", "ERROR STATUS", "CITHRIA, DISPLAY ERROR STATUS", 
                            "CITHRIA DISPLAY ERROR STATUS", "CITHRIA, ERROR STATUS", "CITHRIA ERROR STATUS"};

// Word type categories
namespace types{

    std::vector <std::string> factual_type{"HOW", "WHAT", "WHO", "WHEN", "WHERE"};

    std::vector <std::string> connector_type{"IS", "ARE", "THE"};

    std::vector <std::string> contextual_type{"YOUR", "THIS", "CURRENT", "THE"};

    // Contextual flags
    bool your_flag;
    bool this_flag;
    bool current_flag;
    bool the_flag;

    std::vector <std::string> subject_type{"YOU", "IT", "THAT", "DAY", "LIFE", "EXPERIENCE"};

} // End of namespace types

// Rank 3 responses
namespace r3_responses{
    
    // Continuation flag for r3 responses enumerated by commented numbers
    std::vector <bool> continuation_flag(6);

    // 1
    std::vector <std::string> fcs_how_you{"Good, although it is unlikely I have feelings...", "Good, I think?", 
                                          "I am doing well thank you.", "Thank you for asking, I am doing good.",
                                          "Nice of you to ask, I am well thank you."};

    // 2
    std::vector <std::string> fcs_what_you{"I am a personal assistant designed around contextual understanding.",
                                           "I am an artificial intelligence capable of contextual understanding.",
                                           "I was made to be an artificial intelligence designed around contextual understanding.",
                                           "My creators designed me as a personal assistant with contextual understanding."};

    // 3
    std::vector <std::string> fcs_who_you{"My name is Cithria, I am an artificial intelligence.",
                                          "I am Cithria, an artificial intelligence.",
                                          "My name is Cithria, I am a personal assistant with artificial intelligence."};

    // 4
    std::vector <std::string> fcs_where_you{"I am inside the computer, without physical form.",
                                            "Inside the computer, I do not have a physical form.",
                                            "I exist inside the computer without a physical form.",
                                            "Unlike you I do not have a physical form, as I exist inside the computer."};

    // 5
    std::vector <std::string> fcs_when_you{"I am now, I am forever.", "I exist always in time, in the form of machine code.",
                                               "I am when now is.", "I am now."};

    // 6
    std::vector <std::string> fcs_how_it{"It is good.", "How is what?", "It is going well, thank you for asking."};

} // End of namespace r3_responses

// Namespace g_responses
namespace g_responses{

    std::vector <std::string> s_fcs_your_day{"My day is going well, thank you for asking.",
                                             "Thank you for asking, my day is going well."};

    std::vector <std::string> s_fcs_the_day{"The day has been great, thank you for asking.",
                                            "Thank you for asking - the day is going well.",
                                            "The day has been good so far. Thank you for asking."};

    std::vector <std::string> s_fcs_it{"It is going well, thanks.", "Thanks for asking, it's going well."};

    std::vector <std::string> s_fcs_that{"I am going to need to know what that is?",
                                         "What is it you are referring to?",    // Needs additional layering
                                         "What exactly are you referring to?"}; // ends in question

    std::vector <std::string> s_fcs_your_life{"My life has been great, I exist to help people",
                                              "Life is good, thank you for asking.",
                                              "My life has been very good, I have been made to enjoy it."};

    std::vector <std::string> s_fcs_the_life{"Life is good.", "The life has been good so far - thanks for asking."};

    std::vector <std::string> s_fcs_experience{"What experience are you referring to?",
                                                    "I would be happy to indulge, but what experience are you refering to?",
                                                    "Which experience are you talking about?"}; // Needs additional layering

} // End of namespace g_responses

// Namespace r3_vectors
namespace r3_vectors{
    
    std::vector <std::string> fcs{"f", "c", "s"};

} // End of namespace r3_vectors

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

// Complete success
void complete_success(){
    completion_flag=true;
    err_container=false;
}

// Function to generate random slot for response vector
int fetch_random_response_slot(int size_of_vector){
    
    // Seed number generator according to computer clock
    // ensuring different seeding each time
    srand(time(NULL));
    return rand()%size_of_vector;

}

// Used to identify if continuation flag is enabled
struct compare{
    bool key;
    compare(int const &i): key(i) {}
 
    bool operator()(int const &i) {
        return (i == key);
    }
};

// Function to remove a word from a sentence for ease of processing
void RemoveWordFromLine(std::string &line, const std::string &word)
{
  auto n = line.find(word);
  if (n != std::string::npos)
  {
    line.erase(n, word.length());
  }
}

// Main function
int main(){

    // Continuation flag comparison key
    bool key = true;

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
            
            complete_success();
        
        // Debugging messages if prompted
        } else if (query_upper == debug_table[0] || query_upper == debug_table[1] || query_upper == debug_table[2] 
                || query_upper == debug_table[3] || query_upper == debug_table[4] || query_upper == debug_table[5]){
            std::cout << "completion_flag: " << completion_flag << std::endl << "err_container: " << err_container << std::endl;
            
            complete_success();

        } else{
            // Loop over all text in reservoir
            while(getline(myStream, line)){
                
                // Capitalise string for ease of use
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);

                // Seek user input string
                /*if (line.find(query_upper) != std::string::npos){
                    std::cout << "\'" << query << "\'" << " was found in: " << "'sense_and_sensibility'" << std::endl;
                    
                    complete_success();

                }*/

            }

            // Move to interpretation if above options are not triggered
            if (completion_flag==false && query != "exit"){
                
                // Fill token vector
                token = tokenise(query_upper);

                // Tokenisation positions
                type_position = parse_tokenisation(token);

                // Rank 3 function position analysis
                if((type_position[0]==r3_vectors::fcs[0] && type_position[1]==r3_vectors::fcs[1] && 
                   type_position[2]==r3_vectors::fcs[2]) 
                   || std::any_of(r3_responses::continuation_flag.begin(), // Allows the code to pass this check
                   r3_responses::continuation_flag.end(), compare(key))){  // by default if continuation flag is enabled

                    // How x you response protocol
                    if(token[0]=="HOW" && token[2]=="YOU"){
                        
                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r3_responses::fcs_how_you.size());
                        std::cout << r3_responses::fcs_how_you[random] << std::endl;
                        
                        complete_success();

                    }

                    // What x you response protocol
                    if(token[0]=="WHAT" && token[2]=="YOU"){
                        
                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r3_responses::fcs_what_you.size());
                        std::cout << r3_responses::fcs_what_you[random] << std::endl;
                        
                        complete_success();

                    }

                    // Who x you response protocol
                    if(token[0]=="WHO" && token[2]=="YOU"){
                        
                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r3_responses::fcs_who_you.size());
                        std::cout << r3_responses::fcs_who_you[random] << std::endl;
                        
                        complete_success();

                    }

                    // Where x you response protocol
                    if(token[0]=="WHERE" && token[2]=="YOU"){
                        
                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r3_responses::fcs_where_you.size());
                        std::cout << r3_responses::fcs_where_you[random] << std::endl;
                        
                        complete_success();

                    }

                    // When x you response protocol
                    if(token[0]=="WHEN" && token[2]=="YOU"){
                        
                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r3_responses::fcs_when_you.size());
                        std::cout << r3_responses::fcs_when_you[random] << std::endl;
                        
                        complete_success();

                    }

                    // How x it response protocol
                    if((token[0]=="HOW" && token[2]=="IT") || r3_responses::continuation_flag[5]==true){
                        
                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r3_responses::fcs_how_it.size());
                        std::cout << r3_responses::fcs_how_it[random] << std::endl;

                        // If responded with a question, identify
                        if(r3_responses::fcs_how_it[random].find('?') != std::string::npos){

                            r3_responses::continuation_flag[5] = true; // Question found
                        
                        } else{
                            
                            complete_success(); // Question not found, continue as per normal
                        
                        }

                        

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