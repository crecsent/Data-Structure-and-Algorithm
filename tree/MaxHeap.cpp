#include<ctime>
#include<Windows.h>
#include<fstream>
#include<iostream>
#pragma comment(lib, "winmm.lib ")
using namespace std;


template<class T>
class MaxPQ {
public:
	virtual ~MaxPQ() {}
	virtual bool isEmpty() const = 0;
	virtual const T& top() const = 0;
	virtual void push(const T&) = 0;
	virtual void pop() = 0;
};

template<class T>
class MaxHeap :public MaxPQ<T> {
public:
	MaxHeap(int capa = 10)
	{
		if (capa < 1)
			throw "Capacity must be >= 1.";
		capacity = capa;
		heapSize = 0;
		heap = new T[capacity + 1];//heap[0]不用

	}
	bool isEmpty() const
	{
		return heapSize == 0;
	}
	const T& top() const
	{
		return heap[1];
	}
	void push(const T & x)
	{
		if (heapSize == capacity)
			doubleSize();
		heap[++heapSize] = x;
		int parentIndex = heapSize / 2;
		int currentIndex = heapSize;
		while (parentIndex != 0 && heap[parentIndex] < x)
		{
			heap[currentIndex] = heap[parentIndex];
			currentIndex = parentIndex;
			parentIndex /= 2;
		}
		heap[currentIndex] = x;
	}

	void pushByBinarySearch(const T & x)
	{

		if (heapSize == capacity)
			doubleSize();
		heap[++heapSize] = x;
		int toReplace = binarySearch(1, heapSize, heapSize);//用折半查找法找到该新增节点应该放置的位置

		int parentIndex = heapSize / 2;
		int currentIndex = heapSize;
		while (currentIndex != toReplace)
		{
			heap[currentIndex] = heap[parentIndex];
			currentIndex = parentIndex;
			parentIndex /= 2;
		}
		heap[currentIndex] = x;
	}

	void traverse() {
		for (int i = 1; i <= heapSize; i++)
			cout << heap[i] << " ";
	}

	void pop()
	{
		if (isEmpty())
		{
			cout << "An empty heap." << endl;
			return;
		}
		else
		{
			T last = heap[heapSize--];
			int above = 1, below = 2;
			while (below <= heapSize)
			{
				if (below + 1 <= heapSize)
					below += (heap[below] < heap[below + 1] ? 1 : 0);//将below指向值更大的那个
				if (heap[below] <= last)
					break;
				else
				{
					heap[above] = heap[below];
					above = below;
					below *= 2;
				}
			}
			heap[above] = last;
		}
	}
	~MaxHeap()
	{
		delete[] heap;
		heap = nullptr;
	}
private:
	int binarySearch(int begin, int end, int newValueIndex)
	{
		if (begin == end)
			return begin;
		else
		{
			int levelDiff = (log(end) / log(2) - log(begin) / log(2)) / 2.0 + 0.5;//得到高度较高的节点与中间高度节点的层级差
			int middle = end / pow(2, levelDiff);//得到中间高度节点的数组索引

			if (heap[newValueIndex] > heap[middle])
				return binarySearch(begin, middle, newValueIndex);
			else
			{
				middle = end / pow(2, levelDiff - 1);//得到中间高度节点下一层对应节点的数组索引
				return binarySearch(middle, end, newValueIndex);
			}
		}
	}
	void doubleSize()
	{
		T * newHeap = new T[2 * capacity + 1];
		for (int i = 1; i <= heapSize; i++)
			newHeap[i] = heap[i];
		delete[] heap;
		heap = newHeap;
		capacity *= 2;
	}
	T* heap;
	int heapSize;
	int capacity;
};

