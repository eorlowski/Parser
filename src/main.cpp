#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <map>
#include "Parser.h"

using namespace std;

int main(int argc, char** argv) {

	Parser parser;
	string s;
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			s += argv[i];
		}
		cout << "Going to calculate: " << s << endl;
//		s = argv[1];
	}
	else {
//		s = " 2 *5+3*4+9*8*7";
		getline(cin, s);
	}

	// let 0 be the default for recursionLevel
	long int result = parser.parse(s, 0, NULL);

	cout << "Result of parser is: " << result << endl;

	return 0;
}
