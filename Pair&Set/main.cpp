#include <iostream>
#include <algorithm> // pair
#include <set>

using namespace std;

typedef pair<int, int> PII;
typedef set<PII> SPII;

void showPair(const PII& p);
void showSetPair(const SPII& sp);


int main()
{
	PII arr[100], p, temp;
	int sum1 = 0, sum2 = 0;
	SPII setPair;

	for (int i = 0; i < 100; i++)
	{
		arr[i].first = i;
		sum1 += arr[i].first;
		arr[i].second = arr[i].first * arr[i].first;
		sum2 += arr[i].second;
	}
	p.first = sum1;
	p.second = sum2;

	showPair(p);

	cout << "-----------------------------------------\n";

	for (int i = 0; i < 101; i++) //imput values from arr
	{
		temp.first = arr[i].first;
		temp.second = arr[i].second;
		setPair.insert(temp);
	}
	temp.first = p.first;
	temp.second = p.second; // input 101's value which holds sum
	setPair.insert(temp);

	for (auto it = setPair.begin(); it != setPair.end(); it++)
	{
		temp = *it;
		if (temp.first % 7 == 0 || temp.second % 7 == 0) // if any of pair's elements are divisble by 7, remove 
			it = setPair.erase(it);
	}
	showSetPair(setPair);

	return 0;
}
void showPair(const PII& p)
{
	cout << "(" << p.first << ", " << p.second << ")" << endl;
}
void showSetPair(const SPII& sp)
{
	for (auto it = sp.begin(); it != sp.end(); it++)
		showPair(*it);
}
