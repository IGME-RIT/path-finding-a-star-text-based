/*
File Name : graph.cpp
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
C++ demonstration of the A* pathfinding algorithm
*/
#include "graph.h"


#pragma region Graph Generation


//Method to initalize the graph data
void graph::initMap(int oCount)
{
	//Seeding our random number generator
	srand(time(NULL));

	//Initializing node values 
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < S; j++)
		{
			map[i][j].pos.x = i;
			map[i][j].pos.y = j;
			map[i][j].status = ".";
			

			pMap[i][j] = 0;
		}

	}

	//Randomnly generating obstacles

	for (int i = 0; i < oCount; i++)
	{
		map[randIndex()][randIndex()].status = "O";
	}

	//Randomly generating start and end points

	do {
		start.x = randIndex();
		start.y = randIndex();
		end.x = randIndex();
		end.y = randIndex();
	} 
	while (calcDist(start, end) < S*1.2f);

	map[start.x][ start.y].status = "S";
	map[end.x][ end.y].status = "F";
}

//A* algorithm
 void graph::aStarPF()
 {
	 std::priority_queue<Unit> temp;
	 int i,x,y;
	 Unit u;
	 Unit n;
	 map[start.x][start.y].estimatePriority(end.x,end.y);
	 pMap[start.x][start.y] = map[start.x][start.y].f;

	 openUnits.push(map[start.x][start.y]);
	 

	 //Loop while the list of unprocessed nodes is not empty
	 while (!openUnits.empty())
	 {
		 u = openUnits.top();
		 
		 openUnits.pop();
		 map[u.pos.x][u.pos.y].closed = true; //Processing this node so we can close it
		 path.push_back(u);

		 if (u.status == "F")
		 {
			 //We are at the end point so we can clear the open list and end the algorithm.
			 while (!openUnits.empty()) 
				 openUnits.pop();
		 }
		 else
		 {
			 //Change status of the popped unit unless its the start
			 if(u.status!="S")
				map[u.pos.x][u.pos.y].status = "P";

			 //Checks each node next to the current node
			 for (i= 0; i < dir; i++)
			 {
				 x = u.pos.x + dx[i];
				 y = u.pos.y + dy[i];

				 if(!(x<0 || x>S-1 || y<0 || y>S-1 || //Unit is in the map?
					 map[x][y].closed==true||	      //Closed?
					 map[x][y].status=="O"))		  //Obstacle?
				 {
					 //Adds it to the map we process
					 n = map[x][y];
					 n.updateCost(i);
					 n.estimatePriority(end.x, end.y); //Gets the priority value for the node

					 if (n.open==false)
					 {
						 //Adds it to the list on unprocessed nodes
						 n.open = true;
						 pMap[x][y] = n.f;
						 openUnits.push(n);
					 }
					 else if(pMap[x][y]>n.f)
					 {
						 pMap[x][y] = n.f;

						 openUnits.swap(temp);
						 while (!temp.empty())
						 {
							 if (temp.top().pos == n.pos)
							 {
								 openUnits.push(n);
								 temp.pop();
							 }
							 else
							 {
								 openUnits.push(temp.top());
								 temp.pop();
							 }
						 }
					 }
				 }
			 }
		 }
	 }
	 printGraph();
 }

//Constructor
graph::graph()
{
	initMap(S*2);
}
#pragma region Helper Methods

int graph::randIndex()
{
	return rand() % S;
}


float graph::calcDist(Position p1, Position p2)
{
	int xd = p2.x - p1.x;
	int yd = p2.y - p1.y;

	return sqrt(xd*xd + yd * yd);
}

//Print graph out
void graph::printGraph()
{
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < S; j++)
		{
			std::cout << map[i][j].status << " ";
		}
		std::cout << "\n";
	}
}
#pragma endregion



