// Graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph.h"
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
using namespace std;

template<typename Vertex>
Graph<Vertex>::Graph()
{
}

template<typename Vertex>
Graph<Vertex>::Graph(vector<Vertex>& vertices, int edges[][2], int numberOfEdges)
{
		for (unsigned i = 0; i < vertices.size(); i++)
			addVertex(vertices[i]);

		createAdjacencyLists(vertices.size(), edges, numberOfEdges);
}

template<typename Vertex>
Graph<Vertex>::Graph(int numberOfVertices, int edges[][2], int numberOfEdges)
{
		for (int i = 0; i < numberOfVertices; i++)
			addVertex(i); // vertices is {0, 1, 2, ..., n-1}

		createAdjacencyLists(numberOfVertices, edges, numberOfEdges);
}

template<typename Vertex>
Graph<Vertex>::Graph(vector<Vertex>& vertices, vector<Edge>& edges)
{
	for (unsigned i = 0; i < vertices.size(); i++)
		addVertex(vertices[i]);

	createAdjacencyLists(vertices.size(), edges);
}

template<typename Vertex>
Graph<Vertex>::Graph(int numberOfVertices, vector<Edge>& edges)
{
	for (int i = 0; i < numberOfVertices; i++)
		addVertex(i); // vertices is {0, 1, 2, ..., n-1}

	createAdjacencyLists(numberOfVertices, edges);
}

template<typename Vertex>
void Graph<Vertex>::clear()
{
	vertices.clear();
	for (int i = 0; i < getSize(); i++)
		for (Edge* e : adjacentList[i])
			delete e;
	adjacentList.clear();
}

template<typename Vertex>
bool Graph<Vertex>::addVertex(Vertex v)
{
	if (find(vertices.begin(), vertices.end(), v) == vertices.end())
	{
		vertices.push_back(v);
		adjacentList.push_back(vector<Edge*>(0));
		return true;
	}
	else
	{
		return false;
	}
}

template<typename Vertex>
bool Graph<Vertex>::addEdge(Vertex u, Vertex v)
{
	return createEdge(new Edge(u, v));
}

template<typename Vertex>
bool Graph<Vertex>::createEdge(Edge* e)
{
	if (e->v1 < 0 || e->v1> getSize() - 1)
	{
		stringstream ss;
		ss << e->v1;
		throw invalid_argument("No such edge: " + ss.str());
	}

	if (e->v2 < 0 || e->v2 > getSize() - 1)
	{
		stringstream ss;
		ss << e->v2;
		throw invalid_argument("No such edge: " + ss.str());
	}

	vector<Vertex> listOfNeighbors = getNeighbors(e->v1);
	if (find(listOfNeighbors.begin(), listOfNeighbors.end(), e->v2) == listOfNeighbors.end())
	{
		adjacentList[e->v1].push_back(e);
		return true;
	}
	else
	{
		cout << "Edge between " << e->v1 << " & " << e->v2 << "already present, cannot be added\n";
		return false;
	}
}

template<typename Vertex>
void Graph<Vertex>::createAdjacencyLists(int numberOfVertices, int edges[][2], int numberOfEdges)
{
	for (int i = 0; i < numberOfEdges; i++)
	{
		int u = edges[i][0];
		int v = edges[i][1];
		addEdge(u, v);
	}
}

template<typename Vertex>
void Graph<Vertex>::createAdjacencyLists(int numberOfVertices, vector<Edge>& edges)
{
	for (unsigned i = 0; i < edges.size(); i++)
	{
		int u = edges[i].u;
		int v = edges[i].v;
		addEdge(u, v);
	}

}

template<typename Vertex>
int Graph<Vertex>::getSize() 
{
	return vertices.size();
}

template<typename Vertex>
int Graph<Vertex>::getDegree(Vertex v) 
{
	return adjacentList[v].size();
	
}

template<typename Vertex>
Vertex Graph<Vertex>::getVertex(int index) 
{
	return vertices[index];
}

template<typename Vertex>
vector<Vertex> Graph<Vertex>::getNeighbors(Vertex u) 
{
	vector<Vertex> result;
	for (Edge* e : adjacentList[u])
	{
		result.push_back(e->v2);
	}
	return result;
}

template<typename Vertex>
vector<Vertex> Graph<Vertex>::incidentVertices(Edge * edge) 
{
	vector<Vertex> result;
			
	for (Edge* e : adjacentList[edge->v1])
	{
		if (find(result.begin(), result.end(), edge->v2) == result.end()) {
			result.push_back(e->v2);
		}
	}

		for (Edge* e : adjacentList[edge->v2])
	{
		if (find(result.begin(), result.end(), edge->v2) == result.end()) {
			result.push_back(e->v2);
		}
	}
	return result;

}

template<typename Vertex>
void Graph<Vertex>::printAdjacencyMatrix() 
{
	// Use vector for 2-D array
	vector<vector<Vertex>> adjacencyMatrix(getSize());

	// Initialize 2-D array for adjacency matrix
	for (int i = 0; i < getSize(); i++)
	{
		adjacencyMatrix[i] = vector<int>(getSize());
	}

	for (unsigned i = 0; i < adjacentList.size(); i++)
	{
		for (Edge* e : adjacentList[i])
		{
			adjacencyMatrix[i][e->v2] = 1;
		}
	}

	for (unsigned i = 0; i < adjacencyMatrix.size(); i++)
	{
		for (unsigned j = 0; j < adjacencyMatrix[i].size(); j++)
		{
			cout << adjacencyMatrix[i][j] << " ";
		}

		cout << endl;
	}
}

template<typename Vertex>
void Graph<Vertex>::printEdges()
{
	for (unsigned u = 0; u < adjacentList.size(); u++)
	{
		cout << "Vertex " << getVertex(u) << "(" << u << "): ";
		for (Edge* e : adjacentList[u])
		{
			cout << "(" << getVertex(e->v1) << ", " << getVertex(e->v2) << ") ";
		}
		cout << endl;
	}
}



	
int main()
{
	Graph<int> g;
	g.addVertex(0);
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(0, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 3);
	g.printEdges();
	int v;
	cout << "Enter the vertex \n";
	cin >> v;
	vector<int> result = g.getNeighbors(v);
	std::vector<int>::iterator it;
	cout << "Neighbors of vertex  " << v << " are ";
	for (it = result.begin(); it != result.end(); it++)
	{
		 cout <<*it<<" ";
	}
	cout << endl;
	Edge edg(2, 3);
	
	vector<int> result1 = g.incidentVertices(&edg);
	std::vector<int>::iterator it1;
	cout << "Incidence of Edge  " << edg.v1 << " & " << edg.v2 << " are ";
	for (it1 = result1.begin(); it1 != result1.end(); it1++)
	{
		cout << *it1 <<" ";
	}
	cout << endl;
	cout << "Degree of vertex " <<edg.v1 <<" " << g.getDegree(edg.v1)<<endl;
	cout << "Degree of vertex " <<edg.v2 <<" "<< g.getDegree(edg.v2);
	g.printAdjacencyMatrix();

	return 0;
}



