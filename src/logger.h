#include <iostream>
#include <string>
//#include <cstdarg>

enum loglevel {ERROR, WARN, INFO, DEBUG};

class logger {
	public:
		static loglevel level;
		void info(std::string);
		void debug(std::string);
		void debug(std::string, char);
		void debug(std::string, std::string);
		void debug(std::string, int);
		void debug(std::string, int, int);
};

