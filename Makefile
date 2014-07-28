CPPFlags=-std=c++0x

all: Robot

Robot: DFS.o Robot.o
	g++ DFS.o Robot.o -o FindPath

DFS.o: DFS.cpp
	g++ -c DFS.cpp $(CPPFlags)

Robot.o: Robot.hpp Robot.cpp
	g++ -c Robot.cpp $(CPPFlags)

clean:
		rm -rf *.o FindPath