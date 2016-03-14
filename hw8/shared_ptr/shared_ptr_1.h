#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <list>
#include <vector>

namespace student {

template <class T>
class shared_ptr {
	T* ptr;
	std::vector<shared_ptr<T>* > * shared_arr;
	typename std::vector<shared_ptr<T>* >::iterator pos;
public:
	shared_ptr() {
		ptr = nullptr;
		shared_arr = new std::vector<shared_ptr<T>* >;
		pos = shared_arr->end();
	}
		//создание пустого объекта, который ничем не владеет
	shared_ptr(T* pointer){
		ptr = pointer;
		shared_arr = new std::vector<shared_ptr<T>* >;
		shared_arr->push_back(this);
		pos = shared_arr->begin();
	}
		//создание объекта, владеющего pointer
	shared_ptr(shared_ptr<T> &&other) {
		ptr = other.ptr;
		other.ptr = nullptr;
		other.shared_arr->erase(pos);
		shared_arr = other.shared_arr;
		other.shared_arr = new std::vector<shared_ptr<T>* >;
		shared_arr->push_back(this);
		pos = shared_arr->end()--;
	}

	//rvalue копирование
	shared_ptr(shared_ptr<T> const &other); //конструктор копирования, реализует равные права на владения обоими shared_ptr
	~shared_ptr(){}                    //разрушение объекта, которым владеет этот shared_ptr, если он больше никому не принадлежит
	T& operator * ();             //операторы разыменовывания
	T* operator -> ();
	shared_ptr& operator =(shared_ptr<T> &&x);      //присваивание rvalue
	shared_ptr& operator =(shared_ptr<T> const&x);  //присваивание (с разделением прав)
	void reset(T *p);                                  //смена владения с разрушением по необходимости предыдущего объекта
	T* get();                                       //необходимо отдать сырой указатель на объект, которым владеем
	void swap(shared_ptr<T> &x);                    //необходимо поменять местами объекты, которыми владеют this и x без разрушения и копирования оных
	operator bool() {return (ptr != nullptr);}
	//приведение к типу bool. true, если объект, которым владеем существует, false иначе
	int use_count() {
		return shared_arr->size();
	}//возвращает количество shared_ptr, разделяющих владение, включая данный};
};

template<class T>
class weak_ptr
{
public:
	weak_ptr();
	weak_ptr(weak_ptr const & other);
	weak_ptr(weak_ptr && other);
	weak_ptr(shared_ptr<T> const &master); 		//создание weak_ptr, разделяющего владение с shared
	~weak_ptr();
	weak_ptr& operator = (weak_ptr const & other);
	weak_ptr& operator = (weak_ptr && other);
	void swap (weak_ptr &other); 				//обмен без копирования и стирания
	void reset();								//сброс владения
	int use_count(); 							//число shared_ptr владеющих объектом
	bool expired();								//проверка на валидность. true, если объект "испортился", false, если объект валиден
	shared_ptr<T> lock();						//возвращает shared_ptr, владеющий тем же объектом
};

}
#endif // SHARED_PTR_H
