#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

using namespace std;

void start_parsing_the_program(){
    Token current_token=my_lexer.GetToken();
	Token next_token = my_lexer.GetToken();
    if(current_token.token_type != ID)
    {
        cout << "Syntax Error"<<endl;
		exit(1);
    }
    else
    {	
		if (next_token.token_type==LBRACE || next_token.token_type==SEMICOLON || next_token.token_type==COMMA)
		{	
			if(next_token.token_type == LBRACE){
				my_lexer.UngetToken(next_token);
				my_lexer.UngetToken(current_token);           
			}		
			else if(next_token.token_type == SEMICOLON )
			{
				ST.push_back({current_token.lexeme,"::",0});        
			}
			else if(next_token.token_type==COMMA){
				my_lexer.UngetToken(next_token);
				my_lexer.UngetToken(current_token);
				
				global_variable_parsing();
			}
			scope_of_the_variable();
		}
        else{
            cout << "Syntax Error"<<endl;
			exit(1);
		}

    }
    
    Token agla_token = my_lexer.GetToken();
    if(agla_token.token_type != END_OF_FILE)
    {
         cout << "Syntax Error"<<endl;
		 exit(1);
    }
	Token sargun = my_lexer.GetToken();
    if(sargun.token_type != END_OF_FILE) cout << "Syntax Error"<<endl;
	int deep=0;
	while(deep<=Final_result_danish.size()-1)
	{
		cout << Final_result_danish[deep]<<endl;
		deep++;
	}
}



string determine_scope(string name_of_var, string determine_scope)
{
    int x=ST.size()-1;
	while(x>=0)
    {
        if(name_of_var==ST[x].name_of_the_variable)
        {
            if(ST[x].scope_of_the_variable == determine_scope || ST[x].value_assigned_to_scope == 1)
            {
                return ST[x].scope_of_the_variable;
            }else if(ST[x].value_assigned_to_scope==0){
                return "::";
            }
        }
	    x--;
    }
    return "?";
}


void scope_of_the_variable()
{
    Token current_token=my_lexer.GetToken();
	Token next_token=my_lexer.GetToken();
    if(next_token.token_type==LBRACE && current_token.token_type==ID)
    {
		int gurjeet=0;
		while(gurjeet<2)
		{
			public_private_variable_parsing(current_token.lexeme);
			gurjeet+=1;
		}
		
		Token this_token = my_lexer.GetToken();
		if(this_token.token_type == ID)
		{
			while(this_token.token_type == ID)
			{
				my_lexer.UngetToken(this_token);
				assignment_parsing(current_token.lexeme);
				this_token = my_lexer.GetToken();
			}

			if(this_token.token_type != RBRACE)
			{
				cout << "Syntax Error"<<endl;
				exit(1);
			}
			else my_lexer.UngetToken(this_token);
			
		}
		else
		{
		  cout << "Syntax Error"<<endl;
		  exit(1); 
		}
			
		if(my_lexer.GetToken().token_type != RBRACE)
		{
			cout << "Syntax Error"<<endl;
			exit(1);		   
		}
		else end_game(current_token.lexeme);
	}
	else{
		cout << "Syntax Error"<<endl;
		exit(1);
	}
		
    
}
void end_game(string jass){
	if(ST.size()>0)
	{
		while(ST[ST.size()-1].scope_of_the_variable == jass &&  ST.size()>0)
		{
			ST.pop_back();
			if(ST.size()<=0)	break;
		}
	}
}





vector<string> assign_variables_into_list()
{
	vector<string> result;
	Token currentToken = my_lexer.GetToken();
	while(currentToken.token_type != SEMICOLON)
	{
		if(currentToken.token_type == ID) result.push_back(currentToken.lexeme);
		currentToken = my_lexer.GetToken();			
	}
	return result;
}



void helper(Token refer_token_2, Token refer_token_1)
{
	my_lexer.UngetToken(refer_token_2);
    my_lexer.UngetToken(refer_token_1);
}

void insertInSymbolTable(string scope_of_the_variable,int value_assigned_to_scope)
{
	vector<string> list_of_variables = assign_variables_into_list();
	int var_list_size = list_of_variables.size();
	int entryNumber=0;
	while(var_list_size > 0)
	{
		ST.push_back({list_of_variables[entryNumber++],scope_of_the_variable, value_assigned_to_scope});
		var_list_size--;
	}
}

