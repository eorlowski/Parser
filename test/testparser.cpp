#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "../src/parser.cpp"

TEST_CASE("Testing parser") {
	Parser parser;
	REQUIRE( parser.parse("1+2", 0, NULL) == 3);
	REQUIRE( parser.parse("2*(3+4)", 0, NULL) == 14);
	REQUIRE( parser.parse("2+5*4", 0, NULL) == 22);
}
