#include<iostream>
using namespace std;

template<class T>
class DblList;

template<class T>
class DblListNode {
	friend class DblList<T>;
public:
	DblListNode<T>(const T e = NULL, DblListNode<T> * l = nullptr, DblListNode<T> * r = nullptr)
		: data(e), left(l), right(r) {}
private:
	T data;
	DblListNode<T> * left, *right;
};

template<class T>
class DblList {
public:
	DblList()
	{
		head = new DblListNode<T>();//创建表头结点
		head->left = head; head->right = head;
	}

	void insertAtFront(const T & e)
	{
		DblListNode<T> * newNode = new DblListNode<T>(e, head, head->right);//新增节点的左节点设为头节点，右节点设为原来的第一个节点
		head->right->left = newNode;//原来的第一个节点的左节点设为新增节点
		head->right = newNode;//头节点的右节点设为新增节点
	}

	void deleteNode(DblListNode<T> * node)
	{
		if (node != head)
		{
			node->left->right = node->right;
			node->right->left = node->left;
			delete node;
		}
	}

	DblListNode<T> * getNodeAt(int index)
	{
		DblListNode<T> * current = head;
		for (; index > 0; index--)
			current = current->left;
		return current;
	}

	void traverse()
	{
		DblListNode<T> * current = head->right;
		if (current == head)
			cout << "Empty list!";
		while (current != head)
		{
			cout << current->data << " ";
			current = current->right;
		}
		cout << endl;
	}

	void concatenate(DblList<T> & m)
	{
		if (m.head->left != head)//m链表非空才执行
		{
			//m链表的第一个节点接到this链表的原尾部节点右边
			this->head->left->right = m.head->right;
			m.head->right->left = this->head->left;
			//m链表的最后一个节点接到this链表head节点的左边
			this->head->left = m.head->left;
			m.head->left->right = this->head;
			//使链表m为空
			m.head->left = m.head;
			m.head->right = m.head;
		}
	}

private:
	DblListNode<T> * head;
};

int main()
{
	DblList<int> list1, list2;
	for (int i = 0; i < 10; i++)
		list1.insertAtFront(i);
	for (int i = 10; i < 20; i++)
		list2.insertAtFront(i);
	cout << "list1: ";
	list1.traverse();
	cout << "list2: ";
	list2.traverse();

	list1.concatenate(list2);
	cout << "list1 after concatenating:";
	list1.traverse();
	cout << "list2 after concatenating: ";
	list2.traverse();

	system("pause");
}