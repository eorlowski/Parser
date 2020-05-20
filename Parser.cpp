#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <map>

using namespace std;

enum ElemType { OperandType, OperatorType};

class Element {
	public:
		ElemType type;
		string content;
};

class Operators {
	map<char,int> operatorMap;
	public:
		Operators() {
			operatorMap.insert({'+', 2});
			operatorMap.insert({'-', 2});
			operatorMap.insert({'*', 1});
			operatorMap.insert({'/', 1});
		}
		int getPriority(char symbol) {
			auto it = operatorMap.find(symbol);
			return it->second;
		}
};

class Parser {
	Operators ops;
	list<Element> elemList;
	public:
	void parse(string s) {
		cout << "Length of string: " << s.length() << endl;
		bool readingNumber = false;
		string elem;
		Element element;
		int i;
		long int result;
		for (i = 0; i < s.length(); i++) {
			cout << "Found character: " << s[i];
			if (s[i] >= '0' && s[i] <= '9') {
				if (!readingNumber) {
					readingNumber = true;
					elem = s[i];
				}
				else {
					elem += s[i];
				}
				cout << "\n\tFound digit... ";
			}
			else if (s[i] == '+' || s[i] == '*') {
				if (readingNumber) {
					readingNumber = false;
					cout << "\nClosing number read with: " << elem; 
					element.type = OperandType;
					element.content = elem;
					elemList.push_back(element);
				}
				cout << "\n\tFound operator... with priority: " << ops.getPriority(s[i]);
				element.type = OperatorType;
				element.content = s[i];
				elemList.push_back(element);
			}
			else {
				cout << "\nSyntax error!";
				exit(1);
			}

			cout << endl;
		}
		if (readingNumber) {
			elem += s[i];
			cout << "\nClosing number at end of file: " << elem;
			element.type = OperandType;
			element.content = elem;
			elemList.push_back(element);
		}
		cout << "\nNumber of elements in list: " << elemList.size() << endl;
		printList(elemList);
		result = evaluateParsedStatement(elemList); 
		cout << "\nResult is: " << result << endl;
	}

	void printList(list<Element> elemList) {
		cout << "Printing list" << endl;
		for (auto const& e : elemList) {
			cout << "Element content: " << e.content << ", type: " << (e.type == OperandType ? "Operand" : "Operator") << endl;
		}
	}

	long evaluateParsedStatement(list<Element> elemList) {
		Operators ops;
		long int result, subResult;
		Element element, elem1, elem2, elem3, elem4, elem5;
		list<Element>::iterator iterator;
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
				cout << "got in size() > 3 part, size() is: " << elemList.size() << endl;
				// Skipping checks for operand/operator
				iterator = elemList.begin();
				elem1 = *iterator++;
				elem2 = *iterator++;
				elem3 = *iterator++;
				elem4 = *iterator++;
				elem5 = *iterator++;
				if (ops.getPriority(elem2.content[0]) <= ops.getPriority(elem4.content[0])) {
					subResult = evaluateElementaryOperation(elem1.content, elem2.content, elem3.content);
					cout << "Subresult: " << subResult << endl;
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
					cout << "Subresult: " << subResult << endl;
					iterator = elemList.begin();
					iterator++;
					iterator++;
					element.content = to_string(subResult);
					element.type = OperandType;
					elemList.insert(iterator, 1, element);
					cout << "After insert, size is: " << elemList.size() << endl;
					iterator = elemList.begin();
					iterator++;
					iterator++;
					iterator++;
					iterator = elemList.erase(iterator);
					cout << "After erase, size is: " << elemList.size() << endl;
					printList(elemList);
					iterator = elemList.erase(iterator);
					cout << "After erase, size is: " << elemList.size() << endl;
					printList(elemList);
					iterator = elemList.erase(iterator);
					cout << "After erase, size is: " << elemList.size() << endl;
					printList(elemList);
				}
				cout << "After subresult evalutation, size is: " << elemList.size() << endl;
			}
		}
		return result;
	}

	long evaluateElementaryOperation(string term1, string Operator, string term2) {
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
		cout << "term1: " << term1Int << ", term2: " << term2Int << endl;
		return result;
	}
};

int main(int argc, char** argv) {

	Parser parser;
	string s;
	if (argc > 1) {
		cout << "Going to calculate: " << argv[1] << endl;
		s = argv[1];
	}
	else {
		s = "2*5+3*4+9*8*7";
	}

	parser.parse(s);

	return 0;
}
