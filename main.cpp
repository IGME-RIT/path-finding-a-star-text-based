
#include "graph.h"


void main()
{
	graph *g = new graph();
	
	g->aStarPF();
	std::cin.get();
	std::cin.get();
	
	delete g;
	
	return;
}