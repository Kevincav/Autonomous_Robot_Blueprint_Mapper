#include "Robot.hpp"

void Robot::insertPoint(int x, int y) {
	points.insert(std::make_pair(x, y));
}
bool Robot::isVisited (int x, int y) {
	return points.find(std::make_pair(x, y)) != points.end();
}
direction Robot::getDirection() {
	return current;
}
void Robot::moveToPoint (int x, int y) {
	insertPoint(x, y);
	if (x == this->x && y == this->y)
		return;
	if (y + 1 == this->y) {
		if (current == EAST)
			turnLeft();
		else if (current == WEST)
			turnRight();
		else if (current == SOUTH)
			turnAround();
	}
	else if (y - 1 == this->y) {
		if (current == WEST)
			turnLeft();
		else if (current == EAST)
			turnRight();
		else if (current == NORTH)
			turnAround();
	}
	else if (x - 1 == this->x) {
		if (current == SOUTH)
			turnLeft();
		else if (current == NORTH)
			turnRight();
		else if (current == WEST)
			turnAround();
	}
	else if (x + 1 == this->x) {
		if (current == NORTH)
			turnLeft();
		else if (current == SOUTH)
			turnRight();
		else if (current == EAST)
			turnAround();
	}
	moveForward();
}
void Robot::turnLeft () {
	if (current == NORTH)
		current = WEST;
	else if (current == WEST)
		current = SOUTH;
	else if (current == SOUTH)
		current = EAST;
	else
		current = NORTH;
}
void Robot::turnRight () {
	if (current == NORTH)
		current = EAST;
	else if (current == WEST)
		current = NORTH;
	else if (current == SOUTH)
		current = WEST;
	else
		current = SOUTH;
}
void Robot::turnAround () {
	turnLeft();
	turnLeft();
}
void Robot::moveForward () {
	switch (current) {
		NORTH: y--;
			   break;
		SOUTH: y++;
			   break;
		EAST : x++;
			   break;
		WEST : x--;
			   break;
	}
}
void Robot::printVisited() {
    std::set<std::pair<int,int> >::iterator it = points.begin();
	int minX = it->first, maxX = it->first;
	int minY = it->second, maxY = it->second;

	for ( ; it != points.end(); ++it) {
		if (it->first < minX)
			minX = it->first;
		else if (it->first > maxX)
			maxX = it->first;
		if (it->second < minY)
			minY = it->second;
		else if (it->second > maxY)
			maxY = it->second;
	}

	std::vector<std::vector<char> > grid(maxX-minX+3, std::vector<char>(maxY-minY+3, ' '));
	for (it = points.begin(); it != points.end(); ++it)
		grid[it->first - minX + 1][it->second - minY + 1] = '@';

	for (int i=0;i<grid.size();i++)
		std::cout << &grid[i][0] << std::endl;
}
void Robot::printBluePrint() {
    std::set<std::pair<int,int> >::iterator it = points.begin();
	int minX = it->first, maxX = it->first;
	int minY = it->second, maxY = it->second;

	for ( ; it != points.end(); ++it) {
		if (it->first < minX)
			minX = it->first;
		else if (it->first > maxX)
			maxX = it->first;
		if (it->second < minY)
			minY = it->second;
		else if (it->second > maxY)
			maxY = it->second;
	}
	
	std::vector<std::vector<char> > grid(maxX-minX+3, std::vector<char>(maxY-minY+3, ' '));
	for (it = points.begin(); it != points.end(); ++it)
		grid[it->first - minX + 1][it->second - minY + 1] = '@';
	
	for (int i=0;i<grid.size();i++)
		for (int j=0;j<grid[i].size();j++) {
			if (grid[i][j] != ' ')
				continue;
			for (int k=i-1;k<=i+1;k++) {
				if (k < 0 || k >= grid.size())
					continue;
				for (int l=j-1;l<=j+1;l++) {
					if (l < 0 || l >= grid[k].size())
						continue;
					if (grid[k][l] == '@') {
						grid[i][j] = '#';
						break;
					}
				}
				if (grid[i][j] == '#')
					break;
			}
		}
	for (int i=0;i<grid.size();i++)
		for (int j=0;j<grid[i].size();j++)
			if (grid[i][j] != '#')
				grid[i][j] = ' ';

	for (int i=0;i<grid.size();i++)
		std::cout << &grid[i][0] << std::endl;
}
