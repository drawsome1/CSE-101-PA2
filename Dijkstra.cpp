// CSE 101 Winter 2018, PA 2
//
// Name: Richard Chum
// PID: A11564681
// Sources of Help:
// Due: February 9th, 2018 at 11:59 PM

#ifndef __DIJKSTRA_CPP__
#define __DIJKSTRA_CPP__

#include "Graph.hpp"
// include more libraries as needed
#include <queue>
#include <vector>
#include <iomanip>

template <class T>
class mycomparison
{
	public:
		//least to greatest
		bool operator() ( std::pair< T, float> & lhs, std::pair< T, float> & rhs)
		{
			//need to get the weights 
			if(lhs.second < rhs.second)
			{
				return false;
			}
			else if( lhs.second == rhs.second)
			{
				if(lhs.first < rhs.first)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
};

template <class T>
float dijkstra(Graph<T>&g, T src) {
	//priority queue of all the elements listed in order from smallest distance
	std::priority_queue< std::pair< T, float>, std::vector< std::pair< T, float>
		>, mycomparison<T> > pq;

	//setting start's distance to be 0
	g.vertices[src]->distance = 0;
	g.vertices[src]->visited = true;

	//putting all of it's neighbors into the pq
	for( auto edgeIt = g.vertices[src]->edges.begin(); edgeIt !=
				g.vertices[src]->edges.end(); edgeIt++)
	{
			//since this is the neighbors of the src it's current shortestest
			//distance is the weight 
			g.vertices[*edgeIt]->distance = g.get_weight(src,*edgeIt);
			g.vertices[*edgeIt]->prev = src;

			//inserting the neighbor into the pq
			pq.push(std::make_pair(*edgeIt,g.get_weight(src,*edgeIt)));
	}

	//get all the weights of it's neighbors and put into pq
	while(!pq.empty())
	{
		//getting the smallest weighted vertex
		auto current = pq.top();
		g.vertices[current.first]->visited = true;
		pq.pop();

		for( auto edgeIt = g.vertices[current.first]->edges.begin(); edgeIt !=
				g.vertices[current.first]->edges.end(); edgeIt++)
		{
			if( g.vertices[*edgeIt]->visited == true)
			{
				continue;
			}
			if( g.vertices[*edgeIt]->distance > g.vertices[src]->distance +
					g.get_weight(src,*edgeIt))
			{
				g.vertices[*edgeIt]->distance = g.vertices[src]->distance +
					g.get_weight(src,*edgeIt);
				g.vertices[*edgeIt]->prev = current.first;
			}
			pq.push(std::make_pair(*edgeIt,g.get_weight(current.first,*edgeIt)));
		}
	}

	//while the queue isn't empty
	//get the smallest element
	//for all of it's edges
	float sumDist = 0.0;

	for(auto mapIt = g.vertices.begin(); mapIt != g.vertices.end(); mapIt++)
	{
		sumDist += (*mapIt).second->distance;

	}
	
	
	
	
  return sumDist;
}

#endif
