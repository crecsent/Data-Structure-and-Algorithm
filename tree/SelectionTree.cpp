#include<iostream>
#include<climits>
using namespace std;
class WinnerTree {
public:
	WinnerTree(int k, int * recordArray)
	{
		if (!recordArray)
		{
			cout << "invalid records" << endl;
			return;
		}
		else
		{
			numOfRecord = k;
			//索引0不用，1到k-1为存储的是胜出比赛的值在records数组里的索引，k到2*k-1存的是records数组的顺序索引
			winners = new int[k * 2];
			records = new int[k];//原数组的副本
			for (int i = 0; i < k; i++)
				records[i] = recordArray[i];
			for (int i = k; i < 2 * k; i++)
				winners[i] = i - k;
			build();//计算第一轮比赛结果
		}
	}
	void build()
	{
		for (int i = numOfRecord - 1; i >= 1; i--)
			winners[i] = (records[winners[2 * i]] < records[winners[2 * i + 1]] ? winners[2 * i] : winners[2 * i + 1]);
	}
	int next()
	{
		int minIndex = winners[1];//最小值在原数组中的索引
		int minTreeIndex = numOfRecord + minIndex;//最小值在胜者树中的索引
		int toUpdate = minTreeIndex / 2;

		records[minIndex] = INT_MAX;

		while (toUpdate != 0)
		{
			winners[toUpdate] = (records[winners[2 * toUpdate]] < records[winners[2 * toUpdate + 1]] ?
				winners[2 * toUpdate] : winners[2 * toUpdate + 1]);
			toUpdate /= 2;
		}
		return minIndex;
	}
private:
	int numOfRecord;
	int * records;
	int * winners;

};

class LoserTree {
public:
	LoserTree(int k, int * recordArray)
	{
		if (!recordArray || k < 1)
		{
			cout << "invalid records" << endl;
			return;
		}
		else
		{
			numOfRecord = k;
			//索引0不用，1到k-1为存储的是胜出比赛的值在records数组里的索引，k到2*k-1存的是records数组的顺序索引
			losers = new int[k * 2];
			records = new int[k];//原数组的副本
			for (int i = 0; i < k; i++)
				records[i] = recordArray[i];
			for (int i = k; i < 2 * k; i++)
				losers[i] = i - k;
			build();//计算第一轮比赛结果
		}
	}
	void build()
	{
		for (int i = numOfRecord - 1; i >= 1; i--)
			losers[i] = (records[losers[2 * i]] < records[losers[2 * i + 1]] ? losers[2 * i] : losers[2 * i + 1]);
		losers[0] = losers[1];
		for (int i = 1; i < numOfRecord; i++)
			losers[i] = (losers[i] == losers[2 * i] ? losers[2 * i + 1] : losers[2 * i]);
		cout << "loser tree after first build:" << endl;
		for (int i = 0; i < 2*numOfRecord; i++)
			cout <<  records[losers[i]] << " ";
	}

	int next()
	{
		int minIndex = losers[0];//最小值在原数组中的位置
		int minTreeIndex = numOfRecord + minIndex;//最小值在losers数组中的位置
		int lastWinner = losers[minTreeIndex / 2];//最小值对应的败者在原数组中的位置
		int toUpdate = minTreeIndex / 4;
		records[minIndex] = INT_MAX;
		while (toUpdate != 0)
		{
			if (records[lastWinner] > records[losers[toUpdate]])//更新败者
			{
				int temp = lastWinner;
				lastWinner = losers[toUpdate];
				losers[toUpdate] = temp;
			}
			toUpdate /= 2;
		}
		losers[0] = lastWinner;//设置新找出的最小值
		return minIndex;
	}
private:
	int numOfRecord;
	int * records;
	int * losers;
};

int main()
{
	const int size = 20;
	int * rec = new int[size];
	cout << "The unsorted array: ";
	for (int i = 0; i <size; i++)
	{
		rec[i] = rand()%50;
		cout << rec[i] <<" ";
	}
	cout << endl;
	WinnerTree wt(size, rec);
	LoserTree lt(size, rec);
	cout << "\nuse winner tree to sort :" << endl;
	for (int i = 0; i < size; i++)
		cout << rec[wt.next()] << " ";
	cout << "\nuse loser tree to sort :" << endl;
	for (int i = 0; i < size; i++)
		cout << rec[lt.next()] << " ";
	system("pause");
}