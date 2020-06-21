#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "../src/parser.h"
#include <string>

TEST_CASE("Testing parser") {
	Parser parser;
	std::string errorMessage;
	errorMessage = "";
	REQUIRE( parser.parse("1+2", errorMessage) == 3);
	REQUIRE( errorMessage == "");
	REQUIRE( parser.parse("2*(3+4)", errorMessage) == 14);
	REQUIRE( parser.parse("2+5*4", errorMessage) == 22);
	REQUIRE( parser.parse("(1+2)", errorMessage) == 3);
	REQUIRE( parser.parse("(2)", errorMessage) == 2);
	REQUIRE( parser.parse("((2))", errorMessage) == 2);
	REQUIRE( parser.parse("2*(3+3*(2+1))", errorMessage) == 24);
	REQUIRE( parser.parse("3*(4+2) ", errorMessage) == 18);
	REQUIRE( parser.parse(")", errorMessage) == 0);
	REQUIRE( errorMessage != "");
	errorMessage = "";
	REQUIRE( parser.parse("1+1", errorMessage) == 2);
	REQUIRE( errorMessage == "");
}
