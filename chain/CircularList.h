#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H
#include<iostream>
#include<iterator>
using namespace std;

template<class T>
class CircularList;

template<class T>
class ChainNode {
	friend class CircularList<T>;
public:
	ChainNode(T element= T(), ChainNode<T> * next = 0) { data = element; link = next; }
private:
	T data;
	ChainNode<T> * link;
};

template<class T>
class CircularList {
public:
	CircularList()
	{
		last = new ChainNode<T>();
		last->link = last;//表头结点
	}

	class CircularListIterator:public std::iterator<forward_iterator_tag,T>//自定义迭代器需继承iterator
	{
	public:
		CircularListIterator(ChainNode<T> * startNode = 0) :current(startNode) {}
		T& operator*() const { return current->data; }
		T* operator->() const { return &current->data; }

		CircularListIterator& operator++() { current = current->link; return *this; }
		CircularListIterator operator++(int) { CircularListIterator old = *this; current = current->link; return old; }
		bool operator!=(const CircularListIterator right) const { return current != right.current; }
		bool operator==(const CircularListIterator right)const { return current == right.current; }
	private:
		ChainNode<T> * current;
	};
	typedef CircularListIterator iterator;//设置别名，统一观感

	CircularListIterator begin() const{ return CircularListIterator(last->link->link); }
	CircularListIterator end() const{ return CircularListIterator(last->link); }

	void insertBack(const T& e)
	{
		ChainNode<T> * node = getNode(e,last->link);//指向表头结点
		last->link = node;//原来的尾节点指向新增节点
		last = node;//last指向新增节点
	}
	void insertFront(const T& e)
	{
		ChainNode<T> * node = getNode(e,last->link->link);//指向原先表头结点后的第一个节点
		last->link->link = node;//表头结点指向该新增节点
	}

	void deleteChain()
	{//只有表头结点的情况（相当于空链表）不做任何操作
		if (last != last->link)//除表头结点还含有其他节点
		{
			ChainNode<T> * head = last->link;//暂存表头指针的位置
			last->link = available;//将最后一个节点指向available所指的节点链
			available = head->link;//再用available指向表头结点之后的第一个节点

			last = head;//再把last指向表头结点
			last->link = head;//表头结点指向自身
			//这样就把除表头结点之外的节点链回收到了可用空间链表里
		}
	}
private:
	ChainNode<T> * getNode(const T& e,ChainNode<T> * link)
	{
		ChainNode<T> * x;
		if (available)//可用空间链表中有空间，则将该空间用所给参数赋值后返回
		{
			x = available;
			available = available->link;
			x->data = e; 
			x->link = link;

		}
		else//无空间，则new一个
			x = new ChainNode<T>(e,link);
		return x;
	}

	ChainNode<T> * last;
	static ChainNode<T> * available;//指向可用空间链表，为类的各个对象所共享
};

template<class T>
ChainNode<T>* CircularList<T>::available = nullptr;
#endif