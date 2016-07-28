CXX=g++
CXXFLAGS=-std=c++11
BIN=checkers.exe
CXX_DEBUG_FLAGS=-g

SRCDIR= src
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(SRC:%.cpp=%.o)

.PHONY: debug
debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug: all

all: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c %.h
	$(CXX) $@ -c $<

clean:
	rm -f $(SRCDIR)/*.o $(BIN)  *~
