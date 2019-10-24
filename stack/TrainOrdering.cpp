#include<iostream>
#include<stack>
using namespace std;
//对n辆火车，进出轨道操作各有n次，合起来为2n个操作。令1为进轨道操作，-1为出轨道操作，用长为2n的track数组表示操作的顺序
//找到所有可能的火车排序实际上就是找到所有合法的操作顺序。除第一步操作必为进轨道外，其它步的操作初始都为出轨道，在确定下一步
//操作前，总是调用validOperation(index,operation)判断操作的合法性，合法则把操作赋到track对应位置处，继续下一步操作的确定；非法则回溯
//到上一步操作，上一步操作若为出轨道，则判断上一步操作是否能为进轨道，能则修改track对应位置的元素值并继续完成后面操作的确定；不能则
//再回溯到上上步的操作，重复上述步骤。如果最后一步操作也被确定下来了，则说明已找到一个可能排序，那么打印该排序，然后回溯，
//修改之前的操作，寻找其它可能排序。如果某次回溯一直回到了第一步操作，则说明所有的可能排序都被找到了，那么退出函数。
class TrainOrdering 
{
public:
	TrainOrdering(int n) :operationCount(2*n)
	{
		track = new char[operationCount];
	}
	void ordering()
	{
		char op = -1;//1为进轨道操作，-1为出轨道操作
		int index = 1;
		track[0] = 1;//第一步操作总为进轨道
		bool end = false;//判断是否已找到所有可能排序
		int validOrder = 0;//总的可能排序数
		while (true)
		{
			//op>1这个条件，是为了当找到某个可能排序后，在不调用validOperation的情况下仍能进入该循环体里的回溯过程而设置的
			while (op>1||!validOperation(index, op))
			{
				op += 2;//原操作为出轨道（-1）无效，则尝试进轨道（1）；原操作为进轨道（1）无效，则回溯
				while (op > 1&&index!=0)
				{
					op = track[--index] + 2;
				}
				if (index == 0)//说明所有的可能排序都被找到了
				{
					end = true;
					break;
				}
			}
			if (end)
			{
				cout << "All possible " << validOrder << " orders have been found." << endl;
				break;
			}
			track[index] = op;
			if (index == operationCount - 1)//说明找到了某个可能排序，打印它
			{
				validOrder++;
				printOrder();
				op += 2;
			}
			else
			{
				index++;
				op = -1;
			}
		}
	}
	void printOrder()
	{
		int nextTrain = 1;
		for (int i = 0; i < operationCount; i++)
		{
			if (track[i] == 1)//火车进轨道
				order.push(nextTrain++);
			else
			{
				cout << order.top() << " ";//火车出轨道
				order.pop();
			}
		}
		cout << endl;
	}
private:
	bool validOperation(int index, char op)
	{
		char sum = 0;
		for (int i = 0; i < index; i++)
			sum += track[i];

		if ((index - sum) / 2 + sum == operationCount / 2)//说明所有的火车都已进过轨道了
			return op == -1;//则只有出轨道操作是有效的
		else if (sum == 0)//说明轨道中无车
			return op == 1;//则只有进轨道操作是有效的
		return true;
	}
	int operationCount;
	stack<int> order;//模拟火车进出轨道
	char * track;//存放火车进出轨道操作的顺序
};

int main()
{
	int n;
	cout << "Enter the train number: " << endl;
	cin >> n;
	TrainOrdering to(n);
	to.ordering();
	system("pause");
}