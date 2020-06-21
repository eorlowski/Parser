#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <map>
#include "Parser.h"

using namespace std;

Operators::Operators() {
	operatorMap.insert({'+', 2});
	operatorMap.insert({'-', 2});
	operatorMap.insert({'*', 1});
	operatorMap.insert({'/', 1});
}

int Operators::getPriority(char symbol) {
	auto it = operatorMap.find(symbol);
	return it->second;
}

long Parser::parse(string s, int recursionLevel, int* stringPos) {
	list<Element> elemList;
	log.debug ("Length of string: " + to_string(s.length()) + ", recursion level: " + to_string(recursionLevel) );
	bool readingNumber = false;
	string elem;
	Element element;
	int i;
	long int result;
	int relStringPos;
	for (i = 0; i < s.length(); i++) {
		log.debug("Found character: %", s[i]);
		if (s[i] == '(') {
			log.debug("Entering next level of recursion...");
			long subResult = parse(s.substr(i+1), ++recursionLevel, &relStringPos);
			// Add element and jump to corresponding closing bracket
			element.type = OperandType;
			element.content = to_string(subResult);
			elemList.push_back(element);
			i += relStringPos + 1;
		}
		else if (s[i] == ')') {
			if (recursionLevel < 1) {
				cout << "Syntax error: ')' without corresponding '('" << endl;
				exit(1);
			}
			*stringPos = i;
			break; // exit loop
		}
		else if (s[i] >= '0' && s[i] <= '9') {
			if (!readingNumber) {
				readingNumber = true;
				elem = s[i];
			}
			else {
				elem += s[i];
			}
			log.debug("\t\tFound digit... ");
		}
		//TODO: Use a search in operatormap function
		else if (s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '-') {
			if (readingNumber) {
				readingNumber = false;
				log.debug("Closing number read with: %", elem); 
				element.type = OperandType;
				element.content = elem;
				elemList.push_back(element);
			}
			log.debug("\t\tFound operator... with priority: %", ops.getPriority(s[i]));
			element.type = OperatorType;
			element.content = s[i];
			elemList.push_back(element);
		}
		else if (s[i] == ' ') {
			if (readingNumber) {
				readingNumber = false;
				log.debug("Closing number read after whitespace with: %", elem); 
				element.type = OperandType;
				element.content = elem;
				elemList.push_back(element);
			}
		}
		else {
			cout << "\nSyntax error!";
				exit(1);
		}
	} // for-loop
	if (readingNumber) {
		if (recursionLevel == 0) {
			elem += s[i];
		}
		log.debug("Closing number at end of file: %", elem);
		element.type = OperandType;
		element.content = elem;
		elemList.push_back(element);
	}
	log.debug("Number of elements in list: %", (int) elemList.size());
	printList(elemList);
	result = evaluateParsedStatement(elemList); 
	log.debug("Result is: %", (int) result);

	return result;
}

void Parser::printList(list<Element> elemList) {
	log.debug("Printing list");
	for (auto const& e : elemList) {
		log.debug("Element content: " + e.content + ", type: " + (e.type == OperandType ? "Operand" : "Operator"));
	}
}

long Parser::evaluateParsedStatement(list<Element> elemList) {
	Operators ops;
	long int result, subResult;
	Element element, elem1, elem2, elem3, elem4, elem5;
	list<Element>::iterator iterator;
	if (elemList.size() == 1) {
		iterator = elemList.begin();
		elem1    = *iterator++;
		stringstream ss;
		ss << elem1.content;
		ss >> result;
	}
	else { // TODO: correct indentation
		while (elemList.size() > 1) {
			if (elemList.size() == 3) {
				iterator = elemList.begin();
				elem1 = *iterator++;
				elem2 = *iterator++;
				elem3 = *iterator++;
				result = evaluateElementaryOperation(elem1.content, elem2.content, elem3.content);
				elemList.erase(elemList.begin());
				elemList.erase(elemList.begin());
				elemList.erase(elemList.begin());
				element.content = to_string(result);
				element.type = OperandType;
				elemList.push_front(element);
			}
			else if (elemList.size() > 3) {
				if (elemList.size() < 5) {
					cout << "Syntax error!" << endl;
					exit(1);
				}
				log.debug("got in size() > 3 part, size() is: %", (int) elemList.size());
				// Skipping checks for operand/operator
				iterator = elemList.begin();
				elem1 = *iterator++;
				elem2 = *iterator++;
				elem3 = *iterator++;
				elem4 = *iterator++;
				elem5 = *iterator++;
				if (ops.getPriority(elem2.content[0]) <= ops.getPriority(elem4.content[0])) {
					subResult = evaluateElementaryOperation(elem1.content, elem2.content, elem3.content);
					log.debug("Subresult: %", (int) subResult);
					element.content = to_string(subResult);
					element.type = OperandType;
					elemList.erase(elemList.begin());
					elemList.erase(elemList.begin());
					elemList.erase(elemList.begin());
					elemList.push_front(element);
					printList(elemList);
				}
				else {
					subResult = evaluateElementaryOperation(elem3.content, elem4.content, elem5.content); 
					log.debug("Subresult: %", (int) subResult);
					iterator = elemList.begin();
					iterator++;
					iterator++;
					element.content = to_string(subResult);
					element.type = OperandType;
					elemList.insert(iterator, 1, element);
					iterator = elemList.begin();
					iterator++;
					iterator++;
					iterator++;
					iterator = elemList.erase(iterator);
					iterator = elemList.erase(iterator);
					iterator = elemList.erase(iterator);
					log.debug("After substitution, size is: %", (int) elemList.size());
					printList(elemList);
				}
				log.debug("After subresult evalutation, size is: %", (int) elemList.size());
			}
		} // while loop
	} // else
	return result;
}

long Parser::evaluateElementaryOperation(string term1, string Operator, string term2) {
	long int term1Int, term2Int, result;
	stringstream ss;
	ss << term1;
	ss >> term1Int;
	stringstream ss2;
	ss2 << term2;
	ss2 >> term2Int;
	if (Operator == "+") {
		result = term1Int+term2Int;
	}
	else if (Operator == "*") {
		result = term1Int*term2Int;
	}
	else if (Operator == "/") {
		result = term1Int/term2Int;
	}
	else if (Operator == "-") {
		result = term1Int-term2Int;
	}
	log.debug("term1: %, term2: %", term1Int, term2Int);
	return result;
}
