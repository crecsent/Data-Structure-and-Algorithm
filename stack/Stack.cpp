#include<iostream>
using namespace std;

template<class T>
class Stack
{
public:
	friend ostream & operator<<(ostream& out, Stack& s)
	{
		cout << "From top to bottom:" << endl;
		for (int i = s.topIndex; i >= 0; i--)
		{
			cout << s.stack[i] << " ";
		}
		cout << endl;
		return out;
	}
	Stack(int stackCapacity = 10) :capacity(stackCapacity)
	{
		if (capacity < 1)
			throw "stack capacity must be > 0";
		stack = new T[capacity];
		topIndex = -1;
	}
	bool isEmpty() const { return topIndex == -1; }
	T& top() const
	{
		if (isEmpty())
			throw "Stack is empty.";
		return stack[topIndex];
	}
	void push(const T& item)
	{
		if (++topIndex == capacity)
			resize();
		stack[topIndex] = item;
	}
	void pop()
	{
		if (isEmpty())
			throw "Stack is empty. Cannot delete.";
		stack[topIndex--].~T();
	}
	static void split(Stack & initial,Stack & s1, Stack & s2)
	{
		Stack temp(initial.topIndex + 1);//因为原栈中元素的顺序在另两个栈中不应该改变，而栈又是先进后出的数据结构，所以
		//需要一个临时栈把栈中的元素先倒序拿出来，再正序放入另两个栈里
		int half1 = (initial.topIndex +1) / 2;
		int half2 = initial.topIndex + 1 - half1;
		for (int i = 0; i < temp.capacity; i++)
		{
			temp.push(initial.top());
			initial.pop();
		}
		for (int i = 0; i < half1; i++)
		{
			s1.push(temp.top());
			temp.pop();
		}
		for (int i = 0; i < half2; i++)
		{
			s2.push(temp.top());
			temp.pop();
		}
	}
	static void combine(Stack & s1,Stack & s2)
	{
		Stack temp(s2.topIndex + 1);
		for (int i = 0; i < temp.capacity; i++)
		{
			temp.push(s2.top());
			s2.pop();
		}
		for (int i = 0; i < temp.capacity; i++)
		{
			s1.push(temp.top());
			temp.pop();
		}
	}
private:
	void resize()
	{
		capacity *= 2;
		T * temp = new T[capacity];
		for (int i = 0; i < (capacity / 2); i++)
			temp[i] = stack[i];
		delete[] stack;
		stack = temp;
	}
	T * stack;
	int topIndex;
	int capacity;
};

int main()
{
	Stack<int> s1(4);
	for (int i = 0; i < 10; i++)
		s1.push(i);
	cout << "s1 before split:" << s1;
	Stack<int> s2, s3;
	Stack<int>::split(s1, s2, s3);
	cout << "s1 after split:" << s1;
	cout << "s2 after split:" << s2;
	cout << "s3 after split:" << s3;
	Stack<int>::combine(s2, s3);
	cout << "s2 after combine:" << s2;
	cout << "s3 after combine:" << s3;
	system("pause");
}