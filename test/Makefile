CXX=g++
src=$(wildcard *.cpp)
obj=$(src:.cpp=.o) ../src/parser.o ../src/logger.o

EXE=testparser.exe

$(EXE): $(obj)
	$(CXX) -o $@ $^

%.o: %.cpp ../src/parser.cpp ../src/logger.cpp
	$(CXX) -c $^

test: $(EXE)
	./$(EXE) -s

clean:
	rm -f $(EXE) $(obj)

.PHONY: test clean
