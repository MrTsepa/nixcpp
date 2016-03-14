#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <list>
#include <vector>

namespace student {

template <class T>
class weak_ptr;

template <class T>
class shared_ptr {
	T* ptr;
	std::list<shared_ptr<T>* > * shared_arr;
	typename std::list<shared_ptr<T>* >::iterator pos;
public:
	shared_ptr() {
		ptr = nullptr;
		shared_arr = new std::list<shared_ptr<T>* >;
		pos = shared_arr->end();
	}
		//создание пустого объекта, который ничем не владеет
	shared_ptr(T* pointer){
		if (pointer == nullptr) {
			ptr = nullptr;
			shared_arr = new std::list<shared_ptr<T>* >;
			pos = shared_arr->end();
		} else {
			ptr = pointer;
			shared_arr = new std::list<shared_ptr<T>* >;
			shared_arr->push_back(this);
			pos = shared_arr->begin();
		}
	}
		//создание объекта, владеющего pointer
	shared_ptr(shared_ptr<T> &&other) {
		if (other) {
			ptr = other.ptr;
			other.ptr = nullptr;
			other.shared_arr->erase(other.pos);
			shared_arr = other.shared_arr;
			other.shared_arr = new std::list<shared_ptr<T>* >;
			other.pos = other.shared_arr->end();
			shared_arr->push_back(this);
			pos = shared_arr->end();
			pos--;
		} else {
			ptr = nullptr;
			shared_arr = new std::list<shared_ptr<T>* >;
			pos = shared_arr->end();
		}
	}
		//rvalue копирование
	shared_ptr(shared_ptr<T> const &other){
		if (other.ptr != nullptr) {
			ptr = other.ptr;
			shared_arr = other.shared_arr;
			shared_arr->push_back(this);
			pos = shared_arr->end();
			pos--;
		} else {
			ptr = nullptr;
			shared_arr = new std::list<shared_ptr<T>* >;
			pos = shared_arr->end();
		}
	}
		//конструктор копирования, реализует равные права на владения обоими shared_ptr
	~shared_ptr() {
		if (*this) {
			if (use_count() == 1) {
				delete ptr;
				delete shared_arr;
			}
		} else
			delete shared_arr;
	}
		//разрушение объекта, которым владеет этот shared_ptr, если он больше никому не принадлежит
	T& operator * () {return *ptr;}             //операторы разыменовывания
	T* operator -> () {return ptr;}
	shared_ptr& operator =(shared_ptr<T> &&other) {
		if (use_count() == 1) {
			delete ptr;
			delete shared_arr;
		}
		else if (use_count() != 0) {
			shared_arr->erase(pos);
		}
		if (other) {
			ptr = other.ptr;
			other.ptr = nullptr;
			other.shared_arr->erase(other.pos);
			shared_arr = other.shared_arr;
			other.shared_arr = new std::list<shared_ptr<T>* >;
			other.pos = other.shared_arr->end();
			shared_arr->push_back(this);
			pos = shared_arr->end();
			pos--;
		}
		else {
			ptr = nullptr;
			shared_arr = new std::list<shared_ptr<T>* >;
			pos = shared_arr->end();
		}
		return *this;
	}
		//присваивание rvalue
	shared_ptr& operator =(shared_ptr<T> const &other) {
		if (use_count() == 1) {
			delete ptr;
			delete shared_arr;
		}
		else if (use_count() != 0) {
			shared_arr->erase(pos);
		}
		if (other.ptr != nullptr) {
			ptr = other.ptr;
			shared_arr = other.shared_arr;
			shared_arr->push_back(this);
			pos = shared_arr->end();
			pos--;
		} else {
			ptr = nullptr;
			shared_arr = new std::list<shared_ptr<T>* >;
			pos = shared_arr->end();
		}
		return *this;
	}
		//присваивание (с разделением прав)
	void reset(T *pointer) {
		if (use_count() == 1) {
			delete ptr;
			delete shared_arr;
		}
		else if (use_count() != 0) {
			shared_arr->erase(pos);
		}
		if (pointer == nullptr) {
			ptr = nullptr;
			shared_arr = new std::list<shared_ptr<T>* >;
			pos = shared_arr->end();
		} else {
			ptr = pointer;
			shared_arr = new std::list<shared_ptr<T>* >;
			shared_arr->push_back(this);
			pos = shared_arr->begin();
		}
	}
		//смена владения с разрушением по необходимости предыдущего объекта
	T* get() {return ptr;}  //необходимо отдать сырой указатель на объект, которым владеем
	void swap(shared_ptr<T> &other) {
		if (*this)
			shared_arr->erase(pos);
		if (other)
			other.shared_arr->erase(other.pos);
		std::swap(shared_arr, other.shared_arr);
		std::swap(ptr, other.ptr);
		if (*this) {
			shared_arr->push_back(this);
			pos = shared_arr->end()--;
		}
		else
			pos = shared_arr->end();
		if (other) {
			other.shared_arr->push_back(&other);
			other.pos = other.shared_arr->end()--;
		} else
			other.pos = other.shared_arr->end();
	}
		//необходимо поменять местами объекты, которыми владеют this и x
	operator bool() {return (ptr != nullptr);}
	//приведение к типу bool. true, если объект, которым владеем существует, false иначе
	int use_count() {
		return shared_arr->size();
	}//возвращает количество shared_ptr, разделяющих владение, включая данный};
	void print() {
		std::cout << ptr << std::endl << use_count() << std::endl;
	}

	friend weak_ptr<T>;
};

template<class T>
class weak_ptr
{
	T* ptr;
	std::list<shared_ptr<T> *> *master_shared_arr;
public:
	weak_ptr() {
		ptr = nullptr;
		master_shared_arr = nullptr;
	}

	weak_ptr(weak_ptr const & other) {
		ptr = other.ptr;
		master_shared_arr = other.master_shared_arr;
	}

	weak_ptr(weak_ptr && other) {
		ptr = other.ptr;
		master_shared_arr = other.master_shared_arr;
		other.ptr = nullptr;
		other.master_shared_arr = nullptr;
	}

	weak_ptr(shared_ptr<T> const &master) {
		ptr = master.ptr;
		master_shared_arr = master.shared_arr;
	}
		//создание weak_ptr, разделяющего владение с shared
	~weak_ptr() {;}
	weak_ptr& operator = (weak_ptr const & other) {
		ptr = other.ptr;
		master_shared_arr = other.ptr;
		return *this;
	}

	weak_ptr& operator = (weak_ptr && other) {
		ptr = other.ptr;
		master_shared_arr = other.master_shared_arr;
		other.ptr = nullptr;
		other.master_shared_arr = nullptr;
		return *this;
	}

	void swap (weak_ptr &other) {
		std::swap(ptr, other.ptr);
		std::swap(master_shared_arr, other.master_shared_arr);
	}
		//обмен без копирования и стирания
	void reset() {
		ptr = nullptr;
		master_shared_arr = nullptr;
	}
		//сброс владения
	int use_count() {return master_shared_arr->size();} 	//число shared_ptr владеющих объектом
	bool expired() {
		return (ptr == nullptr);
	}
		//проверка на валидность. true, если объект "испортился", false, если объект валиден
	shared_ptr<T> lock() {
		if (expired()) {
			shared_ptr<T> tmp;
			return tmp;
		} else {
			shared_ptr<T> tmp(*(master_shared_arr->begin()));
			return tmp;
		}
	}
		//возвращает shared_ptr, владеющий тем же объектом
};

}
#endif // SHARED_PTR_H
