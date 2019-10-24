#include<iostream>
using namespace std;

template<class T>
class Queue
{
public:
	Queue(int QueueCapacity = 10):capacity(QueueCapacity),lastOp(1)
	{
		if (capacity < 1)
			throw "Queue capacity must be > 0 ";
		queue = new T[capacity];
		front = rear = capacity-1;
	}

	bool isEmpty() const 
	{ 
		return front == rear&&lastOp;//lastOpΪ1��ʾ��һ������Ϊ�����У����д�ʱΪ��
	}

	T & Front() const
	{
		if (isEmpty())
			throw "Queue is empty. No front element.";
		return queue[(front + 1) % capacity];
	}

	T& Rear() const
	{
		if (isEmpty())
			throws "Queue is empty. No rear element.";
		return queue[rear];
	}

	void push(const T& item)
	{
		if (rear==front&&lastOp==0)//˵����������
		{
			T * temp = new T[2 * capacity];
			if (rear!=capacity-1)//˵������ͷ��Ԫ�ز���������ͷ��
			{
				copy(temp,0, front + 1, capacity - 1);//��ԭ�����Ұ벿�ֵ�Ԫ�أ�������ͷ��Ԫ�أ��Ƶ������鿪ͷ
				copy(temp,capacity-1-front, 0, rear);//����벿��Ԫ�أ�����β��Ԫ�أ��Ƶ�����������Ԫ�غ���
				rear = capacity - 1;//����rear����������ָ���λ��
			}
			else//˵��ԭ�����Ԫ��˳��ǡ���Ƕ���ͷ��β��˳��
				copy(temp, 0, (front + 1) % capacity, rear);
			capacity *= 2;
			front = capacity - 1;//����front����������ָ���λ��

			delete[] queue;
			queue = temp;
		}
		rear = (rear + 1) % capacity;
		queue[rear] = item;
		lastOp = 0;
	}

	void pop()
	{
		if (isEmpty())
			throw "Queue is empty. Cannot delete.";
		front = (front + 1) % capacity;
		queue[front].~T();
		lastOp = 1;
	}

	int size() const
	{
		return rear - front + (front < rear||isEmpty() ? 0 : capacity);
	}

	static void split(Queue & initial, Queue & q1, Queue & q2)
	{
		if (!initial.isEmpty())
		{
			//�õ�initial��ЧԪ�ظ���
			int count = initial.size();
			for (int i = 1; i <= count; i++)
			{
				if (i % 2 == 1)//�ӵ�һ��Ԫ�ؿ�ʼ��ÿ��һ��Ԫ�ؾ���ӵ�q1������
				{
					q1.push(initial.Front());
					initial.pop();
				}
				else//����Ԫ����ӵ�q2������
				{
					q2.push(initial.Front());
					initial.pop();
				}
			}
		}
	}

private:
	void copy(T * q1, int q1Start, int start, int end)
	{
		for (int i = q1Start,j=start; j <= end; i++,j++)
		{
			q1[i] = queue[j];
		}
	}
	T * queue;
	bool lastOp;//1��ʾPop,0��ʾPush
	int front;
	int rear;
	int capacity;
};

int main()
{
	Queue<int> s1;
	for (int i = 0; i < 10; i++)
		s1.push(i);
	//��������˳����ʾs1���е�����Ԫ��
	cout << "s1: " << endl;
	for (int i = s1.size(); i >0; i--)
	{
		cout << s1.Front() << " ";
		s1.pop();
	}
	for (int i = 0; i < 10; i++)
		s1.push(i);
	Queue<int> s2, s3;
	cout << "\nspliting s1 to s2 and s3 ..." << endl;
	Queue<int>::split(s1, s2, s3);
	cout << " s2 after split" << endl;
	for (int i = s2.size(); i > 0; i--)
	{
		cout << s2.Front() << " ";
		s2.pop();
	}
	cout << " \ns3 after split" << endl;
	for (int i = s3.size(); i > 0; i--)
	{
		cout << s3.Front() << " ";
		s3.pop();
	}
	system("pause");
}