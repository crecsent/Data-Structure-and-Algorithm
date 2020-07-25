#include<iostream>
#include<algorithm>
#include<iomanip>
#include<ctime>
using namespace std;

template<class K, class V>
class BST;

template<class K, class V>
class TreeNode {
	friend class BST<K, V>;
public:
	TreeNode(const pair<K, V> & e, TreeNode<K, V> * l = nullptr, TreeNode<K, V> * r = nullptr) :element(e), leftChild(l), rightChild(r) {}

private:
	pair<K, V> element;
	TreeNode<K, V> * leftChild;
	TreeNode<K, V> * rightChild;
};

template<class K, class V>
class BST{
public:
	BST() :root(nullptr) {}
	 bool isEmpty() const
	{
		return root == nullptr;
	}
	pair<K, V> * get(const K & k)
	{
		TreeNode<K, V> * current = root;
		search(current, k);//寻找键值对应位置
		return (current == nullptr ? nullptr : &(current->element));//没找到或树为空则current为nullptr，返回空指针，否则返回对应的pair地址
	}
	void insert(const pair<K, V> & e)
	{
		TreeNode<K, V> * current = root;
		TreeNode<K, V> * parent = search(current, e.first);//寻找键值对应节点的父节点
		if (current)//已有键值则替换value
			current->element.second = e.second;
		else//无该键值则新建
		{
			current = new TreeNode<K, V>(e);
			if (!parent)//树为空，则将新建节点赋给root
				root = current;
			else if (e.first < parent->element.first)//将父节点的左孩子指向新建节点
				parent->leftChild = current;
			else//将父节点的右孩子指向新建节点
				parent->rightChild = current;
		}
	}
	void remove(const K & k)
	{
		TreeNode<K, V> * current = root;
		TreeNode<K, V> * parent = search(current, k);//寻找键值对应节点的父节点

		if (current)
		{
			if (!(current->leftChild || current->rightChild))//叶子节点
			{
				if (current == root)//被删节点为根节点，且该节点无孩子
				{
					delete root;
					root = nullptr;
				}
				else {
					delete current;
					parent = nullptr;
				}
			}
			else if (!current->leftChild || !current->rightChild)//没左子树或右子树
			{
				if (current == root)//被删节点为根节点，且该节点有单侧子树
				{
					root = (root->leftChild ? root->leftChild : root->rightChild);
					delete current;
				}
				else
				{
					TreeNode<K, V> * toDelete = current;
					current = (current->leftChild ? current->leftChild : current->rightChild);
					if (k < parent->element.first)//更新父节点的孩子指针
						parent->leftChild = current;
					else
						parent->rightChild = current;
					delete toDelete;
				}
			}
			else//找到右子树里的最小节点，替换给定键值节点的值，释放最小节点所占空间
			{
				TreeNode<K, V> * min = current->rightChild;
				while (min->leftChild)//寻找最小节点
					min = min->leftChild;

				parent->element = min->element;//将最小节点的值赋给给定键值节点

				TreeNode<K, V> * minParent = search(current, min->element.first);//寻找最小节点的父节点
				if (parent != minParent)//右子树的根节点不是最小节点,则将最小节点的父节点的相应指针设为空
					minParent->leftChild = min->rightChild;
				else//右子树的根节点是最小节点，则将它的右孩子赋给给定键值节点的右孩子指针
					parent->rightChild = parent->rightChild->rightChild;
				delete min;//释放最小节点的空间				
			}
		}
	}

	void inorderTraverse() const
	{
		inorderTraverse(root);
	}

	int height() const
	{
		return height(root);
	}

	int height(TreeNode<K, V> * node) const
	{
		if (node)
			return max(height(node->leftChild), height(node->rightChild)) + 1;
		else
			return 0;
	}

	~BST()
	{
		deleteNode(root);
	}
private:
	void inorderTraverse(TreeNode<K, V> * node) const
	{
		if (node)
		{
			inorderTraverse(node->leftChild);
			cout <<"("<< node->element.first<<","<<node->element.second << "), ";
			inorderTraverse(node->rightChild);
		}
	}
	void deleteNode(TreeNode<K, V> * node)
	{
		if (node)
		{
			deleteNode(node->leftChild);
			deleteNode(node->rightChild);
			delete node;
		}
	}
	//查找键值，将current设置成符合条件的节点的位置，并返回该节点的父节点指针
	TreeNode<K, V> * search(TreeNode<K, V> * & current, const K & k)
	{
		TreeNode<K, V> * parent = current;
		while (current)
		{
			if (k == current->element.first)
				break;
			else {
				parent = current;
				if (k > current->element.first)//到右子树中找相应位置
					current = current->rightChild;
				else//到左子树中找相应位置
					current = current->leftChild;
			}
		}
		return parent;
	}
	TreeNode<K, V> * root;
};
