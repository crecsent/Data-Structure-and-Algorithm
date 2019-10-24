#include<iostream>
#include<stack>
using namespace std;
//��n���𳵣����������������n�Σ�������Ϊ2n����������1Ϊ�����������-1Ϊ������������ó�Ϊ2n��track�����ʾ������˳��
//�ҵ����п��ܵĻ�����ʵ���Ͼ����ҵ����кϷ��Ĳ���˳�򡣳���һ��������Ϊ������⣬�������Ĳ�����ʼ��Ϊ���������ȷ����һ��
//����ǰ�����ǵ���validOperation(index,operation)�жϲ����ĺϷ��ԣ��Ϸ���Ѳ�������track��Ӧλ�ô���������һ��������ȷ�����Ƿ������
//����һ����������һ��������Ϊ����������ж���һ�������Ƿ���Ϊ������������޸�track��Ӧλ�õ�Ԫ��ֵ��������ɺ��������ȷ����������
//�ٻ��ݵ����ϲ��Ĳ������ظ��������衣������һ������Ҳ��ȷ�������ˣ���˵�����ҵ�һ������������ô��ӡ������Ȼ����ݣ�
//�޸�֮ǰ�Ĳ�����Ѱ�����������������ĳ�λ���һֱ�ص��˵�һ����������˵�����еĿ������򶼱��ҵ��ˣ���ô�˳�������
class TrainOrdering 
{
public:
	TrainOrdering(int n) :operationCount(2*n)
	{
		track = new char[operationCount];
	}
	void ordering()
	{
		char op = -1;//1Ϊ�����������-1Ϊ���������
		int index = 1;
		track[0] = 1;//��һ��������Ϊ�����
		bool end = false;//�ж��Ƿ����ҵ����п�������
		int validOrder = 0;//�ܵĿ���������
		while (true)
		{
			//op>1�����������Ϊ�˵��ҵ�ĳ������������ڲ�����validOperation����������ܽ����ѭ������Ļ��ݹ��̶����õ�
			while (op>1||!validOperation(index, op))
			{
				op += 2;//ԭ����Ϊ�������-1����Ч�����Խ������1����ԭ����Ϊ�������1����Ч�������
				while (op > 1&&index!=0)
				{
					op = track[--index] + 2;
				}
				if (index == 0)//˵�����еĿ������򶼱��ҵ���
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
			if (index == operationCount - 1)//˵���ҵ���ĳ���������򣬴�ӡ��
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
			if (track[i] == 1)//�𳵽����
				order.push(nextTrain++);
			else
			{
				cout << order.top() << " ";//�𳵳����
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

		if ((index - sum) / 2 + sum == operationCount / 2)//˵�����еĻ𳵶��ѽ��������
			return op == -1;//��ֻ�г������������Ч��
		else if (sum == 0)//˵��������޳�
			return op == 1;//��ֻ�н������������Ч��
		return true;
	}
	int operationCount;
	stack<int> order;//ģ��𳵽������
	char * track;//��Ż𳵽������������˳��
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