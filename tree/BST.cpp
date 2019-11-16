#include<iostream>
#include<iomanip>
#include<algorithm>
#include<ctime>
using namespace std;
template<class K, class V>
struct Pair {
	K key;
	V value;
};

template<class K, class V>
class Dictionary {
public:
	virtual bool isEmpty() const = 0;
	virtual Pair<K, V> * get(const K &) = 0;
	virtual void insert(const Pair<K, V> &) = 0;
	virtual void remove(const K &) = 0;
};

template<class K, class V>
class BST;

template<class K, class V>
class TreeNode {
	friend class BST<K, V>;
public:
	TreeNode(const Pair<K, V> & e, TreeNode<K, V> * l = nullptr, TreeNode<K, V> * r = nullptr) :element(e), leftChild(l), rightChild(r) {}

private:
	Pair<K, V> element;
	TreeNode<K, V> * leftChild;
	TreeNode<K, V> * rightChild;
};


template<class K, class V>
class BST :public Dictionary<K, V> {
public:
	BST() :root(nullptr) {}
	virtual bool isEmpty() const
	{
		return root == nullptr;
	}
	virtual Pair<K, V> * get(const K & k)
	{
		TreeNode<K, V> * current = root;
		search(current, k);//寻找键值对应位置
		return (current == nullptr ? nullptr : &(current->element));//没找到或树为空则current为nullptr，返回空指针，否则返回对应的pair地址
	}
	virtual void insert(const Pair<K, V> & e)
	{
		TreeNode<K, V> * current = root;
		TreeNode<K, V> * parent = search(current, e.key);//寻找键值对应节点的父节点
		if (current)//已有键值则替换value
			current->element.value = e.value;
		else//无该键值则新建
		{
			current = new TreeNode<K, V>(e);
			if (!parent)//树为空，则将新建节点赋给root
				root = current;
			else if (e.key < parent->element.key)//将父节点的左孩子指向新建节点
				parent->leftChild = current;
			else//将父节点的右孩子指向新建节点
				parent->rightChild = current;
		}
	}
	virtual void remove(const K & k)
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
					if (k < parent->element.key)//更新父节点的孩子指针
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

				TreeNode<K, V> * minParent = search(current, min->element.key);//寻找最小节点的父节点
				if (parent != minParent)//右子树的根节点不是最小节点,则将最小节点的父节点的相应指针设为空
					minParent->leftChild = min->rightChild;
				else//右子树的根节点是最小节点，则将它的右孩子赋给给定键值节点的右孩子指针
					parent->rightChild = parent->rightChild->rightChild;
				delete min;//释放最小节点的空间				
			}
		}
	}
	
	int height() const
	{
		return height(root);
	}

	int height(TreeNode<K,V> * node) const
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
			if (k == current->element.key)
				break;
			else {
				parent = current;
				if (k > current->element.key)//到右子树中找相应位置
					current = current->rightChild;
				else//到左子树中找相应位置
					current = current->leftChild;
			}
		}
		return parent;
	}
	TreeNode<K, V> * root;
};

int main()
{
	srand(time(0));
	//P296-1测试
	{
		BST<int, int> bst;
		for (int i = 0; i < 10; i++)
			bst.insert(Pair<int, int>({ i,rand() % 20 }));
		for (int i = 0; i < 10; i++)
			cout << bst.get(i)->key << " : " << bst.get(i)->value << endl;

		for (int i = 0; i < 10; i += 2)
			bst.remove(i);
		cout << "after removing key of odd number:" << endl;
		for (int i = 0; i < 10; i++)
		{
			if (bst.get(i) != nullptr)
				cout << bst.get(i)->key << " : " << bst.get(i)->value << endl;
		}
	}
	//P296-2测试
	{
		BST<int, int> bst;
		for (int i = 0; i < 100; i++)
			bst.insert(Pair<int, int>({ rand(),1 }));
		int height = bst.height();
		cout <<"n=100, height="<< height <<", height/logn="<<fixed<<setprecision(4)<<height/(log(100)/log(2))<< endl;
	}
	{
		BST<int, int> bst;
		for (int i = 0; i < 500; i++)
			bst.insert(Pair<int, int>({ rand(),1 }));
		int height = bst.height();
		cout << "n=500, height=" << height << ", height/logn=" << fixed << setprecision(4) << height / (log(500) / log(2)) << endl;
	}
	{
		BST<int, int> bst;
		for (int i = 1; i <= 10; i++)
		{
			for (int j = i * 1000; j > 0; j--)
				bst.insert(Pair<int, int>({ rand(),1 }));
			int height = bst.height();
			cout << "n=" << i * 1000 << ", height=" << height << ", height/logn=" << fixed << setprecision(4) << height / (log(i*1000) / log(2)) << endl;
		}
	}
	system("pause");
}