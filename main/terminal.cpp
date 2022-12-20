// Libraries
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>

// Header files
#include "../hdr/err.hpp"
#include "../hdr/terminal.hpp"
#include "../hdr/raw_hash_table.hpp"
#include "../hdr/hash_table.hpp"
#include "../hdr/tokenisation.hpp"
#include "../hdr/comparator.hpp"
#include "../hdr/if_multiple_processor.hpp"

// Hash table declarations
std::vector <std::string> simple_query{"HELLO", "HI", "HI CITHRIA", "HELLO CITHRIA", "HI, CITHRIA", "HELLO, CITHRIA"};

std::vector <std::string> debug_table{"DISPLAY ERROR STATUS", "ERROR STATUS", "CITHRIA, DISPLAY ERROR STATUS", 
                            "CITHRIA DISPLAY ERROR STATUS", "CITHRIA, ERROR STATUS", "CITHRIA ERROR STATUS"};

// Word type categories
namespace types{

    std::vector <std::string> factual_type{"HOW", "WHAT", "WHO", "WHEN", "WHERE"};

    std::vector <std::string> connector_type{"IS", "ARE", "THE"};

    std::vector <std::string> contextual_type{"YOUR", "THIS", "THE", "IT", "CURRENT", "CURRENTLY", "TODAY", 
                                              "TODAY'S", "NOW", "TOMORROW", "MONDAY", "TUESDAY", "WEDNESDAY", 
                                              "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};

    // Contextual flags
    bool your_flag;
    bool this_flag;
    bool the_flag;
    bool it_flag;
    bool current_flag;
    bool currently_flag;
    bool today_flag;
    bool todays_flag;
    bool now_flag;
    bool tomorrow_flag;
    bool monday_flag;
    bool tuesday_flag;
    bool wednesday_flag;
    bool thursday_flag;
    bool friday_flag;
    bool saturday_flag;
    bool sunday_flag;

    std::vector <std::string> subject_type{"YOU", "IT", "THAT", "DAY", "LIFE", "EXPERIENCE", "TIME", "DATE", "TODAY", "TODAY'S",
                                           "CURRENT", "CURRENTLY", "NOW", "TOMORROW", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY",
                                           "FRIDAY", "SATURDAY", "SUNDAY"};

    std::vector <std::string> and_type{"AND"};

} // End of namespace types

// Rank 3 responses
namespace r3_responses{

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
    int fcs_how_it_cont_flag=0;

} // End of namespace r3_responses

// Rank 4 responses
namespace r4_responses{

    // fccs

    // 1
    std::vector <std::string> fccs_what_time{"The current time is ", "Time right now: ", "It is currently ", "Right now it is ",
                                             "Currently it is ", "Current time: "};

    // 2
    std::vector <std::string> fccs_what_date{"The current date is ", "Today's date: ", "Today's date is: "};

    // end of fccs


    // fscs

    // 1
    std::vector <std::string> fscs_what_time{"The current time is ", "Time right now: ", "It is currently ", "Right now it is ",
                                             "Currently it is ", "Current time: "};

    // 2
    std::vector <std::string> fscs_what_date{"The current date is ", "Today's date: ", "Today's date is: "};

    // end of fscs

} // End of namespace r4_responses

// Namespace g_responses
namespace g_responses{

    std::vector <std::string> s_fcs_your_day{"My day is going well, thank you for asking.",
                                             "Thank you for asking, my day is going well."};

    std::vector <std::string> s_fcs_the_day{"The day has been great, thank you for asking.",
                                            "Thank you for asking - the day is going well.",
                                            "The day has been good so far. Thank you for asking."};

    std::vector <std::string> s_fcs_it{"It is going well, thanks.", "Thanks for asking, it's going well."};

    std::vector <std::string> s_fcs_that{"I am going to need to know what that is?",
                                         "What is it you are referring to?",    
                                         "What exactly are you referring to?"}; 
    int s_fcs_that_cont_flag=0;

    std::vector <std::string> s_fcs_your_life{"My life has been great, I exist to help people",
                                              "Life is good, thank you for asking.",
                                              "My life has been very good, I have been made to enjoy it."};

    std::vector <std::string> s_fcs_the_life{"Life is good.", "The life has been good so far - thanks for asking."};

    std::vector <std::string> s_fcs_experience{"What experience are you referring to?",
                                               "I would be happy to indulge, but what experience are you refering to?",
                                               "Which experience are you talking about?"}; 
    int s_fcs_experience_cont_flag=0;

} // End of namespace g_responses

// Namespace r4_vectors
namespace r4_vectors{

    std::vector <std::string> fccs{"f", "c", "c", "s"};

