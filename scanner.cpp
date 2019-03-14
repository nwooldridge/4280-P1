#include "token.h"
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

vector<token> scanner(vector<char> input) {

	vector<token> tokens;

	int [][] table = {
		{-1,0,1,2},
		{0,0,0,4},
		{5,5,1,5},
		{6,6,6,6}
	}
	int lineNum = 0;
	for (int i = 0; i != input.size(); i++) {
		
		int currentState = 0;
		token t;	

		while ((currentState < 4) && (currentState > -1)) {
		
			if (isupper(input[i])) { //uppercase letters
			
				currentState = table[currentState][0];
				t.tokenInstance += input[i];
				i++;
			}
			else if (islower(input[i])) { //lowercase letters
				
				currentState = table[currentState][1];
				t.tokenInstance += input[i];
				i++;
			}
			else if (isdigit(input[i])) { //digits
			
				currentState = table[currentState][2];
				t.tokenInstance += input[i];
				i++;	
			}
			else if (filter1(input[i])) { //operators

				currentState = table[currentState][3];
				t.tokenInstance += input[i];
				i++;
			}
			else if (isspace(input[i])) { //whitespace
				
				if (input[i] == 10) //newline character
					lineNum++;
	
				currentState = table[currentState][4];
				i++;
			}
			else { //unallowed characters

				cout << "Error " << input[i] << " is not in allowed language.\n";
				exit(EXIT_FAILURE);		
			}
		}
			
		switch (currentState) {
			
			case -1:
				cout << "No token begins with lowercase letter.\n";
	                        exit(EXIT_FAILURE);
				break;
			case 4: 
				t.tokenID = "IDToken";
				break;
			case 5:
				t.tokenID = "digitToken";
				break;
			case 6:
				t.tokenID = "operatorToken";
				break;
			case default:
				cout << "Error, state " << currentState << " is not an allowed state.\n";
				exit(EXIT_FAILURE);
				break;
		}

		tokens.push_back(t);			
	}	
}

//Checks if operator is in allowed language
bool filter1(char c) {
	
	bool result = false;

	int[] operators = {37, 40, 41, 42, 43, 44, 45, 46, 47, 58, 59, 60, 61, 62, 91, 93, 123, 125};

	for (int i = 0; i != operators.size(); i++) {
		
		if (c == operators[i])
			result = true;

	} 	

	return result;
}
