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
	//因为该地图着色问题每给一块新区域着色都要检查是否与相邻区域颜色相同，所以要访问栈内部的元素
	//标准的栈不能访问栈内部的元素，只能访问栈顶。这里权且用该函数判断已有色块与候选色块是否冲突
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

typedef vector<vector<unsigned int>> UIntVector2D;//用于动态创建二维数组
class MapPainting
{
public:
	void coloring(int limit)
	{
		int currentBlock = 1, currentColor = 1, i = 0;
		bool suc = false;
		mapColor.push(currentColor);//给第一块区域着色
		while (i++ < limit)
		{
			currentColor = 1;
			while (isConflicted(currentBlock, currentColor))//检查要给currentBlock上的色是否会造成与它相邻的已上色区块的颜色冲突
			{
				currentColor++;//冲突了则用下一个颜色
				while (currentColor >= 5)//若四个颜色都有冲突，无法给currentBlock上色，则将上一块区域重新着色
				{
					currentBlock--;
					currentColor = mapColor.Top()+1;//上一块区域的颜色值加1表示要填上的新颜色。若值大于颜色数，则会将上上块区域重新着色
					mapColor.pop();
				}
			}
			mapColor.push(currentColor);
			currentBlock++;

			if (mapColor.size() == size)//说明所有区域都被成功着色了
			{
				suc = true;
				break;
			}
			else if (mapColor.size() == 1)//size值为1说明上面的着色发生着色冲突且一直回退到了第一块区域的着色，
			{//那么不需要再考虑第一块区域着其它色的情况也可以推出：整张地图没有可行的着色方案
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
			//假如该块与另一块区域相连且通过查看栈发现颜色相同，则发生冲突
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