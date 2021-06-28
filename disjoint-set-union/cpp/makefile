# compiler
CXX=g++
CXXFLAGS=-g -std=c++14  -Wall -Werror
LDFLAGS=-L/usr/local/lib -lgtest -lgtest_main -pthread
BIN=$(shell basename $(CURDIR))

# folders
SOURCEDIR=source
BUILDDIR=build

SRC=$(wildcard $(SOURCEDIR)/*.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^ $(LDFLAGS)

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)
