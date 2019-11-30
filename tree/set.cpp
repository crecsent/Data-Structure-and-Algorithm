#include"set.h"
#include<random>
#include<ctime>
#include<Windows.h>
#include<fstream>
//性能测试方法
//随机并：每次从当前所有根节点中随机取出两个。重复size次或当根节点只有一个时停止。
//随机查：将所有元素乱序逐个查找一遍。
int main()
{
	srand(time(0));
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);

	vector<int> roots, toFind;
	int r1, r2;
	double cost;

	const int sizes[] = { 100,200,500,1000,2000,5000,10000};

	ofstream file;
	file.open("d:/setTest.txt");

	for (int j = 0; j < 7; j++)
	{
		int size = sizes[j];
		cout << "size=" << size << endl;
		file << size << " ";

		Sets set1(size);
		roots = set1.getRoots();
		toFind = set1.getRoots();
		cost = 0.0;

		//simpleUnion
		for (int i = 0, rootSize = roots.size(); i < size&&rootSize>1; i++)
		{
			r1 = roots.at(rand() % rootSize);
			r2 = roots.at(rand() % rootSize);
			QueryPerformanceCounter(&t1);
			set1.simpleUnion(r1, r2);
			QueryPerformanceCounter(&t2);
			cost += (t2.QuadPart - t1.QuadPart)*1000000.0 / tc.QuadPart;
			roots = set1.getRoots();
			rootSize = roots.size();
		}
		cout << "simpleUnion averagely costs: " << (cost) / size << " μs" << endl;
		file << (cost) / size << " ";

		//simpleFind
		random_shuffle(toFind.begin(), toFind.end());
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++)
			set1.simpleFind(toFind.at(i));
		QueryPerformanceCounter(&t2);
		cost = (t2.QuadPart - t1.QuadPart)*1000000.0 / tc.QuadPart;
		cout << "simpleFind averagely costs: " << (cost) / size << " μs" << endl;
		file << (cost) / size << " ";

		//weightedUnion
		Sets set2(size);
		roots = set2.getRoots();
		toFind = set2.getRoots();
		cost = 0.0;
		for (int i = 0, rootSize = roots.size(); i < size&&rootSize>1; i++)
		{
			r1 = roots.at(rand() % rootSize);
			r2 = roots.at(rand() % rootSize);
			QueryPerformanceCounter(&t1);
			set2.weightedUnion(r1, r2);
			QueryPerformanceCounter(&t2);
			cost += (t2.QuadPart - t1.QuadPart)*1000000.0 / tc.QuadPart;
			roots = set2.getRoots();
			rootSize = roots.size();
		}
		cout << "weightedUnion averagely costs: " << (cost) / size<<" μs" << endl;
		file << (cost) / size << " ";

		//collapsingFind
		random_shuffle(toFind.begin(), toFind.end());
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++)
			set2.collapsingFind(toFind.at(i));
		QueryPerformanceCounter(&t2);
		cost = (t2.QuadPart - t1.QuadPart)*1000000.0 / tc.QuadPart;
		cout << "collapsingFind averagely costs: " << (cost) / size << " μs" << endl;
		file << (cost) / size << "\n";
	}
	system("pause");
}