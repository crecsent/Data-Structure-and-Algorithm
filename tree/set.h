#include<iostream>
#include<vector>
using namespace std;
class Sets {
public:
	Sets(int size)
	{
		if (size < 2)
			throw "Must have at least 2 elements.";
		n = size;
		parent = new int[n];
		fill(parent, parent + n, -1);
	}
	void simpleUnion(int i, int j)
	{
		if(i!=j)
			parent[i] = j;
	}
	int simpleFind(int i)
	{
		while (parent[i] >= 0) i = parent[i];
		return i;
	}
	void weightedUnion(int i, int j)
	{
		if (i != j)
		{
			int temp = parent[i] + parent[j];
			if (parent[i] > parent[j])
			{
				parent[i] = j; parent[j] = temp;
			}
			else
			{
				parent[j] = i; parent[i] = temp;
			}
		}
	}

	int collapsingFind(int i)
	{
		int r = i;
		for (; parent[r] >= 0; r = parent[r]);
		while (i != r)
		{
			int s = parent[i];
			parent[i] = r;
			i = s;
		}
		return r;
	}

	vector<int> getRoots()
	{
		vector<int> rootsIndex;
		for (int i = 0; i < n; i++)
		{
			if (parent[i] < 0)
				rootsIndex.push_back(i);
		}
		return rootsIndex;
	}
private:
	void fill(int *begin, int* end, int value)
	{
		for (; begin != end; begin++)
			*begin = -1;
	}
	int * parent;
	int n;
};