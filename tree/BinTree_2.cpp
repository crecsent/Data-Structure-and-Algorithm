#include<iostream>
#include<iterator>
#include<stack>
#include<queue>
using namespace std;

template<class T>
class BinaryTree;

template<class T>
class TreeNode {
	friend class BinaryTree<T>;
public:
	TreeNode(const T & d = T(), TreeNode<T> * l = nullptr, TreeNode<T> * r = nullptr) :data(d), leftChild(l), rightChild(r) {}
	T getData() { return data; }
private:
	T data;
	TreeNode<T> * leftChild;
	TreeNode<T> * rightChild;
};

template<class T>
class BinaryTree {
public:
	BinaryTree(TreeNode<T> * rootNode = nullptr) :root(nullptr)
	{
		if (rootNode)
			root = rootNode;
		else
		{
			cout << "Create the tree in inorder way: " << endl;
			createBTree(root);
		}
	}
	//拷贝构造函数
	BinaryTree(const BinaryTree<T> & b) :root(nullptr)
	{
		copyNode(root, b.root);
	}
	//用两棵子树合成创建新树
	BinaryTree(BinaryTree<T> & bt1, const T & item, BinaryTree<T> & bt2)
	{
		BinaryTree<T> left(bt1);
		BinaryTree<T> right(bt2);
		root = new TreeNode<T>(item, left.root, right.root);
		left.root = nullptr;
		right.root = nullptr;
	}

	bool isEmpty()
	{
		return root == nullptr;
	}

	BinaryTree<T> leftSubTree()
	{
		if ((!isEmpty()) && root->leftChild)
		{
			//在堆上创建对象，避免在局部变量在越出作用域时被析构，导致返回对象的接收者有微妙错误
			BinaryTree<T> * left = new BinaryTree<T>(root->leftChild);
			left->copyNode(left->root, root->leftChild);
			return *left;
		}
		else
		{
			cout << "An empty tree." << endl;
			return *this;
		}
	}
	BinaryTree<T> rightSubTree()
	{
		//在堆上创建对象，避免在局部变量在越出作用域时被析构，导致返回对象的接收者有微妙错误
		if ((!isEmpty()) && root->rightChild)
		{
			BinaryTree<T> * right = new BinaryTree<T>(root->rightChild);
			right->copyNode(right->root, root->rightChild);
			return *right;
		}
		else
		{
			cout << "An empty tree." << endl;
			return *this;
		}
	}

	//四种遍历方式的迭代器
	class TreePreorderIterator :public std::iterator<forward_iterator_tag, T>
	{
	public:
		TreePreorderIterator(TreeNode<T> * node)
		{
			if (node)
				s.push(node);
		}

		TreeNode<T> * next()
		{
			if (s.empty())
				return nullptr;
			TreeNode<T> * top = s.top();
			s.pop();
			if (top->rightChild)
				s.push(top->rightChild);
			if (top->leftChild)
				s.push(top->leftChild);
			return top;
		}
	private:
		stack<TreeNode<T> *> s;
	};
	class TreeInorderIterator :public std::iterator<forward_iterator_tag, T>
	{
	public:
		TreeInorderIterator(TreeNode<T> * node) {
			TreeNode<T> * current = node;
			while (current)
			{
				s.push(current);
				current = current->leftChild;
			}
		}

		//迭代法，返回中序遍历方式下的后继节点
		TreeNode<T> * next()
		{
			if (s.empty()) return nullptr;
			TreeNode<T> * top = s.top();
			s.pop();
			if (top->rightChild)
			{
				TreeNode<T> * current = top->rightChild;
				while (current)
				{
					s.push(current);
					current = current->leftChild;
				}
			}
			return top;
		}
	private:
		stack<TreeNode<T> *> s;//用于中序遍历存储前驱节点信息
	};
	class TreePostorderIterator :public std::iterator<forward_iterator_tag, T>
	{
	public:
		TreePostorderIterator(TreeNode<T> * node)
		{
			while (node)
			{
				s.push(node);
				if (node->leftChild)
					node = node->leftChild;
				else if (node->rightChild)
					node = node->rightChild;
				else
					node = nullptr;
			}
		}
		TreeNode<T> * next()
		{
			if (s.empty())
				return nullptr;
			TreeNode<T> * top = s.top();
			while (top->rightChild&&previousNode != top->rightChild)//有非空右节点且该右节点没被访问过
			{
				TreeNode<T>* current = top->rightChild;
				while (current)//找到该右节点所对应的子树的第一个要被访问的节点
				{
					s.push(current);
					current = current->leftChild;
				}
				top = s.top();
			}
			previousNode = top;//设置为已访问节点
			s.pop();
			return top;
		}
	private:
		TreeNode<T> * previousNode;//用于保存上次访问的节点，比较下个节点的右节点是否与之相同，以此判断是否需要从栈中弹出
		stack<TreeNode<T> *> s;
	};
	class TreeLevelIterator :public std::iterator<forward_iterator_tag, T>
	{
	public:
		TreeLevelIterator(TreeNode<T> * node)
		{
			if (node)
				q.push(node);
		}
		TreeNode<T> * next()
		{
			if (q.empty())
				return nullptr;
			TreeNode<T> * top = q.front();
			q.pop();
			if (top->leftChild) q.push(top->leftChild);
			if (top->rightChild) q.push(top->rightChild);
			return top;
		}
	private:
		queue<TreeNode<T>*> q;
	};

