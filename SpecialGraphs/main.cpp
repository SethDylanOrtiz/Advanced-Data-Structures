// CS 532, Seth Ortiz, Special Graphs Example, 5/18/2019
/* a Graph g is an ordered pair (V, E)
V is a set of verticesa vertex is an int
E is a set of edgesan edge is a set of 2 different verticesa Graph2 g2 is a set of ordered pairs: (Vertex, VertexSet)
each vertex of the graph appears as the first element of anordered pairs
The vertexSet corresponding to a vertex is the set of vertices
adjacent to that vertex.*/
#include <algorithm> // pair
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef int Vertex;
typedef set<Vertex> VertexSet;
typedef set<Vertex> Edge; // size 2
typedef set<Edge> EdgeSet;
typedef pair<VertexSet, EdgeSet> Graph;
typedef map<Vertex, VertexSet> Graph2;	// map = <"key", value>

vector<Vertex> vectorFromSet(const VertexSet& vs)
{
	vector<Vertex> ret;
	for (const Vertex& v : vs)ret.push_back(v);
	return ret;
}
ostream& operator<<(ostream& out, const Edge& e)
{
	vector<Vertex> v = vectorFromSet(e);
	return out << "(" << v[0] << ", " << v[1] << ")";
}
Graph2 graph2FromGraph(Graph& g);
void show(const Graph2& g2);

Graph2 createComplete(unsigned n);
bool isComplete(Graph2& g2);
Graph2 createCycle(unsigned n);
bool isCycle(Graph2& g2);
Graph2 createWheel(unsigned n);
bool isWheel(Graph2& g2);
Graph2 createBipartite(unsigned m, unsigned n);
// isBipartite wont be asked on final, 2019

int main()
{
	Graph2 g2;

	cout << "Complete Graph \n";
	g2 = createComplete(5);
	show(g2);
	isComplete(g2) ? cout << "Complete graph. \n\n" : cout << "Not a complete graph. \n\n";

	cout << "Cycle Graph \n";
	g2 = createCycle(4);
	show(g2);
	isCycle(g2) ? cout << "Complete Cycle. \n\n" : cout << "Not a complete Cycle. \n\n";

	// Graph2 falseg2{ {1,{2,4,5}},{ 2,{1,3,5}},{ 3,{2,4,5}},{ 4,{1,3,5}}, {5, {1,2,3,4}} };
	cout << "Wheel Graph \n";
	g2 = createWheel(5);
	show(g2);
	isWheel(g2) ? cout << "Complete Wheel. \n\n" : cout << "Not a complete Wheel. \n\n";

	cout << "Bipartite Graph \n";
	g2 = createBipartite(2, 3);
	show(g2);

	return 0;
} // main

Graph2 graph2FromGraph(Graph& g)
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
}

void show(const Graph2& g2)
{
	for (auto it = g2.begin(); it != g2.end(); it++)
	{
		cout << "(" << it->first << ", {";
		for (auto it2 = it->second.begin();
			it2 != it->second.end(); it2++)
		{
			if (it2 != it->second.begin())cout << ", ";
			cout << *it2;
		}cout << "})\n";
	}
}

Graph2 createComplete(unsigned n)
{
	Graph2 g2;
	for (Vertex v1 = 0; v1 < n; v1++)
		for (Vertex v2 = 0; v2 < n; v2++)
		{
			if (v2 != v1)
				g2[v1].insert(v2);
		}
	return g2;
}
bool isComplete(Graph2& g2)
{
	for (auto v : g2)
	{
		if (v.second.size() != g2.size() - 1) return false;
		auto itr = v.second.begin();				 // goes through adjacents

		for (Vertex adj = 0; adj < g2.size(); adj++) // adj  is used for comparison
			if (v.first != adj)
			{
				if (*itr != adj)					// check if adjacent exists
					return false;
				itr++;
			}
	}
	return true;
} // end complete

Graph2 createCycle(unsigned n)
{
	Graph2 g2;
	for (Vertex v = 0; v < n; v++)
	{
		if (v == 0)			// first vertex special case
		{
			g2[v].insert(1);
			g2[v].insert(n - 1);
		}
		else
			if (v == n - 1) // last vertex special case
			{
				g2[v].insert(0);
				g2[v].insert(v - 1);
			}
			else
			{
				g2[v].insert(v - 1);
				g2[v].insert(v + 1);
			}
	}
	return g2;
}
bool isCycle(Graph2& g2)
{
	//  Professor Hart's algorithm
	for (auto p : g2)
		if (p.second.size() != 2) return false;
	unsigned steps = 1;

	for (Vertex v0 = g2.begin()->first, v1 = v0, v2 = *g2.at(v0).begin(); v2 != v0; steps++)
	{
		auto it = g2.at(v2).begin();
		if (*it == v1)
			it++;

		Vertex v3 = *it;
		v1 = v2;
		v2 = v3;
	}
	return steps == g2.size();
} // end cycle

Graph2 createWheel(unsigned n)
{
	Graph2 g2 = createCycle(n);
	for (Vertex v = 0; v < n; v++) // insert extra vertex
		g2[v].insert(n);
	for (Vertex v = 0; v < n; v++) // assign extra vertex to all others
		g2[n].insert(v);

	return g2;
}
bool isWheel(Graph2& g2)
{
	//when n == 5, g2.size == 6;
	map <int, int> occurances;
	int oneTimeSize = 0; // only one element, one element should have size() - 1 vertices

	for (auto v : g2)
	{
		auto itr = v.second.begin();

		for (Vertex v1 = 0; v1 < v.second.size(); v1++)
		{
			if (*itr > g2.size()) return false;

			occurances[*itr]++;
			itr++;
		}
	}
	for (Vertex v = 1; v <= g2.size(); v++)
	{
		if (occurances[v] == g2.size() - 1)
			oneTimeSize++;
		else
			if (occurances[v] != 3)	return false;
	}
	return oneTimeSize == 1;
} // end wheel

Graph2 createBipartite(unsigned m, unsigned n)
{
	Graph2 g2;
	for (Vertex v1 = 1; v1 <= m; v1++)
	{
		for (Vertex v2 = n; v2 <= m + n; v2++)
		{
			if (v2 != v1)
				g2[v1].insert(v2);
		}
	}
	return g2;
} //end bipartite
