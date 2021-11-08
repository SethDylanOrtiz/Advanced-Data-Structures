 // CS 532, Seth Ortiz, Hw13 - Enumerate nodes & distances with BFS and DFS, 5/3/2019
#include <algorithm> // pair
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

typedef int Vertex;
typedef set<Vertex> VertexSet;			// vertex -> int, dot on graph
typedef set<Vertex> Edge;			    // size 2, edge -> (vertexOne,vertexTwo)
typedef set<Edge> EdgeSet;
typedef pair<VertexSet, EdgeSet> Graph;
typedef map<Vertex, VertexSet> Graph2;  // Vertex = vertices, VertexSet = adjacents

Graph2 graph2FromGraph(const Graph& g);

void DFS(const Graph2& g2, Vertex start);
void dfsUtil(const Graph2& g2, Vertex pos, vector<bool>& discovered);
void BFS(const Graph2& g2, Vertex start);

int main()
{
	Graph g{ { 1,2,3,4,5,6,7,8,9 },
	{ { 3,2 },{ 3,1 },{ 3,5 },{ 1,4 },{ 1,6 },{ 1,5 },{ 2,4 },{ 5,6 },{ 7,8 },{ 7,9 } } };
	Graph2 g2 = graph2FromGraph(g);
	cout << "BFS \n";
	BFS(g2, 3);
	cout << "DFS \n";
	DFS(g2, 3);

	cout << "----------------\n\n";

	Graph web{ { 1,2,3,4,5,6,7,8,9,10,11,12 },
	{ { 1, 2 },{ 1, 3 },{ 1, 4 },{ 2, 5 },{ 2, 6 },{ 5, 9 },{ 5, 10 },{ 4, 7 },{ 4, 8 },{ 7, 11 },{ 7, 12 } } };
	Graph2 webTest = graph2FromGraph(web);
	cout << "BFS \n";
	BFS(webTest, 1);
	cout << "DFS \n";
	DFS(webTest, 1);

	cout << "----------------\n\n";

	Graph crazy{ { 0,1,2,3,4,5,6,7,8 },
	{ { 0,1 },{ 0,3 },{ 0,4 },{ 1,2 },{ 1,4 },{ 2,5 },{ 3,4 },{ 3,6 },{ 4,5 },{ 4,6 },{ 4,7 },{ 5,7 },{ 6,7 },{ 7,8 } } };
	Graph2 crazyGraph = graph2FromGraph(crazy);
	cout << "BFS \n";
	BFS(crazyGraph, 0);

	return 0;
}

Graph2 graph2FromGraph(const Graph& g)
{
	Graph2 ret;
	for (const Vertex& v : g.first)
		ret.insert(make_pair(v, VertexSet()));
	for (const Edge& e : g.second)
	{
		vector<Vertex> vv;
		for (const Vertex& v : e)
			vv.push_back(v);
		ret[vv[0]].insert(vv[1]);
		ret[vv[1]].insert(vv[0]);
	}
	return ret;
} // graph2FromGraph

void BFS(const Graph2& g2, Vertex start)
{
	int N = g2.size() + 1;	    // number of nodes in tree
	vector<bool> discovered(N); // initially all set to false
	vector<int> distances(N);   // holding distances for each value 
	queue<Vertex> q;

	for (int i = 0; i < N; i++) // set each distance to -1
		distances[i] = -1;

	discovered[start] = true;   // set 'start' discovery to true
	distances[start] = 0;       // set initial distance , start to start, to 0
	q.push(start);
	cout << " " << start << ": " << distances[start] << endl;

	while (!q.empty())
	{
		for (int u : g2.at(q.front())) // go to adj
		{
			if (!discovered[u])
			{
				discovered[u] = true;
				distances[u] = distances[q.front()] + 1; // set distance of vertex[u] to front of q's distance + 1
				q.push(u);
				cout << " " << u << ": " << distances[u] << endl; // print vertex and distance
			}
		}
		q.pop();
	}
	cout << endl;
} // BFS

void dfsUtil(const Graph2& g2, Vertex pos, vector<bool>& discovered)
{
	discovered[pos] = true; // mark current neighbor node as discovered
	cout << " " << pos << endl; // print current node

	for (int u : g2.at(pos))
		if (!discovered[u])	 // if u isn't discovered / discovered == false
			dfsUtil(g2, u, discovered);	// recursively call again
}
void DFS(const Graph2& g2, Vertex start)
{
	int N = g2.size() + 1; // number of nodes in tree
	vector<bool> discovered(N); // initially all set to false

	dfsUtil(g2, start, discovered);
	cout << endl;
}// DFS
