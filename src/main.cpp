#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <map>
#include "Parser.h"
#ifdef USE_READLINE
	#include <readline/readline.h>
	#include <readline/history.h>
#endif

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
#ifdef USE_READLINE
		const char *line;
		while ((line = readline("> ")) != nullptr && ((string) line != "exit")) {
			if (*line) {
				add_history(line);
				result = parser.parse(line, 0, NULL);
				cout << result << endl;
			}
			free((void *) line);
		}
#else
		cout << "> ";
		std::getline(std::cin, s);
		while (!std::cin.eof() && s != "exit") {
			result = parser.parse(s, 0, NULL);
			cout << result << endl;
			cout << "> ";
			std::getline(std::cin, s);
		}
#endif
	}

	return 0;
}
