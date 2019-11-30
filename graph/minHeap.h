#include<iostream>
using namespace std;

template<class T>
class MinPQ {
public:
	virtual ~MinPQ() {}
	virtual bool isEmpty() const = 0;
	virtual const T& top() const = 0;
	virtual void push(const T&) = 0;
	virtual void pop() = 0;
};

template<class T>
class MinHeap :public MinPQ<T> {
public:
	MinHeap(int capa = 10)
	{
		if (capa < 1)
			throw "Capacity must be >= 1.";
		capacity = capa;
		heapSize = 0;
		heap = new T[capacity + 1];//heap[0]����

	}
	MinHeap(const MinHeap & a)
	{
		capacity = a.capacity;
		heapSize = a.heapSize;
		heap = new T[capacity+1];
		for (int i = 1; i <= heapSize; i++)
			heap[i] = a.heap[i];
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
		//���ϱȽϵ�ǰ�ڵ�ֵ���丸�ڵ�ֵ��С����ֵ���򽻻�����ֵС���˳�ѭ��
		while (parentIndex != 0 && heap[parentIndex] > x)
		{
			heap[currentIndex] = heap[parentIndex];//�����ڵ�����
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
					below += (heap[below] > heap[below + 1] ? 1 : 0);//��belowָ��ֵ��С���Ǹ��ӽڵ�
				if (heap[below] >= last)
					break;
				else
				{
					heap[above] = heap[below];
					above = below;
					below *= 2;
				}
			}
			heap[above] = last;//Ϊ�������һλԪ���ҵ���λ��
		}
	}
	~MinHeap()
	{
		delete[] heap;
		heap = nullptr;
	}
private:
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
