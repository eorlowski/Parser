#include <map>
#include <string>
#include <list>
#include "logger.h"

enum ElemType { OperandType, OperatorType};

class Element {
	public:
		ElemType type;
		std::string content;
};

class Operators {
	std::map<char,int> operatorMap;
	public:
		Operators();
		int getPriority(char);
};

class Parser {
	logger log;
	Operators ops;
	private:
		long evaluateParsedStatement(std::list<Element>);
		void printList(std::list<Element>);
		long evaluateElementaryOperation(std::string, std::string, std::string); 
	public:
		long parse(std::string, int, int*);
};
