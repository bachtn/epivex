CXX=g++
CXXFLAGS= -std=c++14 -pedantic -Wall -Wextra -Werror -g
OBJS= src/main.o src/option_parser.o src/tetravex_generator.o src/tetravex.o
EXEC= epivex

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -lboost_program_options -o $(EXEC)
clean:
	$(RM) $(EXEC) $(OBJS) $(FLOG) $(ARGS)
check: all
	python3.5 tests/ts.py
