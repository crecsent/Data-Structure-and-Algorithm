#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<iomanip>
using namespace std;

struct Move {
	int row, col;//�洢ĳһ�ƶ���������ڵ�ǰλ�õ��в�ֵ���в�ֵ
};

typedef vector<vector<unsigned int>> UIntVector2D;//���ڶ�̬������ά����

class RandomWalk 
{
public:
	RandomWalk(int n, int m):rows(n),cols(m)
	{
		count = new UIntVector2D;
		//���������n,m������ά����ߴ�
		count->resize(rows);
		for (int i = 0; i < rows; i++)
			(*count)[i].resize(cols);
		//��ʼ��8���ƶ������Ӧ���С��в�ֵ
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
				(*count)[i][j] = 0;//ÿ��ѡ��һ����ʼλ�ÿ�ʼһ������ǰ��������λ�õĵ����������Ϊ0
		//������Ч��ʼλ��
		if (startx >= rows || starty >= cols || startx < 0 || starty < 0)
		{
			cout << "Invalid start point! Quit." << endl;
			return;
		}
		//��ʼλ�õĵ���������ȼ�1
		(*count)[startx][starty]++;
		//nextx��nexty�ݴ���nextDir�뵱ǰλ���������һ��λ�ã���Ч��ֱ𸳸�startx��starty����Ч������ѡ��nextDir
		int nextDir, nextx, nexty;
		unsigned int validMove = 0;//�洢��ѭ�������е���Ч���������ų���nextDirʹ����һ��λ����Ч����Щ���
		unsigned int rest = rows * cols - 1;//ʣ��δ���߹��Ĵ�ש���������д�ש�����߹���rest==0Ϊ�棬�˳�ѭ��
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
				if ((*count)[startx][starty]++ == 0)//����λ��û���߹�����ʣ��δ���߹��Ĵ�ש����1
					rest--;
			}
			if (rest == 0)//����λ�ö������߹�һ���ˣ����˳�ѭ������ӡ���
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