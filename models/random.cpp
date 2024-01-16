#include<bits/stdc++.h>
using namespace std;
int main()
{
	const int N = 1000000;
	int* parr = new int[N];
	int* pm = parr;
	for (int i = 0; i < 10; i++)
	{
		*pm = rand() % 100;
		pm++;
	}
	for (int i = 0; i < 20; i++)
	{
		cout << *(parr + 1) << endl;
	}
	delete[]parr;
	return 0;
}