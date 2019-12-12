#include<iostream>
using namespace std;

template<class T>
class Chain;

template<class T>
class Node
{
	friend class Chain<T>;
public:
	Node(const T & d = T(), Node<T> * l = nullptr) :data(d), link(l) {}
private:
	T data;
	Node<T> * link;
};

template<class T>
class Chain
{
public:
	Chain() :first(nullptr) {}
	void insert(const T & d)
	{
		Node<T> * newNode = new Node<T>(d, first);
		first = newNode;
	}

	void print() const
	{
		Node<T> * current = first;
		while (current)
		{
			cout << current->data << " ";
			current = current->link;
		}
		cout << endl;
	}
	void InsertionSort()
	{
		if (first)
		{
			Node<T> * toInsert = first->link;//待排序的剩余元素
			Node<T> * current = new Node<T>;//存放已排序元素
			Node<T> * temp = nullptr;
			first->link = nullptr;
			current->link = first;
			first = current;

			while (toInsert)
			{
				while (current->link&&toInsert->data >= current->link->data)
					current = current->link;

				temp = toInsert->link;
				toInsert->link = current->link;
				current->link = toInsert;
				toInsert = temp;

				current = first;//重新指回已排序链表的开头
			}

			first = current->link;
			delete current;
		}

	}
private:
	Node<T> * first;
};


int main()
{
	Chain<int> c;
	for (int i = 0; i < 10; i++)
		c.insert(rand() % 30);
	cout << "Chain before insertion sorting:" << endl;
	c.print();
	c.InsertionSort();
	cout << "Chain after insertion sorting:" << endl;
	c.print();
	system("pause");
}