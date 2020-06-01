#include <iostream>
#include <string>
#include <algorithm>
#include "logger.h"

loglevel logger::level = ERROR;

void logger::info(std::string s) {
	if (level > 1) {
		std::cout << "INFO: " << s << std::endl;
	}
}

void logger::debug(std::string s) {
	if (level > 2) {
		std::cout << "DEBUG: " << s << std::endl;
	}
}

void logger::debug(std::string s, char ch) {
	if (level > 2) {
		replace(s.begin(), s.end(), '%', ch);
		logger::debug(s);
	}
}

void logger::debug(std::string s, std::string s1) {
	if (level > 2) {
		int pos = s.find("%");
		s.replace(pos, 1, s1);
		logger::debug(s);
	}
}

void logger::debug(std::string s, int i) {
	if (level > 2) {
		int pos = s.find("%");
		s.replace(pos, 1, std::to_string(i));
		logger::debug(s);
	}
}

void logger::debug(std::string s, int i, int j) {
	if (level > 2) {
		int pos = s.find("%");
		s.replace(pos, 1, std::to_string(i));
		pos = s.find("%");
		s.replace(pos, 1, std::to_string(j));
		logger::debug(s);
	}
}