    std::vector <std::string> fscs{"f", "s", "c", "s"};

} // End of namespace r4_vectors

// Namespace r3_vectors
namespace r3_vectors{
    
    std::vector <std::string> fcs{"f", "c", "s"};

} // End of namespace r3_vectors

// Namespace r1_vectors
namespace r1_vectors{

    std::vector <std::string> s{"s"};

} // End of namespace r1_vectors

// Local variables
std::vector <std::string> token_container;
std::vector <std::string> truncated_vector_container;
std::vector <std::string> intermediate_container;
std::vector <std::string> token_first_half;
std::vector <std::string> token_second_half;
std::vector <std::string> token_final;
std::vector <std::string> and_subject_storage;
std::vector <int> subject_swap_indices;
int comma_index = 0;

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

// Main function
int main(){

    // Continuation variables;
    bool key = true;
    bool c_tf;
    bool message_disp_flag;
    bool and_trigger = false;
    int layer = 0;
    int tokensize = 0;
    int intermediate_container_size = 0;
    int token_first_half_size = 0;
    int token_second_half_size = 0;
    int new_index = 0;

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
        if (if_or_processor_hashtable(query_upper, simple_query)==true){
            std::cout << "Hello." << std::endl;
            
            complete_success();
        
        // Debugging messages if prompted
        } else if (if_or_processor_hashtable(query_upper, debug_table)==true){
            std::cout << "completion_flag: " << completion_flag << std::endl << "err_container: " << err_container << std::endl;
            
            complete_success();

        } else{
            // Loop over all text in reservoir
            while(getline(myStream, line)){
                
                // Capitalise string for ease of use
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);
                
                /*
                // Seek user input string
                if (line.find(query_upper) != std::string::npos){
                    std::cout << "\'" << query << "\'" << " was found in: " << "'sense_and_sensibility'" << std::endl;
                    
                    complete_success();

                }
                */

            }

            // Move to interpretation if above options are not triggered
            if (completion_flag==false && query != "exit"){

                // Fill token vector
                token.clear();
                and_trigger = false;
                token = tokenise(query_upper, and_trigger);

                // Check for any "and"s
                const std::string and_container = "AND";
                if(if_or_processor_hashtable(and_container, token)==true){

                    // If "and"(s) are found, rerun tokenisation without removing commas
                    and_trigger = true;
                    token = tokenise(query_upper, and_trigger);
                    tokensize = token.size();

                    // Truncate tokens that might accidentaly have stuck together
                    for(int i=0; i<tokensize; i++){
                        
                        const std::string comma_container = ",";

                        // Decompose strings contained within each vector slot
                        token_container.clear();
                        token_container = tokenise(token[i], and_trigger);
                        for(int n=0; n<token_container.size(); n++){

                            // Look for commas and seperate into more vector elements
                            intermediate_container_size = 0;
                            token_first_half_size = 0;
                            token_second_half_size = 0;
                            intermediate_container.clear();
                            token_first_half.clear();
                            token_second_half.clear();
                            if(token_container[n].find(comma_container)!=std::string::npos){

                                comma_index = i;
                                std::stringstream truncation_string(token_container[n]);
                                while(truncation_string.good()){
                                    std::string substring;
                                    getline(truncation_string, substring, ',');
                                    if(intermediate_container_size!=0){
                                        intermediate_container.push_back("AND");
                                        intermediate_container_size++;
                                    }
                                    intermediate_container.push_back(substring);
                                    intermediate_container_size++;
                                }

                                for(int location=0; location<comma_index; location++){
                                    token_first_half.push_back(token[location]);
                                    token_first_half_size++;
                                }

                                for(int location=comma_index+1; location<tokensize; location++){
                                    token_second_half.push_back(token[location]);
                                    token_second_half_size++;
                                }

                                // Construct final version of "token" with unrolled terms
                                token.clear();
                                for(int location=0; location<token_first_half_size; location++){
                                    token.push_back(token_first_half[location]);
                                }
                                for(int location=0; location<intermediate_container_size; location++){
                                    token.push_back(intermediate_container[location]);
                                }
                                for(int location=0; location<token_second_half_size; location++){
                                    token.push_back(token_second_half[location]);
                                }

                                // Delete any redundant " "s and 
                                // check for any duplicate "and"s, given artificial ones are introduced
                                std::string token_location_container;
                                for(int location=0; location<token.size(); location++){
                                    if(token[location].empty()){
                                        token.erase(token.begin()+location);
                                    }
                                }
                                for(int location=0; location<token.size(); location++){
                                    if(token_location_container==token[location]) token.erase(token.begin()+location);
                                    token_location_container = token[location];
                                }

                            } 

                        }

                    }

                }
                
                // Tokenisation positions
                type_position = parse_tokenisation(token);

                // Deal with multiple subjects/contexts seperated by "AND"s
                // and register any indices used as a proxy for subject swapping when parsing
                // all "AND" related queries
                and_subject_storage.clear();
                subject_swap_indices.clear();
                bool local_and_edit_flag = false;
                bool subject_swap_index_edit_flag = false;
                for(int location=0; location<type_position.size(); location++){
                    if(type_position[location]!="&"){
                        if(type_position[location]=="s"){
                            if(location+1!=type_position.size()){
                                if(type_position[location+1]=="&"){
                                    and_subject_storage.push_back(token[location]);
                                    local_and_edit_flag = true;
                                    if(subject_swap_index_edit_flag!=true) subject_swap_indices.push_back(location);
                                    subject_swap_index_edit_flag = true;
                                } else{
                                    local_and_edit_flag = false;
                                }
                            } else if(local_and_edit_flag==true){
                                and_subject_storage.push_back(token[location]);
                                local_and_edit_flag = false;
                                subject_swap_index_edit_flag = false;
                            }
                        }
                    }
                }
                
                for(int swap_index=0; swap_index<subject_swap_indices.size(); swap_index++){
                    for(int subject_index=0; subject_index<and_subject_storage.size(); subject_index++){
                        token[swap_index] = and_subject_storage[subject_index];
                    }
                }

                // Rank 4 function position analysis
                if(if_aa_processor_vect(type_position, r4_vectors::fccs)==true){

                    // What x x time response protocol
                    if(token[0]=="WHAT" && token[3]=="TIME" &&
                      (types::current_flag==true || types::todays_flag==true || types::today_flag==true || types::now_flag==true ||
                       types::currently_flag==true || types::the_flag==true)){

                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r4_responses::fccs_what_time.size());

                        // Store and display time according to system clock
                        // Credits: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
                        time_t now = time(0);
                        tm *local_time = localtime(&now);

                        std::cout << r4_responses::fccs_what_time[random] << local_time->tm_hour << ":";
                        std::cout << local_time->tm_min << ":";
                        std::cout << local_time->tm_sec << std::endl;

                        complete_success();

                    }

                    // What x x date response protocol
                    if(token[0]=="WHAT" && token[3]=="DATE" &&
                      (types::current_flag==true || types::todays_flag==true || types::today_flag==true || types::now_flag==true ||
                       types::currently_flag==true || types::the_flag==true)){

                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r4_responses::fccs_what_date.size());

                        // Store and display date according to system clock
                        // Credits: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
                        time_t now = time(0);
                        tm *local_time = localtime(&now);
                        
                        std::cout << r4_responses::fccs_what_date[random] << local_time->tm_mday << "/";
                        std::cout << 1 + local_time->tm_mon << "/";
                        std::cout << 1900 + local_time->tm_year << std::endl;

                        complete_success();

                    }

                }
                
