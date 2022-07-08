/*
 * Copyright (C) Rida Bazzi, 2016
 *
 * Do not share this file with anyone
 */
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>

#include "lexer.h"
#include "inputbuf.h"

using namespace std;

string reserved[] = { "END_OF_FILE",
    "IF", "WHILE", "DO", "THEN", "PRINT",
    "PLUS", "MINUS", "DIV", "MULT",
    "EQUAL", "COLON", "COMMA", "SEMICOLON",
    "LBRAC", "RBRAC", "LPAREN", "RPAREN",
    "NOTEQUAL", "GREATER", "LESS", "LTEQ", "GTEQ",
    "DOT", "NUM", "ID", "ERROR",
    "PRIVATE","PUBLIC", "LBRACE", "RBRACE"
	//"REALNUM", "BASE08NUM", "BASE16NUM"
};

#define KEYWORDS_COUNT 5
string keyword[] = { "IF", "WHILE", "DO", "THEN", "PRINT" };

void Token::Print()
{
    cout << "{" << this->lexeme << " , "
         << reserved[(int) this->token_type] << " , "
         << this->line_no << "}\n";
}

LexicalAnalyzer::LexicalAnalyzer()
{
    this->line_no = 1;
    tmp.lexeme = "";
    tmp.line_no = 1;
    tmp.token_type = ERROR;
}

bool LexicalAnalyzer::SkipSpace()
{
    char c;
    bool space_encountered = false;

    input.GetChar(c);
    // cout << "inside getchar: "<<c<<endl;
    line_no += (c == '\n');

    while (!input.EndOfInput() && isspace(c)) {
        space_encountered = true;
        input.GetChar(c);
        // cout << "inside getchar1: "<<c<<endl;
        line_no += (c == '\n');
    }

    if (!input.EndOfInput()) {
        input.UngetChar(c);
    }
    return space_encountered;
}

bool LexicalAnalyzer::IsKeyword(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return true;
        }
    }
    return false;
}

TokenType LexicalAnalyzer::FindKeywordIndex(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return (TokenType) (i + 1);
        }
    }
    return ERROR;
}

bool LexicalAnalyzer::Skip_the_comments()
{
	bool skip_comment = false;
    char First_comment;
    input.GetChar(First_comment);
	if (First_comment != '/') input.UngetChar(First_comment);
	else
    {
        char Second_comment;
        input.GetChar(Second_comment);
		if(Second_comment != '/')
		{
			input.UngetChar(Second_comment);
            input.UngetChar(First_comment);
		}

        else
        {
            char gurjant;
            input.GetChar(gurjant);
            while(gurjant != '\n') 
            {
                input.GetChar(gurjant);
            }
            int n = (int)gurjant;
            skip_comment = true;
            SkipSpace();
            Skip_the_comments();
            SkipSpace();
            Skip_the_comments();
            SkipSpace();
        }
    }
    return skip_comment;
}

