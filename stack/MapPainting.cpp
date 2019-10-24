#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<iomanip>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()
	{
		capacity = 8;
		p = new T[capacity];
		top = -1;
	}
	bool empty() { return top == -1; }
	int size() { return top + 1; }
	void push(T & t)
	{
		if (++top == capacity)
			resize();
		p[top] = t;
	}
	void pop()
	{
		if (empty())
			cout << "Empty stack! Nothing to pop!" << endl;
		else
			top--;
	}
	T Top()
	{
		if (empty())
			cout << "Empty stack!" << endl;
		else
			return p[top];
	}
	//��Ϊ�õ�ͼ��ɫ����ÿ��һ����������ɫ��Ҫ����Ƿ�������������ɫ��ͬ������Ҫ����ջ�ڲ���Ԫ��
	//��׼��ջ���ܷ���ջ�ڲ���Ԫ�أ�ֻ�ܷ���ջ��������Ȩ���øú����ж�����ɫ�����ѡɫ���Ƿ��ͻ
	bool equals(int index, T & t)
	{
		if (index > top || index < 0)
		{
			cout << "Invalid index." << endl;
			return false;
		}
		else
			return p[index] == t;
	}
	void resize()
	{
		capacity *= 2;
		T *temp = new T[capacity];
		for (int i = 0; i < (capacity >> 2); i++)
			temp[i] = p[i];
		delete[]p;
		p = temp;
	}
private:
	int top;
	int capacity;
	T *p;
};

typedef vector<vector<unsigned int>> UIntVector2D;//���ڶ�̬������ά����
class MapPainting
{
public:
	void coloring(int limit)
	{
		int currentBlock = 1, currentColor = 1, i = 0;
		bool suc = false;
		mapColor.push(currentColor);//����һ��������ɫ
		while (i++ < limit)
		{
			currentColor = 1;
			while (isConflicted(currentBlock, currentColor))//���Ҫ��currentBlock�ϵ�ɫ�Ƿ������������ڵ�����ɫ�������ɫ��ͻ
			{
				currentColor++;//��ͻ��������һ����ɫ
				while (currentColor >= 5)//���ĸ���ɫ���г�ͻ���޷���currentBlock��ɫ������һ������������ɫ
				{
					currentBlock--;
					currentColor = mapColor.Top()+1;//��һ���������ɫֵ��1��ʾҪ���ϵ�����ɫ����ֵ������ɫ������Ὣ���Ͽ�����������ɫ
					mapColor.pop();
				}
			}
			mapColor.push(currentColor);
			currentBlock++;

			if (mapColor.size() == size)//˵���������򶼱��ɹ���ɫ��
			{
				suc = true;
				break;
			}
			else if (mapColor.size() == 1)//sizeֵΪ1˵���������ɫ������ɫ��ͻ��һֱ���˵��˵�һ���������ɫ��
			{//��ô����Ҫ�ٿ��ǵ�һ������������ɫ�����Ҳ�����Ƴ������ŵ�ͼû�п��е���ɫ����
				suc = false;
				break;
			}	
		}
		cout << (suc ? "coloring successfully!" : "no solution.") << endl;
		if (suc)
		{
			for (int i = mapColor.size(); i >0; i--)
			{
				cout << "block " << i << " is painted color: " << mapColor.Top() << endl;
				mapColor.pop();
			}
		}
	}
	bool isConflicted(int blockIndex, int color)
	{
		for (int i = 0; i < blockIndex; i++)
		{
			//����ÿ�����һ������������ͨ���鿴ջ������ɫ��ͬ��������ͻ
			if (relation[blockIndex][i] != 0 && mapColor.equals(i, color))
				return true;
		}
		return false;
	}
private:
	static const int size = 7;
	int relation[size][size] = { 
	{0,1,1,1,1,1,0},
	{1,0,0,0,0,1,0},
	{1,0,0,1,1,0,0},
	{1,0,1,0,1,1,0},
	{1,0,1,1,0,1,0},
	{1,1,0,1,1,0,0},
	{0,0,0,0,0,0,0}
	};
	Stack<int> mapColor;
};

int main()
{
	MapPainting mp;
	mp.coloring(500);
	system("pause");
}