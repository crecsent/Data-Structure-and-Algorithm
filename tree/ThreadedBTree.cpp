#include<iostream>
using namespace std;

template<class T>
class ThreadedBTree;

template<class T>
class TreeNode {
	friend class ThreadedBTree<T>;
public:
	TreeNode(const T & d = T(), TreeNode<T> * l = nullptr, TreeNode<T> * r = nullptr, bool lt = false, bool rt = false)
		:data(d), leftChild(l), rightChild(r), leftThread(lt), rightThread(rt) {}
	T getData() { return data; }
private:
	T data;
	TreeNode<T> * leftChild;
	TreeNode<T> * rightChild;
	bool leftThread;
	bool rightThread;
};

template<class T>
class ThreadedBTree {
public:
	ThreadedBTree()
	{
		head = new TreeNode<T>(T(), nullptr, nullptr, 1, 1);
		head->leftChild = head;
		head->rightChild = head;
	}
	void insertLeft(const T & l, TreeNode<T> *s = nullptr) {

		if (!s)
			s = head->leftChild;
		if (s->leftThread)//��������
		{
			//��ԭ�ڵ����������Ϊ�½ڵ����������������Ϊ�½ڵ㣬ԭ�ڵ㱾����Ϊ�½ڵ��������
			s->leftChild = new TreeNode<T>(l, s->leftChild, s, 1, 1);
			s->leftThread = false;
		}
		else//��������
		{
			//�ҵ��������к�̽ڵ���ԭ�ڵ�Ľڵ�
			TreeNode<T> * previous = previousNode(s);
			//��ԭ�ڵ����������Ϊ�½ڵ�����ӣ�ԭ�ڵ㱾����Ϊ�½ڵ��������
			s->leftChild = new TreeNode<T>(l, s->leftChild, s, 0, 1);
			//���º�̽ڵ㣬ָ���½ڵ�
			previous->rightChild = s->leftChild;
		}

	}
	void insertRight(const T & r, TreeNode<T> *s = nullptr) {
		if (head->leftChild == head)//˵��ȫ��ֻ��һ��ͷ�ڵ㣬�������ڵ����Ϊͷ�ڵ������
		{
			head->leftChild = new TreeNode<T>(r, head, head, 1, 1);
			head->leftThread = false;
		}
		else
		{
			if (!s)
				s = head->leftChild;
			if (s->rightThread)//��������
			{
				s->rightChild = new TreeNode<T>(r, s, s->rightChild, 1, 1);
				s->rightThread = false;
			}
			else
			{
				TreeNode<T> * next = nextNode(s);
				s->rightChild = new TreeNode<T>(r, s, s->rightChild, 1, 0);
				next->leftChild = s->rightChild;
			}
		}

	}
	TreeNode<T> * previousNode(TreeNode<T> * node)
	{
		if (node->leftThread)//��Ҷ�ڵ㣬��ֱ�ӷ���ָ����ǰ���ڵ������
			return node->leftChild;
		else
		{
			TreeNode<T> * current = node->leftChild;
			while (current)
			{
				if (current->rightChild == node)//�ҵ���ǰ���ڵ�
					break;
				current = current->rightChild;
			}
			return current;
		}
	}
	TreeNode<T> * nextNode(TreeNode<T> * node)
	{
		if (node->rightThread)
			return node->rightChild;
		else
		{
			TreeNode<T> * current = node->rightChild;
			while (current)
			{
				if (current->leftChild == node)
					break;
				current = current->leftChild;
			}
			return current;
		}
	}
	void inorderTraverse() const
	{
		inorderTraverse(head->leftChild);
	}
	void inorderTraverse(TreeNode<T> * node) const
	{
		if (!node)
			return;
		TreeNode<T> * current = node;
		while (current != head)//Ԥ��ȫ��ֻ��ͷ�ڵ�����
		{
			while (!current->leftThread)//�ҵ��������еĵ�һ��Ҫ���ʵĽڵ�
				current = current->leftChild;
			cout << current->data << " ";
			while (current->rightThread)//��rightChild������Ǻ�̽ڵ����Ϣʱ�����Ϸ��ʣ�ֱ������������
			{
				current = current->rightChild;
				if (current == head)//ȫ����������
					return;
				cout << current->data << " ";
			}
			current = current->rightChild;
		}
	}

	void preorderTraverse() const
	{
		preorderTraverse(head->leftChild);
	}

	void preorderTraverse(TreeNode<T> * node) const
	{
		if (!node || node == head)
			return;
		TreeNode<T> * current = node;

		while (current != head)
		{
			cout << current->data << " ";
			if (!current->leftThread)//����ǰ�ڵ�����������������������ĸ��ڵ�
				current = current->leftChild;
			else if (!current->rightThread)//��������������������������������ĸ��ڵ�
				current = current->rightChild;
			else//˵���ýڵ���Ҷ�ڵ�
			{
				current = current->rightChild;//Ҷ�ӵĺ�̽ڵ������ϲ��ĳ�����ڵ��ͷ�ڵ�
				while (current->rightThread&&current->rightChild != head)//������Щ�Ѿ�����������ĸ��ڵ�
					current = current->rightChild;
				if (current == head)//˵���������ѱ������ˣ�����
					return;
				if (current->rightChild != head)//˵����δ������
					current = current->rightChild;//����ʸ��ڵ���Һ���
			}
		}
	}
private:
	TreeNode<T> * head;
};
int main()
{
	ThreadedBTree<int> tbt;
	for (int i = 0; i < 10; i++)
	{
		if (i% 2==0)
			tbt.insertLeft(i);
		else
			tbt.insertRight(i);
	}
	cout << "inorder: " << endl;
	tbt.inorderTraverse();
	cout << "\ninsert 10 to the left of 0...... " << endl;
	tbt.insertLeft(10);
	cout << "inorder after inserting: " << endl;
	tbt.inorderTraverse();
	cout << "\npreorder: " << endl;
	tbt.preorderTraverse();

	system("pause");
}