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
		search(current, k);//Ѱ�Ҽ�ֵ��Ӧλ��
		return (current == nullptr ? nullptr : &(current->element));//û�ҵ�����Ϊ����currentΪnullptr�����ؿ�ָ�룬���򷵻ض�Ӧ��pair��ַ
	}
	void insert(const pair<K, V> & e)
	{
		TreeNode<K, V> * current = root;
		TreeNode<K, V> * parent = search(current, e.first);//Ѱ�Ҽ�ֵ��Ӧ�ڵ�ĸ��ڵ�
		if (current)//���м�ֵ���滻value
			current->element.second = e.second;
		else//�޸ü�ֵ���½�
		{
			current = new TreeNode<K, V>(e);
			if (!parent)//��Ϊ�գ����½��ڵ㸳��root
				root = current;
			else if (e.first < parent->element.first)//�����ڵ������ָ���½��ڵ�
				parent->leftChild = current;
			else//�����ڵ���Һ���ָ���½��ڵ�
				parent->rightChild = current;
		}
	}
	void remove(const K & k)
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
					if (k < parent->element.first)//���¸��ڵ�ĺ���ָ��
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

				TreeNode<K, V> * minParent = search(current, min->element.first);//Ѱ����С�ڵ�ĸ��ڵ�
				if (parent != minParent)//�������ĸ��ڵ㲻����С�ڵ�,����С�ڵ�ĸ��ڵ����Ӧָ����Ϊ��
					minParent->leftChild = min->rightChild;
				else//�������ĸ��ڵ�����С�ڵ㣬�������Һ��Ӹ���������ֵ�ڵ���Һ���ָ��
					parent->rightChild = parent->rightChild->rightChild;
				delete min;//�ͷ���С�ڵ�Ŀռ�				
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
	//���Ҽ�ֵ����current���óɷ��������Ľڵ��λ�ã������ظýڵ�ĸ��ڵ�ָ��
	TreeNode<K, V> * search(TreeNode<K, V> * & current, const K & k)
	{
		TreeNode<K, V> * parent = current;
		while (current)
		{
			if (k == current->element.first)
				break;
			else {
				parent = current;
				if (k > current->element.first)//��������������Ӧλ��
					current = current->rightChild;
				else//��������������Ӧλ��
					current = current->leftChild;
			}
		}
		return parent;
	}
	TreeNode<K, V> * root;
};
