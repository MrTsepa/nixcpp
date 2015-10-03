#include <iostream>

using namespace std;

class complex {
	double re, im;
	public:
	complex(double a, double b) {re = a; im = b;}
	complex(double a) {re = a; im = 0;}
	complex(){re = 0; im = 0;}

	double abs() {return sqrt(re*re+im*im);}
	
	complex operator+ (complex a, complex b)
	{
		complex res;
		res.re = a.re + b.re;
		res.im = a.im + b.im;
		return res;
	}	
	complex operator - (complex a, complex b)
	{
		complex res;
		res.re = a.re - b.re;
		res.im = a.im - b.im;
		return res;
	}
	complex operator / (complex a, complex b)
	{
		complex res;
		res.re = a.re / b.re;
		res.im = a.im / b.im;
		return res;
	}
	complex operator * (complex a, complex b)
	{
		complex res;
		res.re = a.re * b.re;
		res.im = a.im * b.im;
		return res;
	}
};

int main()
{
	return 0;
}
