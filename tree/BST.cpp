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
		search(current, k);//Ѱ�Ҽ�ֵ��Ӧλ��
		return (current == nullptr ? nullptr : &(current->element));//û�ҵ�����Ϊ����currentΪnullptr�����ؿ�ָ�룬���򷵻ض�Ӧ��pair��ַ
	}
	virtual void insert(const Pair<K, V> & e)
	{
		TreeNode<K, V> * current = root;
		TreeNode<K, V> * parent = search(current, e.key);//Ѱ�Ҽ�ֵ��Ӧ�ڵ�ĸ��ڵ�
		if (current)//���м�ֵ���滻value
			current->element.value = e.value;
		else//�޸ü�ֵ���½�
		{
			current = new TreeNode<K, V>(e);
			if (!parent)//��Ϊ�գ����½��ڵ㸳��root
				root = current;
			else if (e.key < parent->element.key)//�����ڵ������ָ���½��ڵ�
				parent->leftChild = current;
			else//�����ڵ���Һ���ָ���½��ڵ�
				parent->rightChild = current;
		}
	}
	virtual void remove(const K & k)
	{
		TreeNode<K, V> * current = root;
		TreeNode<K, V> * parent = search(current, k);//Ѱ�Ҽ�ֵ��Ӧ�ڵ�ĸ��ڵ�

		if (current)
		{
			if (!(current->leftChild || current->rightChild))//Ҷ�ӽڵ�
			{
				if (current == root)//��ɾ�ڵ�Ϊ���ڵ㣬�Ҹýڵ��޺���
				{
					delete root;
					root = nullptr;
				}
				else {
					delete current;
					parent = nullptr;
				}
			}
			else if (!current->leftChild || !current->rightChild)//û��������������
			{
				if (current == root)//��ɾ�ڵ�Ϊ���ڵ㣬�Ҹýڵ��е�������
				{
					root = (root->leftChild ? root->leftChild : root->rightChild);
					delete current;
				}
				else
				{
					TreeNode<K, V> * toDelete = current;
					current = (current->leftChild ? current->leftChild : current->rightChild);
					if (k < parent->element.key)//���¸��ڵ�ĺ���ָ��
						parent->leftChild = current;
					else
						parent->rightChild = current;
					delete toDelete;
				}
			}
			else//�ҵ������������С�ڵ㣬�滻������ֵ�ڵ��ֵ���ͷ���С�ڵ���ռ�ռ�
			{
				TreeNode<K, V> * min = current->rightChild;
				while (min->leftChild)//Ѱ����С�ڵ�
					min = min->leftChild;

				parent->element = min->element;//����С�ڵ��ֵ����������ֵ�ڵ�

				TreeNode<K, V> * minParent = search(current, min->element.key);//Ѱ����С�ڵ�ĸ��ڵ�
				if (parent != minParent)//�������ĸ��ڵ㲻����С�ڵ�,����С�ڵ�ĸ��ڵ����Ӧָ����Ϊ��
					minParent->leftChild = min->rightChild;
				else//�������ĸ��ڵ�����С�ڵ㣬�������Һ��Ӹ���������ֵ�ڵ���Һ���ָ��
					parent->rightChild = parent->rightChild->rightChild;
				delete min;//�ͷ���С�ڵ�Ŀռ�				
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
	//���Ҽ�ֵ����current���óɷ��������Ľڵ��λ�ã������ظýڵ�ĸ��ڵ�ָ��
	TreeNode<K, V> * search(TreeNode<K, V> * & current, const K & k)
	{
		TreeNode<K, V> * parent = current;
		while (current)
		{
			if (k == current->element.key)
				break;
			else {
				parent = current;
				if (k > current->element.key)//��������������Ӧλ��
					current = current->rightChild;
				else//��������������Ӧλ��
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
	//P296-1����
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
	//P296-2����
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