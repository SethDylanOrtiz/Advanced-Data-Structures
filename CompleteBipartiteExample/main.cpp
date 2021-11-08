#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <vector>

using namespace std;

typedef vector<int> vi; // vector of all neighbors
typedef queue<int> qi;  // queue of vertices

void show(const vi& v);
void show(const set<int>& s);
void show(const map<int, vi>& m);
unsigned edges(const map<int, vi>& m);

int main()
{
	map<int, vi> m = { {1, {2,4,6}},
						{2, {1,3,5}},
						{3, {2,4,6}},
						{4, {1,3,5}},
						{5, {2,4,6}},
						{6, {1,3,5}} };
	show(m);
	unsigned e = edges(m);

	if (e == 0) // trivial case w/ zero edges
	{
		cout << "yeah\n";
		return 0;
	}
	set<int> b, w; // b = set of "black" vertices, w = set of "white" vertices
	qi q;		   // q = queue of vertices

	int start = m.begin()->first; // set first index from graph "m"
	b.insert(start);			  // mark start as "black"
	q.push(start);				  // push start vertex onto queue
	cout << endl << " mark and push: " << start << endl;

	while (!q.empty()) // breadth first search while queue is NOT empty
	{
		int v = q.front();
		q.pop();
		bool vBlack = b.find(v) != b.end(); // if v is "black", then set vBlack = true
		vi* p = &m[v];					    //pointer to vector of neighboring vertices
		cout << " visit Vertex: " << v << " with neighbors:";
		show(*p);
		for (auto it = p->begin(); it != p->end(); it++)
		{
			if (b.find(*it) == b.end() && w.find(*it) == w.end()) // .find() returns end if not found
			{	// it is neither black nor white, so it is unmarked
				int n = *it; // n is a new unmarked neighbor
				if (vBlack)
					w.insert(n);
				else
					b.insert(n);
				q.push(n);
				cout << " mark and push: " << n << endl;
			}
		}
	}
	unsigned bp = b.size();
	unsigned wp = w.size();
	cout << " black[" << bp << "]:";
	show(b);
	cout << " white[" << wp << "]:";
	show(w);
	cout << " number of edges: " << e << endl;
	if (bp + wp == m.size() && e == bp * wp)
		cout << " yeah\n";
	else
		cout << " nope\n";
	return 0;
}

void show(const vi& v)
{
	for (unsigned i = 0; i < v.size(); i++)
		cout << " " << v[i];
	cout << endl;
}
void show(const set<int>& s)
{
	for (auto it = s.begin(); it != s.end(); it++)
		cout << " " << *it;
	cout << endl;
}
void show(const map<int, vi>& m)
{
	for (auto it = m.begin(); it != m.end(); it++)
	{
		cout << " ( " << it->first << ", {";
		vi vctr = it->second;
		for (unsigned i = 0; i < vctr.size(); i++)
			cout << " " << vctr[i];
		cout << " } )" << endl;
	}
}
unsigned edges(const map<int, vi>& m)
{
	unsigned total = 0;
	for (auto p : m)
		total += p.second.size();
	return total / 2;
}
