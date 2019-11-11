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
		head = new DblListNode<T>();//������ͷ���
		head->left = head; head->right = head;
	}

	void insertAtFront(const T & e)
	{
		DblListNode<T> * newNode = new DblListNode<T>(e, head, head->right);//�����ڵ����ڵ���Ϊͷ�ڵ㣬�ҽڵ���Ϊԭ���ĵ�һ���ڵ�
		head->right->left = newNode;//ԭ���ĵ�һ���ڵ����ڵ���Ϊ�����ڵ�
		head->right = newNode;//ͷ�ڵ���ҽڵ���Ϊ�����ڵ�
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
		if (m.head->left != head)//m����ǿղ�ִ��
		{
			//m����ĵ�һ���ڵ�ӵ�this�����ԭβ���ڵ��ұ�
			this->head->left->right = m.head->right;
			m.head->right->left = this->head->left;
			//m��������һ���ڵ�ӵ�this����head�ڵ�����
			this->head->left = m.head->left;
			m.head->left->right = this->head;
			//ʹ����mΪ��
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