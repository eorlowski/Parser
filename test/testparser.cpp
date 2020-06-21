#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "../src/parser.h"

TEST_CASE("Testing parser") {
	Parser parser;
	REQUIRE( parser.parse("1+2") == 3);
	REQUIRE( parser.parse("2*(3+4)") == 14);
	REQUIRE( parser.parse("2+5*4") == 22);
	REQUIRE( parser.parse("(1+2)") == 3);
	REQUIRE( parser.parse("(2)") == 2);
	REQUIRE( parser.parse("((2))") == 2);
	REQUIRE( parser.parse("2*(3+3*(2+1))") == 24);
	REQUIRE( parser.parse("3*(4+2) ") == 18);
}
