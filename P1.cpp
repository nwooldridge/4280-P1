#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include "token.h"
#include "scanner.h"

using namespace std;

int main(int argc, char ** argv) {
	
	string line;
	vector<string> lineArray;
	vector<char> textArray;	
	string filename;
	ifstream input;	

	if (argc > 2) {
		cout << "Incorrect params\n";
		exit(EXIT_FAILURE);
	} 
	if (argc == 1) {//read from stdin

		
		while (getline(cin, line)) {

                        lineArray.push_back(line + "\n");

                }

	}		
	else {
	
		filename = argv[1];
		filename += ".input1";
		input.open(filename.c_str());

		if (input == NULL) {
			cout << "Error opening file: " << filename << endl;
			exit(EXIT_FAILURE);
		}
	
		while (getline(input, line)) {
                        lineArray.push_back(line + "\n");
                }

		input.close();
	}

	for (int i = 0; i != lineArray.size(); i++) 
		for (int j = 0; j != lineArray[i].length(); j++)
                	textArray.push_back(lineArray[i][j]);
      
	vector<token> tokens = scanner(textArray);

	return 0;

}
