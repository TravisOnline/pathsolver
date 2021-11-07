.default: all

all: assignment1

clean: rm -f assignment1 *.o

assignment1: main.o Node.o NodeList.o PathSolver.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
