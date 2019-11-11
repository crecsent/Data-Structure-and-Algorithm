#include "Polynomial.h"
#include<cmath>

Polynomial::Polynomial()
{
}

Polynomial::Polynomial(const Polynomial & a)
{
	CircularList<Term>::iterator begin = a.poly.begin();
	CircularList<Term>::iterator end = a.poly.end();
	for (; begin != end; begin++)
		poly.insertBack(*begin);
}

const Polynomial & Polynomial::operator=(const Polynomial & a)
{
	poly.deleteChain();//����ԭ����ʽ��ռ�Ŀռ�
	CircularList<Term>::iterator begin = a.poly.begin();
	CircularList<Term>::iterator end = a.poly.end();
	for (; begin != end; begin++)
		poly.insertBack(*begin);
	return *this;
}

Polynomial Polynomial::operator+(const Polynomial & b) const
{
	Polynomial result;
	Term term;
	CircularList<Term>::iterator bi = b.poly.begin();
	CircularList<Term>::iterator ai = this->poly.begin();
	while (1)
	{
		if (ai->exp == bi->exp)
		{
			if (ai->exp == -1)//���������������������˱�ͷ���
				return result;
			else
			{
				int sum = ai->coef + bi->coef;
				if (sum)//��ϵ����Ϊ0
					result.poly.insertBack(term.set(sum, ai->exp));
				ai++; bi++;
			}
		}
		else if (ai->exp < bi->exp)
		{
			result.poly.insertBack(term.set(bi->coef, bi->exp));
			bi++;
		}
		else
		{
			result.poly.insertBack(term.set(ai->coef, ai->exp));
			ai++;
		}
	}
}

Polynomial Polynomial::operator-(const Polynomial & b) const
{
	Polynomial result;
	Term term;
	CircularList<Term>::iterator bi = b.poly.begin();
	CircularList<Term>::iterator ai = this->poly.begin();
	while (1)
	{
		if (ai->exp == bi->exp)
		{
			if (ai->exp == -1)
				return result;
			else
			{
				int sum = ai->coef - bi->coef;
				if (sum)
					result.poly.insertBack(term.set(sum, ai->exp));
				ai++; bi++;
			}
		}
		else if (ai->exp < bi->exp)
		{
			result.poly.insertBack(term.set(-bi->coef, bi->exp));//��b�Ǽ���������Ҫ��ת����
			bi++;
		}
		else
		{
			result.poly.insertBack(term.set(ai->coef, ai->exp));
			ai++;
		}
	}
}

Polynomial Polynomial::operator*(const Polynomial & b) const
{
	Polynomial result, temp;
	Term term;
	CircularList<Term>::iterator bi = b.poly.begin();
	CircularList<Term>::iterator bend = b.poly.end();
	CircularList<Term>::iterator ai;
	CircularList<Term>::iterator aend = this->poly.end();
	for (; bi != bend; bi++)//��b����ʽ������a��ˣ�ÿһ�ֵõ��ĳ˻������н����ӣ����յõ�����bʽ��aʽ�ĳ˻�
	{
		temp.poly.deleteChain();//�����һ�����µĶ���ʽ
		for (ai = this->poly.begin(); ai != aend; ai++)//biָ���b�еĵ�ǰĳ���aʽͨ��a�ĵ�����������ˣ�����ŵ�temp��
			temp.poly.insertBack(term.set(ai->coef*bi->coef, ai->exp + bi->exp));
		result = result + temp;//ÿһ�ֵõ��ĳ˻������н�����
	}
	return result;
}

double Polynomial::evaluate(double x) const
{
	CircularList<Term>::iterator begin = this->poly.begin();
	CircularList<Term>::iterator end = this->poly.end();
	double sum = 0;
	for (; begin != end; begin++)
		sum += begin->coef*pow(x, begin->exp);
	return sum;
}

Polynomial::~Polynomial()
{
	poly.deleteChain();//�黹����ͷ����������ڵ�Ŀռ�
}

istream& operator>>(istream & in, Polynomial& x)
{
	cout << "Enter the poly in the form \"n,c1,e1,c2,e2,...,cn,en\" in descending order: " << endl;
	char c = 0;
	int n=0, coef = 0, exp = 0;
	Term t;

	in >> n;
	while((c = getchar()) != '\n')
	{	
		in >> coef >> exp;
		t.coef = coef; t.exp = exp;
		x.poly.insertBack(t);
	} 

	return in;
}

ostream& operator<<(ostream & out, Polynomial& x)
{
	CircularList<Term>::CircularListIterator start = x.poly.begin();
	CircularList<Term>::CircularListIterator end = x.poly.end();
	for (; start != end; start++)
	{
		cout << start->coef << "*X^" << start->exp << " + ";
	}
	cout << endl;
	return out;
}
