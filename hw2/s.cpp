#include <iostream>
#include <string.h>

using namespace std;

class S{
	char* s;
	unsigned len;
public:
	S(){
		len = 0;
		s = new char('\0');
	}
	unsigned int length() const{
        return len;
  }
  const char* str(){
        return s;
  }
	S(char c){
		len = 1;
		s = new char;
		*s = c;
	}
	S(const string& A){
		len = A.length();
		s = new char [len];
		for (unsigned i = 0; i < len; i++){
			s[i] = A[i];
		}
	}
	S(const S& A){
		len = A.len;
		s = new char[len];
		for(unsigned i = 0;i < len; i++){
			s[i] = A.s[i];
		}
	}
	S(const char* A){
		len = strlen(A);
		s = new char[len];
		for(unsigned i = 0; i < len; i++){
			s[i] = A[i];
		}
	}
  char& operator[](unsigned i) {
        if (i < len) return s[i];
	}
    S operator + (const S& right) const{
        char* tmp = new char[len + right.len];
        for (unsigned i = 0; i < len; i++)
            tmp[i] = s[i];
        for (unsigned i = 0; i < right.len; i++)
            tmp[i + len] = right.s[i];
        return S(tmp);
    }
    S& operator+=(const S& right){
        (*this) = (*this) + right;
        return (*this);
    }

	friend ostream& operator <<(ostream&,const S&);
};

ostream& operator <<(ostream& out,const S& str){
    out << str.s;
	return out ;
}

