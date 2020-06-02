#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "../src/parser.h"

TEST_CASE("Testing parser") {
	Parser parser;
	REQUIRE( parser.parse("1+2", 0, NULL) == 3);
	REQUIRE( parser.parse("2*(3+4)", 0, NULL) == 14);
	REQUIRE( parser.parse("2+5*4", 0, NULL) == 22);
	REQUIRE( parser.parse("(1+2)", 0, NULL) == 3);
	REQUIRE( parser.parse("(2)", 0, NULL) == 2);
	REQUIRE( parser.parse("((2))", 0, NULL) == 2);
	REQUIRE( parser.parse("2*(3+3*(2+1))", 0, NULL) == 24);
}
