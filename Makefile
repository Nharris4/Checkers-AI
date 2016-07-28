CXX=g++
CXXFLAGS=-std=c++11
BIN=checkers.exe

SRCDIR=/src/
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c %.h
	$(CXX) $@ -c $<

clean:
	rm -f *.o $(BIN)  *~
