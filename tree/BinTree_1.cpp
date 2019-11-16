#include<iostream>
#include<iterator>
#include<stack>
using namespace std;

template<class T>
class BinaryTree;

template<class T>
class TreeNode {
	friend class BinaryTree<T>;
public:
	TreeNode(const T & d=NULL, TreeNode<T> * l=nullptr,TreeNode<T> * r=nullptr):data(d),leftChild(l),rightChild(r){}
private:
	T data;
	TreeNode<T> * leftChild;
	TreeNode<T> * rightChild;
};

template<class T>
class BinaryTree {
public:
	BinaryTree()
	{
		cout << "Create the tree in inorder way: " << endl;
		createBTreeInorder(root);
	}

	//中序创建二叉树
	void createBTreeInorder(TreeNode<T> * & node)
	{
		T data = NULL;
		cout << "Enter the data or # to mean NULL: " << endl;
		cin >> data;
		if(data=='#'||cin.fail())
		{
			if (cin.fail())//用于处理接收端为int型，但输入为字符'#'导致的异常情况
			{
				cin.clear();
				cin.get();
			}
			return;
		}
		else
		{
			node = new TreeNode<T>(data);
			createBTreeInorder(node->leftChild);
			createBTreeInorder(node->rightChild);
		}
	}
	
	
	/************题P267-4*********/
	class TreeInorderIterator :public std::iterator<forward_iterator_tag, T>
	{
	public:
		TreeInorderIterator(TreeNode<T> * startNode){ current = startNode;}
		T& operator*() const { return current->data; }
		T* operator->() const { return &current->data; }
		//迭代法，返回中序遍历方式下的后继节点
		T * next()
		{
			while (current)
			{
				s.push(current);
				current = current->leftChild;
			}
			if (s.empty())
				return nullptr;
			current = s.top();
			s.pop();
			T & temp = current->data;
			current = current->rightChild;
			return &temp;
		}
	private:
		TreeNode<T> * current;
		stack<TreeNode<T> *> s;//用于中序遍历存储前驱节点信息
	};
	typedef TreeInorderIterator iterator;
	iterator begin() const { return TreeInorderIterator(root); }
	/*********************/


	/************题P267-6*********/
	//迭代法，从根节点开始前序遍历
	void NoRecPreorderTraverse()
	{
		NoRecPreorderTraverse(root);
	}

	//迭代法，从指定节点位置处开始前序遍历
	void NoRecPreorderTraverse(TreeNode<T> * node)
	{
		stack<TreeNode<T> *> s;
		TreeNode<T> * current = node;
		while (1) {
			while (current) {
				s.push(current);
				cout << current->data << " ";
				current = current->leftChild;
			}
			if (s.empty()) 
				return;
			current = s.top();
			s.pop();
			current = current->rightChild;
		}
		cout << endl;
	}
	/*********************/


	/************题P272-1*********/
	int leafSize()
	{
		return leafSize(root);
	}

	//迭代前序遍历法来计算叶子节点数
	int leafSize(TreeNode<T> * node)
	{
		stack<TreeNode<T> *> s;
		TreeNode<T> * current = node;
		int size = 0;
		while (1)
		{
			while (current) {
				s.push(current);
				if (!(current->leftChild || current->rightChild))//为叶子节点
					size++;
				current = current->leftChild;
			}
			if (s.empty())
				return size;
			current = s.top();
			s.pop();
			current = current->rightChild;
		}
	}
	/*********************/


	/************题P273-4*********/
	//递归后序遍历删除节点
	void deleteRecursively(TreeNode<T> * node)
	{
		if (node)
		{
			deleteRecursively(node->leftChild);
			deleteRecursively(node->rightChild);
			delete node;
		}
	}

	~BinaryTree()
	{
		deleteRecursively(root);
	}
	/*********************/

private:
	TreeNode<T> * root;
};

int main()
{
	{
		BinaryTree<int> tree;
		
		//迭代器中序遍历
		cout << "\nInorderTraverse: ";
		BinaryTree<int>::iterator it = tree.begin();
		for (int * data = it.next(); data != nullptr; data = it.next())
			cout << *data << " ";
		
		cout << "\nPreorderTraverse:";
		//前序遍历的非递归版本
		tree.NoRecPreorderTraverse();

		//叶子节点
		cout << "\nThe size of leaves in the tree is: "<<tree.leafSize() << endl;
	}
	system("pause");
}