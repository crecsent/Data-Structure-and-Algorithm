#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

class SparseMatrix;
class MatrixTerm {
	friend class SparseMatrix;
private: 
	int row, col, value;
};
class SparseMatrix
{
public:
	SparseMatrix(int r, int c, int t):rows(r),cols(c),terms(t),capacity(t),smArray(new MatrixTerm[t]){}
	//从指定文本文件读取稀疏矩阵的三元组表示
	void readData(string path)
	{
		ifstream in;
		in.open(path, ios::in);
		if (!in.is_open())
		{
			cout << "open file failed" << endl;
			return;
		}
		string str;
		stringstream ss;
		int i = 0;
		//利用stringstream将输入字符串自动转换数据类型后
		//赋给三元数组的每个元素
		while (getline(in, str))
		{
			ss.clear();
			ss << str;
			ss >> smArray[i].row >> smArray[i].col>> smArray[i].value;
			i++;
		}
		in.close();
	}
	SparseMatrix transpose()
	{
		SparseMatrix b(cols, rows, terms);
		if (terms > 0)
		{
			int currentB = 0;
			for (int c = 0; c < cols; c++)
				for (int i = 0; i < terms; i++)
				{
					if (smArray[i].col == c)
					{
						b.smArray[currentB].row = smArray[i].col;
						b.smArray[currentB].col = smArray[i].row;
						b.smArray[currentB].value = smArray[i].value;
						currentB++;
					}
				}
		}

		return b;
	}
	//将rowSize与rowStart合为一个数组的快速转置函数
	SparseMatrix fastTranspose()
	{
		SparseMatrix b(cols, rows, terms);
		if (terms > 0)
		{
			int * rowStart = new int[cols];
			fill(rowStart, rowStart + cols, 0);
			//先统计原矩阵每一列的非零元素个数，并以元素列数为索引，
			//累加到rowStart数组的对应位置
			for (int i = 0; i < terms; i++)
				rowStart[smArray[i].col]++;
			//rowStart[i]在被赋新值前代表第i列的非零元素个数，赋值后代表第i列首位非零元素在
			//新的MatrixTerm数组中的位置
			//count在被赋新值前代表的是第i-1列的非零元素个数，赋值后代表第i列的非零元素个数
			//temp用来暂存第i列的非零元素个数的值，因为rowStart[i]和count相互参与对方的赋值
			int count = rowStart[0],temp;
			rowStart[0] = 0;//原矩阵第一列的首位非零元素转置后总是位于新的MatrixTerm数组开头位置处
			for (int i = 1; i < cols; i++)
			{
				temp = rowStart[i];
				rowStart[i] = rowStart[i - 1] + count;
				count = temp;
			}
			//遍历原MatrixArray数组，每一个元素用它的列数查得在新数组中的对应位置，
			//然后一一赋值
			for (int i = 0; i < terms; i++)
			{
				int j = rowStart[smArray[i].col];
				b.smArray[j].row = smArray[i].col;
				b.smArray[j].col = smArray[i].row;
				b.smArray[j].value = smArray[i].value;
				rowStart[smArray[i].col]++;//该列下一个元素位置在b.smArray数组中的位置
			}
			delete[] rowStart;
		}
		return b;
	}
	void print()
	{
		for (int i = 0; i < terms; i++)
			cout << smArray[i].row << " " << smArray[i].col << " " << smArray[i].value << endl;
	}
private:
	int rows, cols, terms, capacity;
	MatrixTerm * smArray;
};


int main()
{
	SparseMatrix sm(7, 7, 8);
	sm.readData("D:/Code/Data Structure/data.txt");//文件读取路径需要修改
	sm.print();
	cout << "after transpose" << endl;
	SparseMatrix sm2=sm.transpose();
	sm2.print();
	cout << "after fastTranspose" << endl;
	SparseMatrix sm3 = sm.fastTranspose();
	sm3.print();

	system("pause");
}