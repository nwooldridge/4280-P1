#include "token.h"
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

bool filter1(char c) {
	bool result = false;

    	int operators[] = {37, 40, 41, 42, 43, 44, 45, 46, 47, 58, 59, 60, 61, 62, 91, 93, 123, 125};

    	for (int i = 0; i != (sizeof(operators) / sizeof(int)); i++) {

		if (c == operators[i])
			result = true;

	}

        return result;
}

vector <token> scanner(vector<char> input) {
	
	vector <token> tokens;
	
	int table[4][6] = {
		{1,-1,2,3,0,-2},
		{1,1,1,4,4,4},
		{5,5,2,5,5,5},
		{6,6,6,6,6,6}
	};
	int lineNum = 0;
	for (int i = 0; i < input.size();) {	

		int currentState = 0;
		token t;

		while ((i < input.size()) && (currentState < 4) && (currentState > -1)) {
			
			cout << "character: " << input[i] << " value: " << (int) input[i] << endl;
			
			if (currentState == 0) {
				
				if (isupper(input[i]))
					currentState = table[currentState][0];
				else if (islower(input[i]))
					currentState = table[currentState][1];
				else if (isdigit(input[i]))
					currentState = table[currentState][2];
				else if (filter1(input[i]))	
					currentState = table[currentState][3];
				else if (isspace(input[i]))
					currentState = table[currentState][4];
				else {
					cout << "Character not in alphabet\n";
					exit(EXIT_FAILURE);
				}
			}
			//if error state is reached, break out of loop
			if (currentState == -1)
				break;

			//if at end of characters
			if (i == input.size() - 1) {
			
				currentState = table[currentState][5];
				t.tokenInstance += input[i];
				i++;
			}		
	
			
			else if (isupper(input[i + 1])) { //uppercase letters
			
				currentState = table[currentState][0];
				t.tokenInstance += input[i];
				i++;
			}
			else if (islower(input[i + 1])) { //lowercase letters
				
				currentState = table[currentState][1];
				t.tokenInstance += input[i];
				i++;
			}
			else if (isdigit(input[i + 1])) { //digits
			
				currentState = table[currentState][2];
				t.tokenInstance += input[i];
				i++;	
			}
			else if (filter1(input[i + 1])) { //operators

				currentState = table[currentState][3];
				t.tokenInstance += input[i];
				i++;
			}
			else if (isspace(input[i + 1])) { //whitespace
				
				if (input[i] == 10) //newline character
					lineNum++;
	
				currentState = table[currentState][4];
				i++;
			}
			else { //unallowed characters

				cout << "Error " << (int) input[i + 1] << " at index " << i + 1 << " is not in allowed language.\n";
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
		}

		tokens.push_back(t);			
		cout << "Token created\n";
	}
	
	for (int i = 0; i != tokens.size(); i++) {
		for (int j = 0; j != tokens[i].tokenInstance.size(); j++)
			cout << (int) tokens[i].tokenInstance[j] << endl;
		cout << endl;
	}

	return tokens;	
}
