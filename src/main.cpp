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
	long int result;

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
		// let 0 be the default for recursionLevel
		result = parser.parse(s, 0, NULL);

		cout << result << endl;
	}
	else {
		// interactive mode
		cout << ">";
		std::getline(std::cin, s);
		while (!std::cin.eof() && s != "exit") {
			result = parser.parse(s, 0, NULL);
			cout << result << endl;
			cout << ">";
			std::getline(std::cin, s);
		}
	}

	return 0;
}