template<class T>
class UnorderedHeap {
public:
	UnorderedHeap(int capa=10) :capacity(capa) { heap = new T[capacity+1]; }
	void push(const T & x)
	{
		if (heapSize == capacity)
			doubleSize();
		heap[++heapSize] = x;//直接加到末尾
	}
	void pop()
	{
		if (heapSize == 0)
			return;
		else
		{
			int maxIndex =1;
			for (int i = 2; i <= heapSize; i++)//寻找最大元素的下标
			{
				if (heap[i] > heap[maxIndex])
					maxIndex = i;
			}
			heap[maxIndex] = heap[heapSize--];//将最后一个元素的值赋给最大元素下标对应的位置，size减1
		}
	}

	void traverse() {
		for (int i = 1; i <= heapSize; i++)
			cout << heap[i] << " ";
	}

private:
	void doubleSize()//数组扩容一倍
	{
		T * newHeap = new T[2 * capacity + 1];
		for (int i = 1; i <= heapSize; i++)
			newHeap[i] = heap[i];
		delete[] heap;
		heap = newHeap;
		capacity *= 2;
	}
	T * heap;
	int heapSize;
	int capacity;
};


int main()
{
	srand(time(0));

	const int n[] = { 100,500,1000,2000,3000,4000 };
	const int m = 1000;
	//产生随机操作序列
	bool operations[m];
	int sum = n[0];//用于记录每次操作后的队列元素数目，以确保生成的随机操作序列不会使队列为空
	bool newOp;
	for (int i = 0; i < m; i++)
	{
		//1为插入，0为删除
		newOp = rand() % 2;
		if (!newOp)//如果是删除操作，则检查该操作是否会导致队列为空
			newOp = (sum > 1 ? 0 : 1);
		sum += (newOp ? 1 : -1);//更新该步操作导致的元素数目变化
		operations[i] = newOp;
	}

	ofstream out("d:/MaxHeapPerformance.txt");//测试数据输出到该文件里

	//微秒级精度的计时方法
	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);

	for (int i = 0; i < size(n); i++)
	{
		MaxHeap<int> mh(n[i]);
		MaxHeap<int> mhBS(n[i]);
		UnorderedHeap<int> uh(n[i]);
		//先将n[i]个随机数插入到队列中
		for (int k = 0; k < n[i]; k++)
		{
			mh.push(rand());
			mhBS.push(rand());
			uh.push(rand());
		}

		out << n[i] << " ";
		
		//测试大顶堆完成m次随机插入删除操作所需运行时间
		QueryPerformanceCounter(&start);
		for (int j = 0; j < m; j++)
		{
			if (operations[j])
				mh.push(rand());
			else
				mh.pop();
		}
		QueryPerformanceCounter(&end);
		//cout << "MaxHeap costs " << ((end.QuadPart - start.QuadPart)*1.0/frequency.QuadPart) * (1000000/m) << "μs" << endl;
		out << ((end.QuadPart - start.QuadPart)*1.0 / frequency.QuadPart) * (1000000 / m) << " ";
		
		//插入操作使用折半查找，测试大顶堆完成m次随机插入删除操作所需运行时间
		QueryPerformanceCounter(&start);
		for (int j = 0; j < m; j++)
		{
			if (operations[j])
				mhBS.push(rand());
			else
				mhBS.pop();
		}
		QueryPerformanceCounter(&end);
		//cout << "Using binary search, MaxHeap costs " << ((end.QuadPart - start.QuadPart)*1.0/frequency.QuadPart) * (1000000/m) << "μs" << endl;
		out << ((end.QuadPart - start.QuadPart)*1.0 / frequency.QuadPart) * (1000000 / m) << " ";

		//测试无序表完成m次随机插入删除操作所需运行时间	
		QueryPerformanceCounter(&start);
		for (int j = 0; j < m; j++)
		{
			if (operations[j])
				uh.push(rand());
			else
				uh.pop();
		}
		QueryPerformanceCounter(&end);
		//cout << "UnorderedHeap costs " << ((end.QuadPart - start.QuadPart)*1.0 / frequency.QuadPart)*(1000000 / m) << "μs" << endl;
		out << ((end.QuadPart - start.QuadPart)*1.0 / frequency.QuadPart) * (1000000 / m) << " ";
		
		out << "\r\n";
	}
	out.close();
	
	system("pause");
}