	typedef TreePreorderIterator preorderIt;
	typedef TreeInorderIterator inorderIt;
	typedef TreePostorderIterator postorderIt;
	typedef TreeLevelIterator levelIt;

	TreeNode<T> * getRootNode() { return root; }
	void preorderTraverse(TreeNode<T> * node) const
	{

		if (node)
		{
			cout << node->data << " ";
			preorderTraverse(node->leftChild);
			preorderTraverse(node->rightChild);
		}
	}
	void inorderTraverse(TreeNode<T> * node) const
	{

		if (node)
		{
			inorderTraverse(node->leftChild);
			cout << node->data << " ";
			inorderTraverse(node->rightChild);
		}
	}
	void postorderTraverse(TreeNode<T> * node) const
	{
		if (node)
		{
			postorderTraverse(node->leftChild);
			postorderTraverse(node->rightChild);
			cout << node->data << " ";
		}
	}
	void levelTraverse(TreeNode<T> * node) const
	{
		queue<TreeNode<T> *> q;
		if (node)
		{
			q.push(node);
			TreeNode<T> * current;
			while (!q.empty())
			{
				current = q.front();
				q.pop();
				cout << current->data << " ";
				if (current->leftChild)
					q.push(current->leftChild);
				if (current->rightChild)
					q.push(current->rightChild);
			}
		}
	}

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
		cout << "Deleting finished." << endl;
	}

private:
	void createBTree(TreeNode<T> * & node)//用于普通构造函数中根据控制台输入创建树
	{
		T data = NULL;
		cout << "Enter the data or # to mean NULL: " << endl;
		cin >> data;
		if (data == '#' || cin.fail())
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
			createBTree(node->leftChild);
			createBTree(node->rightChild);
		}
	}
	void copyNode(TreeNode<T> *& acurrent, TreeNode<T> * bcurrent)//用于拷贝构造函数中逐个复制节点
	{
		if (bcurrent)
		{
			acurrent = new TreeNode<T>(bcurrent->data);
			copyNode(acurrent->leftChild, bcurrent->leftChild);
			copyNode(acurrent->rightChild, bcurrent->rightChild);
		}
	}
	TreeNode<T> * root;
};


int main()
{
	{
		BinaryTree<int> tree1;
		//测试四种遍历方法
		cout << "\ntree1 preorder: " << endl;
		tree1.preorderTraverse(tree1.getRootNode());
		cout << "\ntree1 inorder: " << endl;
		tree1.inorderTraverse(tree1.getRootNode());
		cout << "\ntree1 postorder: " << endl;
		tree1.postorderTraverse(tree1.getRootNode());
		cout << "\ntree1 levelorder: " << endl;
		tree1.levelTraverse(tree1.getRootNode());

		//测试拷贝构造函数
		BinaryTree<int> tree2(tree1);
		//测试四种遍历方法的迭代器
		TreeNode<int> * start;

		BinaryTree<int>::preorderIt it1(tree1.getRootNode());
		cout << "\ntree2 traverse using preorderIt: " << endl;
		for (start = it1.next(); start != nullptr; start = it1.next())
			cout << start->getData() << " ";

		BinaryTree<int>::inorderIt it2(tree1.getRootNode());
		cout << "\ntree2 traverse using inorderIt: " << endl;
		for (start = it2.next(); start != nullptr; start = it2.next())
			cout << start->getData() << " ";

		BinaryTree<int>::postorderIt it3(tree1.getRootNode());
		cout << "\ntree2 traverse using postorderIt: " << endl;
		for (start = it3.next(); start != nullptr; start = it3.next())
			cout << start->getData() << " ";

		BinaryTree<int>::levelIt it4(tree1.getRootNode());
		cout << "\ntree2 traverse using levelIt: " << endl;
		for (start = it4.next(); start != nullptr; start = it4.next())
			cout << start->getData() << " ";

		//测试合成树
		BinaryTree<int> co(tree1, 5, tree2);
		cout << "combine tree1 and tree2 together, level traverse: " << endl;
		co.levelTraverse(co.getRootNode());
		//测试get左右子树
		BinaryTree<int> left = tree1.leftSubTree();
		cout << "left sub tree:" << endl;
		left.preorderTraverse(left.getRootNode());
		BinaryTree<int> right = tree1.rightSubTree();
		cout << "right sub tree:" << endl;
		right.preorderTraverse(right.getRootNode());
		

	}//测试析构函数

	system("pause");
}