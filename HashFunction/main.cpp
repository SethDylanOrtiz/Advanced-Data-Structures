// CS 532, Seth Ortiz, HashTableClassExample, 5/12/2019
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

typedef pair<string, unsigned> ENTRY;
const unsigned MAXENTRIES = 257;

class Hash {
public:
	Hash(); // default constructor
	unsigned hash(const string & s);
	unsigned reHash(const string & s);
	bool add(const string & key, unsigned n);
	unsigned lookUp(const string & key);
	void show();
private:
	ENTRY table[MAXENTRIES]; // 257 elements of <string, unsigned>, mathematical infamous number
	unsigned used; // number of used keys
	unsigned limit;
}; // Hash class

string rString(); // random string generator
unsigned rU();    // random unsigned generator
bool die(const string & msg);

int main()
{
	Hash data;

	data.add("Durant", 35);
	data.add("Curry", 30);
	data.add("Irving", 11);
	data.add("James", 23);
	data.add("Bryant", 24);
	data.add("Westbrook", 1);

	while (data.add(rString(), rU())) continue;

	data.show();

	cout << "\nDurant: " << data.lookUp("Durant");
	cout << "\nCurry: " << data.lookUp("Curry");
	cout << "\nBryant: " << data.lookUp("Bryant");
	cout << "\nbogus: " << data.lookUp("bogus");
	return 0;
}

Hash::Hash()
{
	unsigned ret = 0;
	for (unsigned i = 0; i < MAXENTRIES; i++)
		table[i] = make_pair(string(), 0u); // make a pair of an empty string and an unsigned element of 0
	used = 0;   
	limit = 192; // 192 / 257 = 75% (our goal)
} // Hash default constructor

unsigned Hash::hash(const string & s)
{
	unsigned ret = 0;
	for (unsigned pos = 0; pos < s.size(); pos++)
		ret += (ret * 263 + unsigned char(s[pos])) % 257;

	return ret; // [0,256]
} // hash

unsigned Hash::reHash(const string & s)
{
	unsigned ret = 0;
	for (unsigned pos = s.size(); pos--;)
		ret = (ret * 241 + unsigned char(s[pos])) % 251;

	return ret + 1; // [1,251]
} // reHash

bool Hash::add(const string & key, unsigned n)
{
	if (used >= limit) // if we already surpassed 75% capacity
		return false;

	unsigned h = hash(key);
	unsigned r = reHash(key);

	while (h >= MAXENTRIES || !table[h].first.empty()) // while were not in range OR havent found empty slot in array
		h = (h + r) % 257;

	table[h].first = key;
	table[h].second = n;
	used++;	
	return true; // success, something was added
} // add

unsigned Hash::lookUp(const string & key)
{
	unsigned h = hash(key);
	unsigned r = reHash(key);

	while (h >= MAXENTRIES || table[h].first != key) // while were not in range OR havent found key value in array
	{
		h = (h + r) % 257;						// jump through array to find desired pos
		if (table[h].first.empty())				// if empty spot is found, desired entry does not exist
			return 0u;							// return 0 if not found
	}
	
	return table[h].second;	// return corresponding unsigned value
} // lookUp

void Hash::show()
{
	cout << "Pos: " << left << setw(15) << "Name" << "Value\n";
	for (unsigned i = 0; i < MAXENTRIES; i++)
		cout << right << setw(3) << i << ": " << left << setw(15) << table[i].first << " " << table[i].second << endl;	
}

string rString()
{
	string ret;
	for (unsigned i = 6 + rand() % 6; i--;)
		ret += char('a' + rand() % 26);
	return ret;
} // rString

unsigned rU()
{
	return rand() + (rand() << 15) + (rand() << 30);
} // rU

bool die(const string & msg)
{
	cout << "Fatal error: " << msg << endl;
	exit(EXIT_FAILURE);
} // die