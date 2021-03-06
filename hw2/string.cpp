using namespace std;

size_t strlen(const char* c_str)
{
	size_t count = 0;
	while(*c_str++) ++count;
	return count;
}

class S{
	char* pStr;
	size_t len;
public:
	S(char);
	S(size_t x) {len = x; pStr = new char[x];}
	S(const char*);
	S(const string& A){
		len = A.length();
		pStr = new char[len+1];
		for(int i = 0; i < len; i++){
			pStr[i] = A[i];
		}
		pStr[len] = '\0';
	}
	S(const S&);
	S() {pStr = new char; len = 0; pStr[len] = '\0';}
	
	const char* str() const{return pStr;}
	size_t length() const{return len;}
	
	S operator+(const S &obj) const{
		char* tmp = new char[len + obj.length()+1];
		for (int i = 0; i < len; i++)
			tmp[i] = pStr[i];
		for (int i = 0; i < obj.length(); i++)
			tmp[i + len] = obj.str()[i];
		tmp[len + obj.length()] = '\0';
		return S(tmp);
	}
	S& operator+=(const S &obj){
		S tmp = (*this) + obj;
		len = tmp.length();
		delete[] pStr;
		pStr = new char[len+1];
		for(int i = 0; i < len; i++){
			pStr[i] = tmp[i];
		}
		pStr[len] = '\0';
		return (*this);
	}
	
	char& operator[](int i) {return pStr[i];}
	char& operator[](int i) const{return pStr[i];}

	friend ostream& operator<<(ostream&, const S&);
};

S::S(char a){
	pStr = new char[2];
	*pStr = a;
	len = 1;
	pStr[len] = '\0';
}

S::S(const char* str){
	len = strlen(str);
	pStr = new char[len+1];
	for (int i = 0; i < len; i++)
		pStr[i] = str[i];
	pStr[len] = '\0';
}

S::S(const S &obj){
	len = obj.len;
	pStr = new char[len+1];
	for(int i = 0; i < len; i++)
		pStr[i] = obj.pStr[i];
	pStr[len] = '\0';
}

ostream& operator<<(ostream& os, const S &obj){
//	if (obj.pStr) os << obj.pStr;
//	else os << "";
	for (int i = 0; i < obj.len; i++)
		os << obj[i];
	return os;
}
