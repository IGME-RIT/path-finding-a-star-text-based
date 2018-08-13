/*
File Name : graph.h
Copyright © 2018
Original authors : Sanketh Bhat
Written under the supervision of David I.Schwartz, Ph.D., and
supported by a professional development seed grant from the B.Thomas
Golisano College of Computing & Information Sciences
(https ://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.

Description:
Graph data structure to showcase an A* implementation for pathfinding
*/


//https://www.geeksforgeeks.org/a-search-algorithm/
//http://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/
#ifndef GRAPH_H
#define GRAPH_H

#include <time.h>
#include <queue>
#include <functional>
#include <iostream>
#include <vector>
#include <string>

const int S = 25; //Length of a map side

const int dir = 8; //Number of possible directions we can move

//4 directions
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};

//8 directions
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

//Struct to hold a x and y value(like a 2d vector)
struct Position {

	int x;
	int y;

};

//Create an operator to check for equality
static bool operator==(const Position &A, const Position &B)
{
	return (A.x == B.x && B.y == A.y);
}

//struct for a basic unit in a grid based map
struct Unit {
	Position pos;
	std::string status = "";
	bool open = false;
	bool closed = false;
	float f=0; //total estimated cost (prioritry, lower=better)
	float g=0; //cost so far
	float h=0; //estimate cost from this unit to the end (main heuristic)

	void estimatePriority(int xf, int yf)
	{
		int xd, yd;
		
		xd = xf - pos.x;
		yd = yf - pos.y;

		h = sqrt(xd*xd + yd*yd);

		//h=abs(xd)+abs(yd);

		//d=max(abs(xd), abs(yd));

		f = g + h *10;
	}

	void updateCost(int d)
	{
		
		if (d % 2 == 0)
			g += 10;
		else
			g += 14;
	}
};

static bool operator<(const Unit &A, const Unit &B)
{
	return A.f > B.f; //Ensures that the 
}

class graph {
	
	std::priority_queue<Unit> openUnits; //We use a priority queue for the open list.
	std::vector<Unit> path;
	Unit map[S][S];
	Position start;
	Position end;
	int pMap[S][S];

	void initMap(int oCount);

	void printGraph();
	int randIndex();
	float calcDist(Position p1, Position p2);

public:
	
	
	void aStarPF();
	graph();
	
};


#endif GRAPH_H
