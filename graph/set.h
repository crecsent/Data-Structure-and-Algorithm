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

	void weightedUnion(int i, int j)
	{
		i = collapsingFind(i);
		j = collapsingFind(j);
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

	int getSetNumber() const
	{
		int num = 0;
		for (int i = 0; i < n; i++)
		{
			if (parent[i] < 0)
				num += 1;
		}
		return num;
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