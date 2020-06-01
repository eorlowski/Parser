CXX=g++
src=$(wildcard *.cpp)
obj=$(src:.cpp=.o)

EXE=parser.exe

$(EXE): $(obj)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c $^ 

.PHONY: clean

clean:
	rm -f $(obj) $(EXE)