Token LexicalAnalyzer::ScanNumber()
{
    char c;
    input.GetChar(c);
    if (isdigit(c)) 
	{
        if (c == '0') {
            tmp.lexeme = "0";
        } else {
            tmp.lexeme = "";
            while (!input.EndOfInput() && isdigit(c)) {
                tmp.lexeme += c;
                input.GetChar(c);
            }
            if (!input.EndOfInput()) {
                input.UngetChar(c);
            }
        }

        tmp.token_type = NUM;
        tmp.line_no = line_no;
       // Check for expected tokens
        //extendedNumber(c);
        return tmp;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
        tmp.line_no = line_no;
        return tmp;
    }
}
/*
bool LexicalAnalyzer::extendedNumber(char c){
         if(!input.EndOfInput() )
	{
	input.GetChar(c);
	if(c == 46)
		{
	checkRealNum(c);
		}
		else if(c == 120 )
		{
		Base08Num(c);
		}
		else if(c > 64 && c < 71)
		{
		 Base16Num(c);
	    }
		else
		{
			input.UngetChar(c);
		}

	}
       return true;
     }

bool LexicalAnalyzer::checkRealNum(char c)
{
	int isRealNum = 0;
	string buffer = "";
        buffer += c;

	if(!input.EndOfInput())
	{

		input.GetChar(c);

		while(!input.EndOfInput() && c > 47 && c < 58)
		{

			buffer += c;
			input.GetChar(c);
			isRealNum = 1;
		}
		EndOfInputUngetChar(c);

		if(isRealNum == 1)
		{
			tmp.lexeme += buffer;
			tmp.token_type = REALNUM;
			tmp.line_no = line_no;
		}
		else
		{

			ungetCharacters(buffer);
		}
   }
   else
   {
	   ungetCharacters(buffer);
   }

	return isRealNum == 1;
}

bool LexicalAnalyzer::Base08Num(char c)
{

	string buffer = "";  
	buffer += c;
	int isBase8 = 1;
	

         int index = 0;
         
	for(index = 0; index < 2 && input.EndOfInput() == false ; index++){
		input.GetChar(c);
		  buffer += c;
               
		   
	}
       if(index != 2){
         isBase8 = 0;    
        }

	

	if(isBase8 && buffer[1] == 48 && buffer[2] == 56 )
	{
		for(int i = 0; i< tmp.lexeme.length(); i++)
		{
			if(tmp.lexeme[i] > 55 )
			{
				isBase8 = 0;
				break;
			}
		}
		if(isBase8 == 1)
		{
			tmp.token_type = BASE08NUM;
			tmp.lexeme += buffer;
			tmp.line_no = line_no;
		}
		else
		{
            
			ungetCharacters(buffer);
		}

	}
	else if(isBase8 == 1)
	{
           if(buffer[1] == 49 && buffer[2] == 54){
		tmp.token_type = BASE16NUM;
		tmp.lexeme += buffer;
		tmp.line_no = line_no;
           }else{
               isBase8 = 0;
               ungetCharacters(buffer);
           }
	}
	else
	{
       
    	ungetCharacters(buffer);
        }

	return isBase8 == 1;

}

bool LexicalAnalyzer::Base16Num(char c){
	 string buffer = "";
	 buffer += c;
	 int isBase16 = 1;
	 while(  ((c > 47 && c < 58) || (c > 64 && c < 71)) && !input.EndOfInput())
		{
			input.GetChar(c);
			buffer += c;
		}
		EndOfInputUngetChar(c);
		int index = 0;
		char check[] = {'x','1','6'};
		for(index = 0; index < 3  && input.EndOfInput() == false; index++){
		
		    
			input.GetChar(c);
                        if(index != 0){
			  buffer += c;
                        }
			if(check[index] != c){
				isBase16 = 0;
				break;
			}
			
		   
		}
                if(index !=3){
                       isBase16 = 0;
                   }
	
		if(isBase16 == 1)
		{
			tmp.token_type = BASE16NUM;
			tmp.lexeme += buffer;
			tmp.line_no = line_no;
		}
		
		if(isBase16 == 0)
			{
				ungetCharacters(buffer);
			}
             return isBase16 == 1;
}
bool LexicalAnalyzer::EndOfInputUngetChar(char c){
	if(!input.EndOfInput())
		{
			input.UngetChar(c);
		}

     return true;
}
bool LexicalAnalyzer::ungetCharacters(string buffer){
	
    int i = buffer.length() - 1;
    while(i >= 0){
       input.UngetChar(buffer[i]);
        i--;
   }

 return true;
}

*/



Token LexicalAnalyzer::ScanIdOrKeyword()
{
    char c;
    input.GetChar(c);
    // cout << "ID lo c: "<<c<<endl;

    if (isalpha(c)) {
        tmp.lexeme = "";
        while (!input.EndOfInput() && isalnum(c)) {
            tmp.lexeme += c;
            input.GetChar(c);
        }
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.line_no = line_no;
        if (IsKeyword(tmp.lexeme))
            tmp.token_type = FindKeywordIndex(tmp.lexeme);
        else
            tmp.token_type = ID;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
    }
    return tmp;
}

