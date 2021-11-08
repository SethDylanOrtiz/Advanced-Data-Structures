// CS 532, Seth Ortiz, HashTableChainingExample, 5/16/2019
#include "Node.h"
#include "LinkedList.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

typedef pair<string, unsigned> ENTRY;

class Hash {
public:
	Hash(); // default constructor
	unsigned hash(const string& key);
	unsigned reHash(const string& key);
	bool add(const string& key, unsigned n);
	unsigned lookUp(const string& key);
	void show() const;
private:
	LinkedList table[MAXENTRIES]; // 257 elements of <string, unsigned>, mathematical infamous number
	unsigned used; // number of used keys
	unsigned limit;

}; // Hash class

string rString(); // random string generator
unsigned rU();    // random unsigned generator

int main()
{
	Hash record;

	record.add("Lonzo", 2);
	record.add("Hart", 5);
	record.add("James", 23);

	while (record.add(rString(), rU())) continue;
	record.show();

	string desiredUser = "";
	cout << "Enter Name to lookUp(): \n";
	while (getline(cin, desiredUser) && desiredUser != "")
	{
		unsigned found = record.lookUp(desiredUser);
		cout << (found == UINT_MAX ? "User does not exist" : desiredUser + ": " + to_string(found)) << endl;
	}

	return 0;
}

Hash::Hash()
{
	used = 0;
	limit = 192; // 192 / 257 = 75% (our goal)
} // end hash default ctor

unsigned Hash::hash(const string& key)
{
	unsigned ret = 0;
	for (unsigned pos = 0; pos < key.size(); pos++)
		ret += (ret * 263 + unsigned char(key[pos])) % 257;

	if (ret > limit)  ret = reHash(key);

	return ret; // [0,256]
} // end hash ctor

unsigned Hash::reHash(const string& key)
{
	unsigned ret = 0;
	for (unsigned pos = key.size(); pos--;)
		ret = (ret * 241 + unsigned char(key[pos])) % 251;

	return ret + 1; // [1,251]
} // end reHash

bool Hash::add(const string& key, unsigned n)
{
	if (used >= limit)  return false;

	unsigned h = hash(key);

	if (h > limit) 	h = reHash(key);

	table[h].insert(make_pair(key, n));
	used++;

	return true;
} // end add

unsigned Hash::lookUp(const string& key)
{
	unsigned h = hash(key);			// find "index" in array

	if (h > limit)
		h = reHash(key);

	return table[h].findNode(key);
} // end lookUp

string rString()
{
	string ret;
	for (unsigned i = 6 + rand() % 6; i--;)
		ret += char('a' + rand() % 26);
	return ret;
} // end rString

unsigned rU()
{
	return rand() + (rand() << 15) + (rand() << 30);
} // rU

void Hash::show() const
{
	cout << "Pos: " << left << setw(12) << "Name" << "Value\n";
	for (unsigned i = 0; i < MAXENTRIES; i++)
	{
		cout << right << setw(3) << i << ": " << left << setw(12);
		table[i].showList();
		cout << endl;
	}
} // end show
