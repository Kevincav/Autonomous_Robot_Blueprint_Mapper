#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include "Robot.hpp"

#include "laser_lib/LRFInterface.hpp"
#include "laser_lib/urg_headers/UrgUsbCom.h"
#include "laser_lib/urg_headers/FindComPorts.h"
#include "laser_lib/urg_headers/UrgCtrl.h"
#include "laser_lib/urg_headers/RangeSensorParameter.h"
#include "laser_lib/urg_headers/MathUtils.h"
#include "laser_lib/urg_headers/UrgCtrl.h"

using namespace qrk;

int main (int argc, char *argv[]) {

	std::stack<std::pair<int, int> > stk;
	int x = 0;
	int y = 0;
	Robot curr;
        LRFInterface *b = new LRFInterface(10);
	stk.push(std::make_pair(x, y));
	
        while (!stk.empty()) {
		x = stk.top().first;
		y = stk.top().second;
		curr.moveToPoint(x, y);

		switch (curr.getDirection()) {
			case NORTH: {
				if (b->isDirectionClear(LEFT) && !curr.isVisited(x, y - 1)) {
					stk.push(std::make_pair(x, y - 1));
					continue;
				}
				if (b->isDirectionClear(FRONT) == ' ' && !curr.isVisited(x - 1, y)) {
					stk.push(std::make_pair(x - 1, y));
					continue;
				}
				if (b->isDirectionClear(RIGHT) == ' ' && !curr.isVisited(x, y + 1)) {
					stk.push(std::make_pair(x, y + 1));
					continue;
				}
                                if (!curr.isVisited(x + 1, y)) {
                                        curr.turnAround();
                                        if (b->isDirectionClear(FRONT)) {
					    stk.push(std::make_pair(x + 1, y));
				    	    continue;
                                        }
				}
			} break;
			case SOUTH: {
				if (b->isDirectionClear(LEFT) && !curr.isVisited(x, y + 1)) {
					stk.push(std::make_pair(x, y + 1));
					continue;
				}
				if (b->isDirectionClear(FRONT) && !curr.isVisited(x + 1, y)) {
					stk.push(std::make_pair(x + 1, y));
					continue;
				}
				if (b->isDirectionClear(RIGHT) && !curr.isVisited(x, y - 1)) {
					stk.push(std::make_pair(x, y - 1));
					continue;
				}
                                if (!curr.isVisited(x - 1, y)) {
                                        curr.turnAround();
                                        if (b->isDirectionClear(FRONT)) {
					    stk.push(std::make_pair(x - 1, y));
				    	    continue;
                                        }
				}
			} break;
			case EAST: {
				if (b->isDirectionClear(RIGHT) && !curr.isVisited(x + 1, y)) {
					stk.push(std::make_pair(x + 1, y));
					continue;
				}
				if (b->isDirectionClear(FRONT) && !curr.isVisited(x, y + 1)) {
					stk.push(std::make_pair(x, y + 1));
					continue;
				}
				if (b->isDirectionClear(LEFT) && !curr.isVisited(x - 1, y)) {
					stk.push(std::make_pair(x - 1, y));
					continue;
				}
                                if (!curr.isVisited(x, y - 1)) {
                                        curr.turnAround();
                                        if (b->isDirectionClear(FRONT)) {
					    stk.push(std::make_pair(x, y - 1));
				    	    continue;
                                        }
				}
			} break;
			case WEST: {
				if (b->isDirectionClear(RIGHT) && !curr.isVisited(x - 1, y)) {
					stk.push(std::make_pair(x - 1, y));
					continue;
				}
				if (b->isDirectionClear(FRONT) && !curr.isVisited(x, y - 1)) {
					stk.push(std::make_pair(x, y - 1));
					continue;
				}
				if (b->isDirectionClear(LEFT) && !curr.isVisited(x + 1, y)) {
					stk.push(std::make_pair(x + 1, y));
					continue;
				}
                                if (!curr.isVisited(x, y + 1)) {
                                        curr.turnAround();
                                        if (b->isDirectionClear(FRONT)) {
					    stk.push(std::make_pair(x, y + 1));
				    	    continue;
                                        }
				}
			} break;
		}
		stk.pop();
	}

        delete b;
	curr.printVisited();
	std::cout << std::endl;
	curr.printBluePrint();

        return 0;
}
