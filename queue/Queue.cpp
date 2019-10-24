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
		return front == rear&&lastOp;//lastOp为1表示上一步操作为出队列，队列此时为空
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
		if (rear==front&&lastOp==0)//说明队列满了
		{
			T * temp = new T[2 * capacity];
			if (rear!=capacity-1)//说明队列头部元素并不在数组头部
			{
				copy(temp,0, front + 1, capacity - 1);//将原数组右半部分的元素（即队列头部元素）移到新数组开头
				copy(temp,capacity-1-front, 0, rear);//将左半部分元素（队列尾部元素）移到新数组已有元素后面
				rear = capacity - 1;//更新rear在新数组里指向的位置
			}
			else//说明原数组的元素顺序恰好是队列头到尾的顺序
				copy(temp, 0, (front + 1) % capacity, rear);
			capacity *= 2;
			front = capacity - 1;//更新front在新数组里指向的位置

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
			//得到initial有效元素个数
			int count = initial.size();
			for (int i = 1; i <= count; i++)
			{
				if (i % 2 == 1)//从第一个元素开始，每隔一个元素就添加到q1队列中
				{
					q1.push(initial.Front());
					initial.pop();
				}
				else//其余元素添加到q2队列中
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
	bool lastOp;//1表示Pop,0表示Push
	int front;
	int rear;
	int capacity;
};

int main()
{
	Queue<int> s1;
	for (int i = 0; i < 10; i++)
		s1.push(i);
	//按出队列顺序显示s1队列的所有元素
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