#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include"CircularList.h"

struct Term {
	int coef = -1;
	int exp = -1;
	Term set(int c, int e) { coef = c; exp = e; return *this; }
};
class Polynomial
{
	friend istream& operator>>(istream & in, Polynomial& x);
	friend ostream& operator<<(ostream & out, Polynomial& x);
public:
	Polynomial();
	Polynomial(const Polynomial& a);
	const Polynomial& operator=(const Polynomial & a);
	Polynomial operator+(const Polynomial& b) const;
	Polynomial operator-(const Polynomial& b) const;
	Polynomial operator*(const Polynomial& b) const;
	double evaluate(double x) const;
	~Polynomial();
private:
	CircularList<Term> poly;
};
#endif 