                // Rank 4 function position analysis
                if(if_aa_processor_vect(type_position, r4_vectors::fscs)==true){

                    // What time x x response protocol
                    if(token[0]=="WHAT" && token[1]=="TIME" &&
                      (types::current_flag==true || types::todays_flag==true || types::today_flag==true || types::now_flag==true ||
                       types::currently_flag==true || types::it_flag==true)){

                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r4_responses::fscs_what_time.size());

                        // Store and display date according to system clock
                        // Credits: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
                        time_t now = time(0);
                        tm *local_time = localtime(&now);
                        
                        std::cout << r4_responses::fscs_what_time[random] << local_time->tm_hour << ":";
                        std::cout << local_time->tm_min << ":";
                        std::cout << local_time->tm_sec << std::endl;

                        complete_success();

                    }

                    // What date x x response protocol
                    if(token[0]=="WHAT" && token[1]=="DATE" &&
                      (types::current_flag==true || types::todays_flag==true || types::today_flag==true || types::now_flag==true ||
                       types::currently_flag==true || types::it_flag==true)){

                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r4_responses::fscs_what_date.size());

                        // Store and display date according to system clock
                        // Credits: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
                        time_t now = time(0);
                        tm *local_time = localtime(&now);
                        
                        std::cout << r4_responses::fscs_what_date[random] << local_time->tm_mday << "/";
                        std::cout << 1 + local_time->tm_mon << "/";
                        std::cout << 1900 + local_time->tm_year << std::endl;

