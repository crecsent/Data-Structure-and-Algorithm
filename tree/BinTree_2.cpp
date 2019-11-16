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
	//�������캯��
	BinaryTree(const BinaryTree<T> & b) :root(nullptr)
	{
		copyNode(root, b.root);
	}
	//�����������ϳɴ�������
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
			//�ڶ��ϴ������󣬱����ھֲ�������Խ��������ʱ�����������·��ض���Ľ�������΢�����
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
		//�ڶ��ϴ������󣬱����ھֲ�������Խ��������ʱ�����������·��ض���Ľ�������΢�����
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

	//���ֱ�����ʽ�ĵ�����
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

		//���������������������ʽ�µĺ�̽ڵ�
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
		stack<TreeNode<T> *> s;//������������洢ǰ���ڵ���Ϣ
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
			while (top->rightChild&&previousNode != top->rightChild)//�зǿ��ҽڵ��Ҹ��ҽڵ�û�����ʹ�
			{
				TreeNode<T>* current = top->rightChild;
				while (current)//�ҵ����ҽڵ�����Ӧ�������ĵ�һ��Ҫ�����ʵĽڵ�
				{
					s.push(current);
					current = current->leftChild;
				}
				top = s.top();
			}
			previousNode = top;//����Ϊ�ѷ��ʽڵ�
			s.pop();
			return top;
		}
	private:
		TreeNode<T> * previousNode;//���ڱ����ϴη��ʵĽڵ㣬�Ƚ��¸��ڵ���ҽڵ��Ƿ���֮��ͬ���Դ��ж��Ƿ���Ҫ��ջ�е���
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

	//�ݹ�������ɾ���ڵ�
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
	void createBTree(TreeNode<T> * & node)//������ͨ���캯���и��ݿ���̨���봴����
	{
		T data = NULL;
		cout << "Enter the data or # to mean NULL: " << endl;
		cin >> data;
		if (data == '#' || cin.fail())
		{
			if (cin.fail())//���ڴ�����ն�Ϊint�ͣ�������Ϊ�ַ�'#'���µ��쳣���
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
	void copyNode(TreeNode<T> *& acurrent, TreeNode<T> * bcurrent)//���ڿ������캯����������ƽڵ�
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
		//�������ֱ�������
		cout << "\ntree1 preorder: " << endl;
		tree1.preorderTraverse(tree1.getRootNode());
		cout << "\ntree1 inorder: " << endl;
		tree1.inorderTraverse(tree1.getRootNode());
		cout << "\ntree1 postorder: " << endl;
		tree1.postorderTraverse(tree1.getRootNode());
		cout << "\ntree1 levelorder: " << endl;
		tree1.levelTraverse(tree1.getRootNode());

		//���Կ������캯��
		BinaryTree<int> tree2(tree1);
		//�������ֱ��������ĵ�����
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

		//���Ժϳ���
		BinaryTree<int> co(tree1, 5, tree2);
		cout << "combine tree1 and tree2 together, level traverse: " << endl;
		co.levelTraverse(co.getRootNode());
		//����get��������
		BinaryTree<int> left = tree1.leftSubTree();
		cout << "left sub tree:" << endl;
		left.preorderTraverse(left.getRootNode());
		BinaryTree<int> right = tree1.rightSubTree();
		cout << "right sub tree:" << endl;
		right.preorderTraverse(right.getRootNode());
		

	}//������������

	system("pause");
}