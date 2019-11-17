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
		if (s->leftThread)//无左子树
		{
			//将原节点的左线索设为新节点的左线索，左孩子设为新节点，原节点本身设为新节点的右线索
			s->leftChild = new TreeNode<T>(l, s->leftChild, s, 1, 1);
			s->leftThread = false;
		}
		else//有左子树
		{
			//找到左子树中后继节点是原节点的节点
			TreeNode<T> * previous = previousNode(s);
			//将原节点的左子树设为新节点的左孩子，原节点本身设为新节点的右线索
			s->leftChild = new TreeNode<T>(l, s->leftChild, s, 0, 1);
			//更新后继节点，指向新节点
			previous->rightChild = s->leftChild;
		}

	}
	void insertRight(const T & r, TreeNode<T> *s = nullptr) {
		if (head->leftChild == head)//说明全树只有一个头节点，则将新增节点插入为头节点的左孩子
		{
			head->leftChild = new TreeNode<T>(r, head, head, 1, 1);
			head->leftThread = false;
		}
		else
		{
			if (!s)
				s = head->leftChild;
			if (s->rightThread)//无右子树
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
		if (node->leftThread)//是叶节点，则直接返回指向了前驱节点的左孩子
			return node->leftChild;
		else
		{
			TreeNode<T> * current = node->leftChild;
			while (current)
			{
				if (current->rightChild == node)//找到了前驱节点
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
		while (current != head)//预防全树只有头节点的情况
		{
			while (!current->leftThread)//找到左子树中的第一个要访问的节点
				current = current->leftChild;
			cout << current->data << " ";
			while (current->rightThread)//当rightChild储存的是后继节点的信息时，不断访问，直到遇到右子树
			{
				current = current->rightChild;
				if (current == head)//全树遍历完了
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
			if (!current->leftThread)//若当前节点有左子树，则访问左子树的根节点
				current = current->leftChild;
			else if (!current->rightThread)//无左子树但有右子树，则访问右子树的根节点
				current = current->rightChild;
			else//说明该节点是叶节点
			{
				current = current->rightChild;//叶子的后继节点总是上层的某个父节点或头节点
				while (current->rightThread&&current->rightChild != head)//跳过那些已经访问输出过的父节点
					current = current->rightChild;
				if (current == head)//说明整棵树已遍历完了，返回
					return;
				if (current->rightChild != head)//说明还未遍历完
					current = current->rightChild;//则访问父节点的右孩子
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