#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<iomanip>
using namespace std;

struct Move {
	int row, col;//存储某一移动方向相对于当前位置的行差值与列差值
};

typedef vector<vector<unsigned int>> UIntVector2D;//用于动态创建二维数组

class RandomWalk 
{
public:
	RandomWalk(int n, int m):rows(n),cols(m)
	{
		count = new UIntVector2D;
		//根据输入的n,m调整二维数组尺寸
		count->resize(rows);
		for (int i = 0; i < rows; i++)
			(*count)[i].resize(cols);
		//初始化8个移动方向对应的行、列差值
		move[0].row = -1; move[0].col = 1;
		move[1].row = 0; move[1].col = 1;
		move[2].row = 1; move[2].col = 1;
		move[3].row = 1; move[3].col = 0;
		move[4].row = 1; move[4].col = -1;
		move[5].row = 0; move[5].col = -1;
		move[6].row = -1; move[6].col = -1;
		move[7].row = -1; move[7].col = 0;
	}
	void walking(unsigned int limit,int startx,int starty)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				(*count)[i][j] = 0;//每次选定一个起始位置开始一轮漫步前，将所有位置的到达次数重置为0
		//处理无效起始位置
		if (startx >= rows || starty >= cols || startx < 0 || starty < 0)
		{
			cout << "Invalid start point! Quit." << endl;
			return;
		}
		//起始位置的到达次数首先加1
		(*count)[startx][starty]++;
		//nextx和nexty暂存由nextDir与当前位置算出的下一步位置，有效则分别赋给startx与starty，无效则重新选择nextDir
		int nextDir, nextx, nexty;
		unsigned int validMove = 0;//存储总循环次数中的有效步数，即排除了nextDir使得下一步位置无效的那些情况
		unsigned int rest = rows * cols - 1;//剩余未被走过的瓷砖数，当所有瓷砖都被走过后，rest==0为真，退出循环
		for (unsigned int i = 0; i < limit; i++)
		{
			nextDir = rand() % 8;
			nextx = startx + move[nextDir].row;
			nexty = starty + move[nextDir].col;
			if (nextx < rows&&nextx >= 0 && nexty < cols&&nexty >= 0)
			{
				validMove++;
				startx = nextx;
				starty = nexty;
				if ((*count)[startx][starty]++ == 0)//若该位置没被走过，则剩余未被走过的瓷砖数减1
					rest--;
			}
			if (rest == 0)//所有位置都至少走过一次了，则退出循环，打印结果
				break;
		}
		cout << "All tiles have been reached? " << (rest == 0 ? true : false) << endl;
		cout << "valid move times: " << validMove << endl;
		printCountArray();
	}
	void printCountArray()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				cout << setw(3) << (*count)[i][j];
			cout << "\n";
		}
	}
private:
	int rows;
	int cols;
	UIntVector2D * count;
	Move move[8];
};

int main()
{
	srand(time(0));
	int n, m, x, y;
	cout << "input the n and m:" << endl;
	cin >> n >> m;
	cout << " input the start place x and y:" << endl;
	cin >> x >> y;
	RandomWalk rw(n, m);
	rw.walking(50000, x, y);
	system("pause");
}