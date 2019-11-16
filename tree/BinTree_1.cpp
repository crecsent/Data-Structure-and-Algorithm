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

	//���򴴽�������
	void createBTreeInorder(TreeNode<T> * & node)
	{
		T data = NULL;
		cout << "Enter the data or # to mean NULL: " << endl;
		cin >> data;
		if(data=='#'||cin.fail())
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
			createBTreeInorder(node->leftChild);
			createBTreeInorder(node->rightChild);
		}
	}
	
	
	/************��P267-4*********/
	class TreeInorderIterator :public std::iterator<forward_iterator_tag, T>
	{
	public:
		TreeInorderIterator(TreeNode<T> * startNode){ current = startNode;}
		T& operator*() const { return current->data; }
		T* operator->() const { return &current->data; }
		//���������������������ʽ�µĺ�̽ڵ�
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
		stack<TreeNode<T> *> s;//������������洢ǰ���ڵ���Ϣ
	};
	typedef TreeInorderIterator iterator;
	iterator begin() const { return TreeInorderIterator(root); }
	/*********************/


	/************��P267-6*********/
	//���������Ӹ��ڵ㿪ʼǰ�����
	void NoRecPreorderTraverse()
	{
		NoRecPreorderTraverse(root);
	}

	//����������ָ���ڵ�λ�ô���ʼǰ�����
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


	/************��P272-1*********/
	int leafSize()
	{
		return leafSize(root);
	}

	//����ǰ�������������Ҷ�ӽڵ���
	int leafSize(TreeNode<T> * node)
	{
		stack<TreeNode<T> *> s;
		TreeNode<T> * current = node;
		int size = 0;
		while (1)
		{
			while (current) {
				s.push(current);
				if (!(current->leftChild || current->rightChild))//ΪҶ�ӽڵ�
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


	/************��P273-4*********/
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
	}
	/*********************/

private:
	TreeNode<T> * root;
};

int main()
{
	{
		BinaryTree<int> tree;
		
		//�������������
		cout << "\nInorderTraverse: ";
		BinaryTree<int>::iterator it = tree.begin();
		for (int * data = it.next(); data != nullptr; data = it.next())
			cout << *data << " ";
		
		cout << "\nPreorderTraverse:";
		//ǰ������ķǵݹ�汾
		tree.NoRecPreorderTraverse();

		//Ҷ�ӽڵ�
		cout << "\nThe size of leaves in the tree is: "<<tree.leafSize() << endl;
	}
	system("pause");
}