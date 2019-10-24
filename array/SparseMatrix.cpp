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
	//��ָ���ı��ļ���ȡϡ��������Ԫ���ʾ
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
		//����stringstream�������ַ����Զ�ת���������ͺ�
		//������Ԫ�����ÿ��Ԫ��
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
	//��rowSize��rowStart��Ϊһ������Ŀ���ת�ú���
	SparseMatrix fastTranspose()
	{
		SparseMatrix b(cols, rows, terms);
		if (terms > 0)
		{
			int * rowStart = new int[cols];
			fill(rowStart, rowStart + cols, 0);
			//��ͳ��ԭ����ÿһ�еķ���Ԫ�ظ���������Ԫ������Ϊ������
			//�ۼӵ�rowStart����Ķ�Ӧλ��
			for (int i = 0; i < terms; i++)
				rowStart[smArray[i].col]++;
			//rowStart[i]�ڱ�����ֵǰ�����i�еķ���Ԫ�ظ�������ֵ������i����λ����Ԫ����
			//�µ�MatrixTerm�����е�λ��
			//count�ڱ�����ֵǰ������ǵ�i-1�еķ���Ԫ�ظ�������ֵ������i�еķ���Ԫ�ظ���
			//temp�����ݴ��i�еķ���Ԫ�ظ�����ֵ����ΪrowStart[i]��count�໥����Է��ĸ�ֵ
			int count = rowStart[0],temp;
			rowStart[0] = 0;//ԭ�����һ�е���λ����Ԫ��ת�ú�����λ���µ�MatrixTerm���鿪ͷλ�ô�
			for (int i = 1; i < cols; i++)
			{
				temp = rowStart[i];
				rowStart[i] = rowStart[i - 1] + count;
				count = temp;
			}
			//����ԭMatrixArray���飬ÿһ��Ԫ������������������������еĶ�Ӧλ�ã�
			//Ȼ��һһ��ֵ
			for (int i = 0; i < terms; i++)
			{
				int j = rowStart[smArray[i].col];
				b.smArray[j].row = smArray[i].col;
				b.smArray[j].col = smArray[i].row;
				b.smArray[j].value = smArray[i].value;
				rowStart[smArray[i].col]++;//������һ��Ԫ��λ����b.smArray�����е�λ��
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
	sm.readData("D:/Code/Data Structure/data.txt");//�ļ���ȡ·����Ҫ�޸�
	sm.print();
	cout << "after transpose" << endl;
	SparseMatrix sm2=sm.transpose();
	sm2.print();
	cout << "after fastTranspose" << endl;
	SparseMatrix sm3 = sm.fastTranspose();
	sm3.print();

	system("pause");
}