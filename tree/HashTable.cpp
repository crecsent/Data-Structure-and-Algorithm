#include<iostream>
#include<string>
#include<algorithm>
#include"bst.cpp"
using namespace std;

template<class K,class V>
class HashTable
{
public:
	HashTable(int d) {
		if (d<=0||d%2==0) 
		{
			cout << "The input divisor is not odd. Set to default divisor 29";
			d = 29;
		}
		divisor = d;
		capacity = divisor;
		size = 0;
		hashTable = new pair<K, V>[divisor];
		occupied = new bool[divisor] {};
	}

	void insert(const K key,const V value)
	{	
		int index = mappingFunction(key);
		if (!occupied[index])
		{
			hashTable[index].first = key;
			hashTable[index].second = value;
			occupied[index] = true;
			size++;
			loadFactor = size /(double) capacity;//更新装填因子
			if (loadFactor >= THRESHOLD)//数组加倍 
				resize();
		}
		else if (hashTable[index].first == key)//关键字相同则覆盖原值
			hashTable[index].second = value;
		else{//冲突则将新数据插入到二叉搜索树
			pair<K, V> e(key, value);
			bst.insert(e);		
		}
	}

	void remove(const K key)
	{
		int index = mappingFunction(key);
		if (occupied[index]&&hashTable[index].first == key)
		{
			occupied[index] = false;
			size--;
			loadFactor = size/(double)capacity;
		}
		else
			bst.remove(key);
	}
	
	V search(const K key) const
	{
		int index = mappingFunction(key);
		if (occupied[index] && hashTable[index].first == key)
			return hashTable[index].second;
		else
			return bst.get(key)->second;
	}

	int mappingFunction(const K key) const
	{
		return key % divisor;
	}
	//数组加倍，并将原数组中的值根据新的映射关系一一插入到新数组里
	void resize()
	{
		cout << "resizing...." << endl;
		pair<K, V> * tempHT = new pair<K, V>[2 * capacity + 1];
		bool * tempOcp = new bool[2 * capacity + 1]{};
		divisor = 2 * divisor + 1;
		for (int i = 0; i < capacity; i++)
		{
			if (occupied[i])
			{
				int index = mappingFunction(hashTable[i].first);
				if (!tempOcp[i])
				{
					tempHT[i] = hashTable[i];
					tempOcp[i] = true;
				}
				else
					bst.insert(hashTable[i]);
			}
		}
		capacity = divisor;
		delete[] hashTable;
		delete[] occupied;
		hashTable = tempHT;
		occupied = tempOcp;
		loadFactor = size / (double)capacity;
	}

	void print() const
	{
		cout << "current divisor:" << divisor << endl;
		for (int i = 0; i < capacity; i++)
		{
			if (occupied[i])
				cout << "("<<hashTable[i].first<<","<<hashTable[i].second<< "), ";
		}
		cout << "\npairs in bst:\n";
		bst.inorderTraverse();	
		cout <<"\n"<< endl;
	}
private:
	int divisor;
	int capacity;
	int size;
	double loadFactor;
	const double THRESHOLD = 0.8;
	pair<K, V> * hashTable;
	bool * occupied;
	BST<K, V> bst;
};

int main()
{
	HashTable<int,string> ht(9);
	cout << "inserting 0 to 9 into hashTable..." << endl;
	for (int i = 0; i < 10; i++)
		ht.insert(i,to_string(i));
	cout << "hashTable before insert 19" << endl;
	ht.print();
	ht.insert(19, "19");
	cout << "hashTable after insert 19" << endl;
	ht.print();
	ht.remove(0);
	cout << "hashTable after remove 0" << endl;
	ht.print();

	ht.remove(19);
	cout << "hashTable after remove 19" << endl;
	ht.print();
	system("pause");
}