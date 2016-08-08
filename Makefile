CXX=g++
CXXFLAGS=-std=c++11 -Wall -Iinc/
BIN=checkers.exe
CXX_DEBUG_FLAGS=-g

SRCDIR= src
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $+ -pthread

%.o: %.c %.h
	$(CXX) $@ -c $< -pthread


.PHONY: debug
debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug: all

.PHONY: clean
clean: 
	rm -f $(SRCDIR)/*.o $(BIN)  *~
