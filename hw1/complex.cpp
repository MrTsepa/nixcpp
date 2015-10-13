using namespace std;

class C {
public:
	double re, im;
	C(double a, double b) {re = a; im = b;}
	C(double a) {re = a; im = 0;}
	C(){}

	double abs() {return sqrt(re*re+im*im);}
	
	C operator+ (C &a) {
		return C(a.re + re, a.im + im);
	}
	C operator- (C &a) {
		return C(re - a.re, im - a.im);
	}
	C operator* (C &a) {
		return C(a.re*re - a.im*im, a.re*im + a.im*re);
	}
	C operator/ (C &a) {
		C x(a.re*re + a.im*im, a.re*im - a.im*re);
		x.re /= (a.re*a.re + a.im*a.im);
		x.im /= (a.re*a.re + a.im*a.im);
		return x;
	}
	bool operator == (C &a) {
		return (this->re == a.re) and (this->im == a.im);
	}
	bool operator != (C &a) {
		return (this->re != a.re) or (this->im != a.im);
	}
	friend ostream &operator<<(ostream &os, C obj);
};

ostream &operator<<(ostream &os, C obj){
	os << obj.re << " " << obj.im;
	return os;
}

C operator+(int i, C b) {return C(i) + b;}
C operator-(int i, C b) {return C(i) - b;}
C operator*(int i, C b) {return C(i) * b;}
C operator/(int i, C b) {return C(i) / b;}
bool operator==(int i, C b) {return C(i) == b;}
bool operator!=(int i, C b) {return C(i) != b;}
