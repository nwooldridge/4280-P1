#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char ** argv) {
	
	string line;
	vector<string> lineArray;	
	string filename;	

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
	
	
	}
	

	return 0;

}
