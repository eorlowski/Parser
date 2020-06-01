#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <map>
#include "Parser.h"

using namespace std;

int main(int argc, char** argv) {

	logger log;
	Parser parser;
	string s;
	if (argc > 1) {
		int expressionStart = 1;
		if ((string) argv[1] == "-d") {
			log.level = DEBUG;
			expressionStart = 2;
		}
		for (int i = expressionStart; i < argc; i++) {
			s += argv[i];
		}
		log.debug("Going to calculate: " + s);
	}
	else {
		getline(cin, s);
	}

	// let 0 be the default for recursionLevel
	long int result = parser.parse(s, 0, NULL);

	cout << "Result of parser is: " << result << endl;

	return 0;
}
