#include <cstdlib>
#include <cstring>

using namespace std;

class S{
    char* arr;
public:
    S(char a){
        arr = (char*)malloc(sizeof(char)*2);
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
    const char* str() {return arr;}
    size_t length() {return strlen(arr);}

    S operator+(S &obj){
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

ostream &operator<< (ostream &os, S &obj) {os << obj.str();}