int LexicalAnalyzer::Determine_public_private()
{
    string danish="";
	string Pu="blic";
	string Pr="ivate";
	int length_public=4;
	int length_private=5;
	char c1;
	input.GetChar(c1);
	if (c1=='p')
	{
		danish+=c1;
		char c2;
		input.GetChar(c2);
		
		if (c2=='u')
		{
			danish+=c2;
			int i=0;	
			while(i<length_public)
			{
				char c3;
				input.GetChar(c3);
				if(input.EndOfInput()) break;
				danish += c3;
				i++;
			}	
		}
		if (c2=='r')
		{
			danish+=c2;
			int j=0;
			while(j<length_private)
			{
				char cc_2;
				input.GetChar(cc_2);
				if(input.EndOfInput()) break;
				danish += cc_2;
				j++;
			}
		}
	}
	if(danish == "public") return 1;
	if (danish== "private") return 2;
	int entry=danish.length()-1;
	while(entry>=0)
	{
		input.UngetChar(danish[entry]);
		entry--;
	}
	return 0;	
}


// you should unget tokens in the reverse order in which they
// are obtained. If you execute
//
//    t1 = lexer.GetToken();
//    t2 = lexer.GetToken();
//    t3 = lexer.GetToken();
//
// in this order, you should execute
//
//    lexer.UngetToken(t3);
//    lexer.UngetToken(t2);
//    lexer.UngetToken(t1);
//
// if you want to unget all three tokens. Note that it does not
// make sense to unget t1 without first ungetting t2 and t3
//
TokenType LexicalAnalyzer::UngetToken(Token tok)
{
    tokens.push_back(tok);;
    return tok.token_type;
}

Token LexicalAnalyzer::GetToken()
{
    char c;

    // if there are tokens that were previously
    // stored due to UngetToken(), pop a token and
    // return it without reading from input
    if (!tokens.empty()) {
        tmp = tokens.back();
        tokens.pop_back();
        return tmp;
    }

    SkipSpace();
    Skip_the_comments();
    tmp.lexeme = "";
    tmp.line_no = line_no;
    input.GetChar(c);
    switch (c) {
        case '.':
            tmp.token_type = DOT;
            return tmp;
        case '+':
            tmp.token_type = PLUS;
            return tmp;
        case '-':
            tmp.token_type = MINUS;
            return tmp;
        case '/':
            tmp.token_type = DIV;
            return tmp;
        case '*':
            tmp.token_type = MULT;
            return tmp;
        case '=':
            tmp.token_type = EQUAL;
            tmp.lexeme = "=";
            return tmp;
        case ':':
            tmp.token_type = COLON;
            tmp.lexeme = ":";
            return tmp;
        case ',':
            tmp.token_type = COMMA;
            return tmp;
        case ';':
            tmp.token_type = SEMICOLON;
            tmp.lexeme = ";";
            return tmp;
        case '[':
            tmp.token_type = LBRAC;
            return tmp;
        case ']':
            tmp.token_type = RBRAC;
            return tmp;
        case '(':
            tmp.token_type = LPAREN;
            return tmp;
        case ')':
            tmp.token_type = RPAREN;
            return tmp;
        case '{':   
            tmp.token_type = LBRACE;
            tmp.lexeme = "{";
            return tmp;
        case '}':
            tmp.token_type = RBRACE;
            tmp.lexeme = "}";
            return tmp;
        case '<':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = LTEQ;
            } else if (c == '>') {
                tmp.token_type = NOTEQUAL;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = LESS;
            }
            return tmp;
        case '>':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = GTEQ;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = GREATER;
            }
            return tmp;
        default:
            if (isdigit(c)) 
			{
                input.UngetChar(c);
                return ScanNumber();
            } 
			//check if they are private declared or public declared
			else if (isalpha(c)) 
			{
                input.UngetChar(c);
					if(c == 'p') 
					{
						int result_answer = Determine_public_private();
						if(result_answer == 1)
						{
							tmp.token_type = PUBLIC;
							tmp.lexeme = "PUBLIC";
							return tmp;
						}
						if(result_answer == 2)
						{
							tmp.token_type = PRIVATE;
							tmp.lexeme = "PRIVATE";
							return tmp;
						}
						
					}
                return ScanIdOrKeyword();
            } 
			else if (input.EndOfInput())
                tmp.token_type = END_OF_FILE;
            else
                tmp.token_type = ERROR;

            return tmp;
    }
}

/*int main()
{
    LexicalAnalyzer lexer;
    Token token;

    token = lexer.GetToken();
    token.Print();
    while (token.token_type != END_OF_FILE)
    {
        token = lexer.GetToken();
        token.Print();
    }
}
*/