                        complete_success();

                    }

                }

                // Rank 3 function position analysis
                if((if_aa_processor_vect(type_position, r3_vectors::fcs)==true)
                   || r3_responses::fcs_how_it_cont_flag>0){  // by default if continuation flag is enabled

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

                    //START--------------------------------------------------------------------------------------------------------------------------------------------------------
                    // How x it response protocol
                    if(token[0]=="HOW" && token[2]=="IT"){

                        // Fetch random response from raw hash table
                        int random = fetch_random_response_slot(r3_responses::fcs_how_it.size());
                        std::cout << r3_responses::fcs_how_it[random] << std::endl;

                        // If responded with a question, identify
                        if(r3_responses::fcs_how_it[random].find('?') != std::string::npos){

                            r3_responses::fcs_how_it_cont_flag++;
                            message_disp_flag = false;
                            layer++;

                        }

                        complete_success();

                    }

                    // Conditions to seek question response from user
                    if (r3_responses::fcs_how_it_cont_flag>0 && message_disp_flag==true){

                        // Your x day response protocol
                        c_tf = fcs_comparator(token, "YOUR", "DAY");
                        if(c_tf==true && layer==1){
                                
                            // Fetch random response from raw hash table
                            int random = fetch_random_response_slot(g_responses::s_fcs_your_day.size());
                            std::cout << g_responses::s_fcs_your_day[random] << std::endl;
                                
                            complete_success();
                            r3_responses::fcs_how_it_cont_flag = 0;
                            layer=0;

                        }

                        // The x day response protocol
                        c_tf = fcs_comparator(token, "THE", "DAY");
                        if(c_tf==true && layer==1){
                            
                            // Fetch random response from raw hash table
                            int random = fetch_random_response_slot(g_responses::s_fcs_the_day.size());
                            std::cout << g_responses::s_fcs_the_day[random] << std::endl;
                                
                            complete_success();
                            r3_responses::fcs_how_it_cont_flag = 0;
                            layer=0;

                        }

                        // Your x life response protocol
                        c_tf = fcs_comparator(token, "YOUR", "LIFE");
                        if(c_tf==true && layer==1){
                            
                            // Fetch random response from raw hash table
                            int random = fetch_random_response_slot(g_responses::s_fcs_your_life.size());
                            std::cout << g_responses::s_fcs_your_life[random] << std::endl;
                                
                            complete_success();
                            r3_responses::fcs_how_it_cont_flag = 0;
                            layer=0;

                        }

                        // The x life response protocol
                        c_tf = fcs_comparator(token, "THE", "LIFE");
                        if(c_tf==true && layer==1){
                            
                            // Fetch random response from raw hash table
                            int random = fetch_random_response_slot(g_responses::s_fcs_the_life.size());
                            std::cout << g_responses::s_fcs_the_life[random] << std::endl;
                                
                            complete_success();
                            r3_responses::fcs_how_it_cont_flag = 0;
                            layer=0;

                        }
                    
                        //-------------------------------------------------------------------------------------------------------------------------------------------------------------
                        //START--------------------------------------------------------------------------------------------------------------------------------------------------------
                        // Your x experience response protocol
                        c_tf = fcs_comparator(token, "YOUR", "EXPERIENCE"); 
                        if(c_tf==true && layer==1){                                     
                            
                            // Fetch random response from raw hash table
                            int random = fetch_random_response_slot(g_responses::s_fcs_experience.size());
                            std::cout << g_responses::s_fcs_experience[random] << std::endl;

                            // If responded with a question, identify
                            if(g_responses::s_fcs_experience[random].find('?') != std::string::npos){

                                g_responses::s_fcs_experience_cont_flag++;
                                message_disp_flag = false;
                                layer++;

                            } else{
                                layer=0;
                            }
                            
                            complete_success();

                        }

                        // The x experience response protocol
                        c_tf = fcs_comparator(token, "THE", "EXPERIENCE"); 
                        if(c_tf==true && layer==1){                                    
                            
                            // Fetch random response from raw hash table
                            int random = fetch_random_response_slot(g_responses::s_fcs_experience.size());
                            std::cout << g_responses::s_fcs_experience[random] << std::endl;
                            
                            // If responded with a question, identify
                            if(g_responses::s_fcs_experience[random].find('?') != std::string::npos){

                                g_responses::s_fcs_experience_cont_flag++;
                                message_disp_flag = false;
                                layer++;

                            } else{
                                layer=0;
                            }
                                
                            complete_success();

                        }

                        // Conditions to seek question response from user
                        if (g_responses::s_fcs_experience_cont_flag>0 && message_disp_flag==true){
                            
                            // Your x life response protocol
                            c_tf = fcs_comparator(token, "YOUR", "LIFE");
                            if(c_tf==true && layer==2){
                                
                                // Fetch random response from raw hash table
                                int random = fetch_random_response_slot(g_responses::s_fcs_your_life.size());
                                std::cout << g_responses::s_fcs_your_life[random] << std::endl;
                                    
                                complete_success();
                                r3_responses::fcs_how_it_cont_flag = 0;
                                layer=0;

                            }

                            // The x life response protocol
                            c_tf = fcs_comparator(token, "THE", "LIFE");
                            if(c_tf==true && layer==2){
                                
                                // Fetch random response from raw hash table
                                int random = fetch_random_response_slot(g_responses::s_fcs_the_life.size());
                                std::cout << g_responses::s_fcs_the_life[random] << std::endl;
                                    
                                complete_success();
                                r3_responses::fcs_how_it_cont_flag = 0;
                                layer=0;

                            }

                        }
                        //END----------------------------------------------------------------------------------------------------------------------------------------------------------
                        //-------------------------------------------------------------------------------------------------------------------------------------------------------------

                        // It response protocol
                        c_tf = s_comparator(token, "IT");
                        if(c_tf==true){
                            
                            // Fetch random response from raw hash table
                            int random = fetch_random_response_slot(g_responses::s_fcs_it.size());
                            std::cout << g_responses::s_fcs_it[random] << std::endl;
                                
                            complete_success();
                            r3_responses::fcs_how_it_cont_flag = 0;
                            layer=0;

                        }

                        //-------------------------------------------------------------------------------------------------------------------------------------------------------------
                        //START--------------------------------------------------------------------------------------------------------------------------------------------------------
                        // That response protocol
                        c_tf = s_comparator(token, "THAT"); 
                        if(c_tf==true && layer==1){                     
                            
                            // Fetch random response from raw hash table
                            int random = fetch_random_response_slot(g_responses::s_fcs_that.size());
                            std::cout << g_responses::s_fcs_that[random] << std::endl;
                            
                            // If responded with a question, identify
                            if(g_responses::s_fcs_that[random].find('?') != std::string::npos){

                                r3_responses::fcs_how_it_cont_flag++;
                                message_disp_flag = false;
                                layer++;

                            } else{
                                layer=0;
                            }

                            complete_success();

                        }

                        // Conditions to seek question response from user
                        if (g_responses::s_fcs_that_cont_flag>0 && message_disp_flag==true){
                            
                            // Your x day response protocol
                            c_tf = fcs_comparator(token, "YOUR", "DAY");
                            if(c_tf==true && layer==2){
                                    
                                // Fetch random response from raw hash table
                                int random = fetch_random_response_slot(g_responses::s_fcs_your_day.size());
                                std::cout << g_responses::s_fcs_your_day[random] << std::endl;
                                    
                                complete_success();
                                r3_responses::fcs_how_it_cont_flag = 0;
                                layer=0;

                            }

                            // The x day response protocol
                            c_tf = fcs_comparator(token, "THE", "DAY");
                            if(c_tf==true && layer==2){
                                
                                // Fetch random response from raw hash table
                                int random = fetch_random_response_slot(g_responses::s_fcs_the_day.size());
                                std::cout << g_responses::s_fcs_the_day[random] << std::endl;
                                    
                                complete_success();
                                r3_responses::fcs_how_it_cont_flag = 0;
                                layer=0;

                            }

                            // Your x life response protocol
                            c_tf = fcs_comparator(token, "YOUR", "LIFE");
                            if(c_tf==true && layer==2){
                                
                                // Fetch random response from raw hash table
                                int random = fetch_random_response_slot(g_responses::s_fcs_your_life.size());
                                std::cout << g_responses::s_fcs_your_life[random] << std::endl;
                                    
                                complete_success();
                                r3_responses::fcs_how_it_cont_flag = 0;
                                layer=0;

                            }

                            // The x life response protocol
                            c_tf = fcs_comparator(token, "THE", "LIFE");
                            if(c_tf==true && layer==2){
                                
                                // Fetch random response from raw hash table
                                int random = fetch_random_response_slot(g_responses::s_fcs_the_life.size());
                                std::cout << g_responses::s_fcs_the_life[random] << std::endl;
                                    
                                complete_success();
                                r3_responses::fcs_how_it_cont_flag = 0;
                                layer=0;

                            }

                        }
                        //END----------------------------------------------------------------------------------------------------------------------------------------------------------
                        //-------------------------------------------------------------------------------------------------------------------------------------------------------------

                    }
                    //END----------------------------------------------------------------------------------------------------------------------------------------------------------

                    // Message displayed before responses boolean
                    message_disp_flag = true;

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