void global_variable_parsing()
{
    Token wow_token=my_lexer.GetToken();
	Token wow_token_2=my_lexer.GetToken();
	if( wow_token_2.token_type==COMMA && wow_token.token_type==ID){
		helper(wow_token_2,wow_token);
		insertInSymbolTable("::",0);
	}
	else{
        cout << "Syntax Error"<<endl;
		exit(1);
    }
}


void public_private_variable_parsing(string running_S){
	Token tok1 = my_lexer.GetToken();
	if (tok1.token_type != PRIVATE && tok1.token_type != PUBLIC) my_lexer.UngetToken(tok1);
	else
	{		
		Token tok2 = my_lexer.GetToken();
		if(tok2.token_type == COLON && tok1.token_type == PUBLIC) insertInSymbolTable(running_S,1);
		if(tok2.token_type == COLON && tok1.token_type == PRIVATE) insertInSymbolTable(running_S,2);
		if(tok2.token_type != COLON && (tok1.token_type == PRIVATE or tok1.token_type == PUBLIC))
		{
			cout << "Syntax Error"<<endl;
			exit(1);
		}
	}
}

void generateResultString(Token currentToken1,Token currentToken2,string running_Scope)
	{
		string result;
		Token currentToken3 = my_lexer.GetToken();
		if(currentToken3.token_type == ID)
		{
			Token currentToken4 = my_lexer.GetToken();
			if (currentToken4.token_type == SEMICOLON)
			{	
				if(determine_scope(currentToken1.lexeme, running_Scope).length()>0 && determine_scope(currentToken3.lexeme, running_Scope).length()>0)
				{
					if (determine_scope(currentToken1.lexeme, running_Scope) !="::")
					{
						if (determine_scope(currentToken3.lexeme, running_Scope) !="::")
						{
							string left_scope_temp = determine_scope(currentToken1.lexeme, running_Scope)+".";
							string right_scope_temp = determine_scope(currentToken3.lexeme, running_Scope)+".";
							Final_result_danish.push_back(left_scope_temp+ currentToken1.lexeme+" = "+right_scope_temp+currentToken3.lexeme);
						}
						else
						{
							string left_scope_temp = determine_scope(currentToken1.lexeme, running_Scope)+".";
							Final_result_danish.push_back(left_scope_temp+ currentToken1.lexeme+" = "+determine_scope(currentToken3.lexeme, running_Scope)+currentToken3.lexeme);
						}
						
					}
					else
					{
						if (determine_scope(currentToken3.lexeme, running_Scope) !="::")
						{
							string right_scope_temp = determine_scope(currentToken3.lexeme, running_Scope)+".";
							Final_result_danish.push_back(determine_scope(currentToken1.lexeme, running_Scope)+ currentToken1.lexeme+" = "+right_scope_temp+currentToken3.lexeme);
						}
						else
						{
							Final_result_danish.push_back(determine_scope(currentToken1.lexeme, running_Scope)+ currentToken1.lexeme+" = "+determine_scope(currentToken3.lexeme, running_Scope)+currentToken3.lexeme);
						}
						
					}
				}
			}
			else
			{
				cout << "Syntax Error"<<endl;
				exit(1);
			}
				
		}
	}


void assignment_parsing(string running_Scope)
{
	Token currentToken1 = my_lexer.GetToken();
    if(currentToken1.token_type != ID) my_lexer.UngetToken(currentToken1);
	else
	{
        Token currentToken2 = my_lexer.GetToken();
        if(currentToken2.token_type == EQUAL) generateResultString(currentToken1,currentToken2,running_Scope);
		else if(currentToken2.token_type == LBRACE)
        {
            helper(currentToken2,currentToken1);
            scope_of_the_variable();
        }
		else if(currentToken2.token_type == RBRACE)
		{
			cout << "Syntax Error"<<endl;
			exit(1);
		}
			
		else
        {
            cout << "Syntax Error"<<endl;
			exit(1);
        }
	}  
}

int main()
{
    start_parsing_the_program();
}