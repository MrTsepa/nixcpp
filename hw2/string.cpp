#include <cstdlib>
#include <cstring>

using namespace std;

class S{
public:
    char* arr;
    S(char a){
        arr = (char*)malloc(sizeof(char)*1);
        arr[0] = a;
        arr[1] = '\0';
    }
    S(const char* str2){
        arr = (char*)malloc(sizeof(char)*(strlen(str2)+1));
        strcpy(arr, str2);
    }
    S(const S &obj){
        arr = (char*)malloc(sizeof(char)*(strlen(obj.arr)+1));
        strcpy(arr, obj.arr);
    }
    S() {arr = (char*)"";}

    ~S() {cout << "***" << arr << " "; free(arr);}

    const char* str() {return arr;}
    size_t length() {return strlen(arr);}

    S operator+(S &obj){
        char* res_str = (char*)malloc((this->length()+obj.length()+1)*sizeof(char));
        strcpy(res_str, this->str());
        strcat(res_str, obj.str());
        return S(res_str);
    }
    S operator+(char* str2){
        S obj = str2;
        char* res_str = (char*)malloc((this->length()+obj.length()+1)*sizeof(char));
        strcpy(res_str, this->str());
        strcat(res_str, obj.str());
        return S(res_str);
    }

    void operator+=(S &obj){
        *this = *this + obj;
    }

    char operator[](int i) {return arr[i];}
};


ostream &operator<< (ostream &os, S obj) {os << obj.arr; return os;}

S operator+(char* str1, S &obj2){
    S obj1 = str1;
    return obj1+obj2;
}

void operator+=(S &obj1, char* str2){
    S obj2 = str2;
    obj1 = obj1 + obj2;
}
