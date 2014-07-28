#ifndef _ROBOT_HPP
#define _ROBOT_HPP

#include <iostream>
#include <vector>
#include <set>

enum direction { NORTH, SOUTH, EAST, WEST };

class Robot {
private:
	int x, y;
	direction current;
	std::set<std::pair<int, int> > points;
	void turnLeft();
	void turnRight();
	void moveForward();
	void insertPoint (int x, int y);
public:
	Robot() : x(0),y(0),current(EAST) {}
	~Robot() {}
	bool isVisited (int x, int y);
	void moveToPoint (int x, int y);
	void printVisited();
	void printBluePrint();
	void turnAround();
	direction getDirection();
};

#endif
