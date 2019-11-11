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
		last->link = last;//��ͷ���
	}

	class CircularListIterator:public std::iterator<forward_iterator_tag,T>//�Զ����������̳�iterator
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
	typedef CircularListIterator iterator;//���ñ�����ͳһ�۸�

	CircularListIterator begin() const{ return CircularListIterator(last->link->link); }
	CircularListIterator end() const{ return CircularListIterator(last->link); }

	void insertBack(const T& e)
	{
		ChainNode<T> * node = getNode(e,last->link);//ָ���ͷ���
		last->link = node;//ԭ����β�ڵ�ָ�������ڵ�
		last = node;//lastָ�������ڵ�
	}
	void insertFront(const T& e)
	{
		ChainNode<T> * node = getNode(e,last->link->link);//ָ��ԭ�ȱ�ͷ����ĵ�һ���ڵ�
		last->link->link = node;//��ͷ���ָ��������ڵ�
	}

	void deleteChain()
	{//ֻ�б�ͷ����������൱�ڿ����������κβ���
		if (last != last->link)//����ͷ��㻹���������ڵ�
		{
			ChainNode<T> * head = last->link;//�ݴ��ͷָ���λ��
			last->link = available;//�����һ���ڵ�ָ��available��ָ�Ľڵ���
			available = head->link;//����availableָ���ͷ���֮��ĵ�һ���ڵ�

			last = head;//�ٰ�lastָ���ͷ���
			last->link = head;//��ͷ���ָ������
			//�����Ͱѳ���ͷ���֮��Ľڵ������յ��˿��ÿռ�������
		}
	}
private:
	ChainNode<T> * getNode(const T& e,ChainNode<T> * link)
	{
		ChainNode<T> * x;
		if (available)//���ÿռ��������пռ䣬�򽫸ÿռ�������������ֵ�󷵻�
		{
			x = available;
			available = available->link;
			x->data = e; 
			x->link = link;

		}
		else//�޿ռ䣬��newһ��
			x = new ChainNode<T>(e,link);
		return x;
	}

	ChainNode<T> * last;
	static ChainNode<T> * available;//ָ����ÿռ�����Ϊ��ĸ�������������
};

template<class T>
ChainNode<T>* CircularList<T>::available = nullptr;
#endif