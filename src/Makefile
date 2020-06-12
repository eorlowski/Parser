CXX=g++
src=$(wildcard *.cpp)
obj=$(src:.cpp=.o)

EXE=parser.exe

USE_READLINE=true

ifeq ($(USE_READLINE), true)
	LDLIBS=-lreadline
	CXXFLAGS+=-DUSE_READLINE
endif

$(EXE): $(obj)
	$(CXX) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) -c $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(obj) $(EXE)
