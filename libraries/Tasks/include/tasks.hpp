#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

class Tasks {
    public:
        void generate_question(std::string &question, std::string &first_answer, std::string &second_answer,
                                std::string &third_answer, int &answer);
    private:
        std::vector <std::string> questions = {"Which year brigada came out", "Who is best mentor", "Who is best coder", "Capital of Australia"};
        std::vector <std::string>  first_answers = {"2002", "Zhirov", "bee_dev", "Sydney"};
        std::vector <std::string>  second_answers = {"2006", "Zhirov", "white_dev", "Kandberri"};
        std::vector <std::string>  third_answers = {"2008", "Zhirov", "cosmos_dev", "Moscow"};
        std::vector <int> answers = {1,0,3,2};
};