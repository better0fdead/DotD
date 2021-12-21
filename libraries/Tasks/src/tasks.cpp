#include "tasks.hpp"
void Tasks::generate_question(std::string &question, std::string &first_answer, std::string &second_answer, std::string &third_answer, int &answer) {
    srand( time(0) );
    int q_num = rand() % 3 + 1;
    question = questions[q_num];
    first_answer = first_answers[q_num];
    second_answer = second_answers[q_num];
    third_answer = third_answers[q_num];
    answer = answers[q_num];
}