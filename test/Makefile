CXX=g++
src=$(wildcard *.cpp)
obj=$(src:.cpp=.o)

EXE=testparser.exe

$(EXE): $(obj)
	$(CXX) -o $@ $^

%.o: %.cpp ../src/parser.cpp
	$(CXX) -c $^

test: $(EXE)
	./$(EXE) -s

.PHONY: test
