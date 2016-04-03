CXX=g++
CXXFLAGS= -std=c++14 -pedantic -Wall -Wextra -Werror -O3
OBJS= src/main.o src/option_parser.o src/tetravex_generator.o src/tetravex.o \
	src/node.o src/bdd.o

EXEC= epivex

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -lboost_program_options -o $(EXEC)
clean:
	$(RM) $(EXEC) $(OBJS)
check: all
	python3.5 tests/ts.py
