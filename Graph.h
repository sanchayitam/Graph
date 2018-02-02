#pragma once
#include<iostream>
#include<vector>

using namespace std;

class Edge {
public:
	int v1;
	int v2;

	Edge(int v1, int v2) {
		this->v1 = v1;
		this->v2 = v2;
	}
};

template<typename Vertex>
class Graph
{
private:
	
	vector<Vertex> vertices; // Store vertices
	vector<vector<Edge*>> adjacentList; // Adjacency edge lists						
	
public:
	
	// Construct an empty graph 
	Graph();

	// Construct a graph from vertices in a vector and
	//  edges  
	Graph(vector<Vertex>& vertices, int edges[][2], int numberOfEdges);

	// Construct a graph with vertices 0, 1, ..., n-1 and
	// edges  
	Graph(int numberOfVertices, int edges[][2], int numberOfEdges);

	// Construct a graph from vertices and edges objects 
	Graph(vector<Vertex>& vertices, vector<Edge>& edges);

	// Construct a graph with vertices 0, 1, ..., n-1 and
	// edges in a vector 
	Graph(int numberOfVertices, vector<Edge>& edges);

	// Clear the graph
	void clear();

	// Adds a vertex to the graph
    bool addVertex(Vertex v);

	// Adds an edge from u to v to the graph
	bool addEdge(Vertex u, Vertex v);

	// Add an edge
	bool createEdge(Edge* e);

	// Create adjacency lists for each vertex from an edge array 
	void createAdjacencyLists(int numberOfVertices, int edges[][2], int numberOfEdges);

	// Create adjacency lists for each vertex from an Edge vector 
	void createAdjacencyLists(int numberOfVertices, vector<Edge>& edges);

	// Return the number of vertices in the graph 
	int getSize();

	// Return the degree for a specified vertex 
	int getDegree(Vertex v);

	// Return the neighbors of vertex 
	vector<Vertex> getNeighbors(Vertex v);

	// Return the vertex for the specified index 
	Vertex getVertex(int index);

	// Return the neighbors of vertex v 
	vector<Vertex> incidentVertices(Edge *edge);

	// Print the edges 
	void printEdges() ;

	// Print the adjacency matrix 
	void printAdjacencyMatrix();

};


