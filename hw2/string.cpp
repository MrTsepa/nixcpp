using namespace std;

size_t strlen(const char* c_str)
{
	size_t count = 0;
	while(*c_str++) ++count;
	return count;
}

class S{
public:
	char* pStr;
	size_t len;
	S(char);
	S(size_t x) {len = x; pStr = new char[x];}
	S(const char*);
	S(const S&);
	S() {pStr = NULL; len = 0;}
	
	const char* str() {return pStr;}
	size_t length() {return len;}
	
	friend S operator+(S&, S&);
	friend S operator+(const char*, S&);
	friend S operator+(S&, const char*);
	void operator+=(S&);
	void operator+=(const char*);
	
	char& operator[](int i) {return pStr[i];}

	friend ostream& operator<<(ostream&, S);
};

S::S(char a){
	pStr = new char(a);
	len = 1;
}

S::S(const char* str){
	len = strlen(str);
	pStr = new char[len];
	for (int i = 0; i < len; i++)
		pStr[i] = str[i];
}

S::S(const S &obj){
	len = obj.len;
	pStr = new char(len);
	for(int i = 0; i < len; i++)
		pStr[i] = obj.pStr[i];
}

S operator+(S &obj1, S &obj2){
	size_t len1 = obj1.len, len2 = obj2.len;
	S res(len1+len2);
	for (int i = 0; i < len1; i++){
		res[i] = obj1[i];
	}
	for (int i = len1; i < res.len; i++){
		res[i] = obj2[i - len1];
	}
	return res;
}

S operator+(const char* str1, S &obj2){
	size_t len1 = strlen(str1), len2 = obj2.len;
	S res(len1+len2);
	for (int i = 0; i < len1; i++)
		res[i] = str1[i];
	for (int i = len1; i < res.len; i++)
		res[i] = obj2[i - len1];
	return res;
}

S operator+(S &obj1, const char* str2){
	size_t len1 = obj1.len, len2 = strlen(str2);
	S res(len1+len2);
	for (int i = 0; i < len1; i++)
		res[i] = obj1[i];
	for (int i = len1; i < res.len; i++)
		res[i] = str2[i - len1];
	return res;
}

void S::operator+=(S &obj){
	*this = *this + obj;
}

void S::operator+=(const char* str){
	*this = *this + str;
}

ostream& operator<<(ostream& os, S obj){
	for (int i = 0; i < obj.len; i++)
		os << obj[i];
	return os;
}
