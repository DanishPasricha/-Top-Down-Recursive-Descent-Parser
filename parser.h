#include <iostream>
#include <vector>

#include "lexer.h"

using namespace std;
struct SE
{
    string name_of_the_variable;
    string scope_of_the_variable;
    int value_assigned_to_scope;
};



LexicalAnalyzer my_lexer;
vector<struct SE> ST;
vector<string> Final_result_danish;
string determine_scope(string name_of_var, string determine_scope);
void start_parsing_the_program();
vector<string> assign_variables_into_list();
void scope_of_the_variable();
void global_variable_parsing();
void public_private_variable_parsing(string running_S);
void assignment_parsing(string curr_scope);
void end_game(string jass);