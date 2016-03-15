#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <list>
#include <vector>
#include <algorithm>

namespace student {

template <class T>
class shared_ptr;

template <class T>
class weak_ptr;

template <class T>
class Storage {
	T* ptr;
	int use_count;
	std::list<weak_ptr<T> *> * weak_arr;
public:
	Storage(T* pointer = nullptr) {
		ptr = pointer;
		if (ptr == nullptr) {
			use_count = 0;
			weak_arr = nullptr;
		}
		else {
			use_count = 1;
			weak_arr = new std::list<weak_ptr<T> *>;
		}
	}
	friend shared_ptr<T>;
	friend weak_ptr<T>;
};

template <class T>
class shared_ptr {
	Storage<T> * storage;
	void delete_self() {
		if (storage->use_count == 1 or storage->use_count == 0) {
			if (storage->ptr != nullptr)
				delete storage->ptr;
			storage->ptr = nullptr;
			storage->use_count = 0;
			if (storage->weak_arr != nullptr) {
				for (auto it = storage->weak_arr->begin();
				     it != storage->weak_arr->end(); it++) {
					(*it)->master_storage = nullptr;
				}
				storage->weak_arr->clear();
				delete storage->weak_arr;
				storage->weak_arr = nullptr;
			}
			delete storage;
		}
		else if (storage->use_count > 1){
			storage->use_count--;
		}
	}

public:
	shared_ptr() {
		storage = new Storage<T>(nullptr);
	}
		//создание пустого объекта, который ничем не владеет
	shared_ptr(T* pointer){
		storage = new Storage<T>(pointer);
	}
		//создание объекта, владеющего pointer
	shared_ptr(shared_ptr<T> &&other) {
//		delete_self();
		storage = other.storage;
		other.storage = new Storage<T>;
	}
		//rvalue копирование
	shared_ptr(shared_ptr<T> const &other){
//		delete_self();
		if (other.storage->ptr == nullptr) {
			storage = new Storage<T>(nullptr);
		}
		else {
			storage = other.storage;
			storage->use_count++;
		}
	}
		//конструктор копирования, реализует равные права на владения обоими shared_ptr
	~shared_ptr() {
		delete_self();
	}
		//разрушение объекта, которым владеет этот shared_ptr, если он больше никому не принадлежит
	T& operator * () {return *(storage->ptr);}             //операторы разыменовывания
	T* operator -> () {return storage->ptr;}
	shared_ptr& operator =(shared_ptr<T> &&other) {
		delete_self();
		storage = other.storage;
		other.storage = new Storage<T>;
		return *this;
	}
		//присваивание rvalue
	shared_ptr& operator =(shared_ptr<T> const &other) {
		delete_self();
		if (other.storage->ptr == nullptr) {
			storage = new Storage<T>(nullptr);
			return *this;
		}
		storage = other.storage;
		storage->use_count++;
		return *this;
	}
		//присваивание (с разделением прав)
	void reset(T *pointer = nullptr) {
		delete_self();
		storage = new Storage<T>(pointer);
	}
		//смена владения с разрушением по необходимости предыдущего объекта
	T* get() {return storage->ptr;}  //необходимо отдать сырой указатель на объект, которым владеем
	void swap(shared_ptr<T> &other) {
		std::swap(storage, other.storage);
	}
		//необходимо поменять местами объекты, которыми владеют this и x
	operator bool() {
		return (storage->ptr != nullptr and use_count() != 0);
	}
	//приведение к типу bool. true, если объект, которым владеем существует, false иначе
	int use_count() {
		return storage->use_count;
	}//возвращает количество shared_ptr, разделяющих владение, включая данный};
	void print() {
		std::cout << storage->ptr << std::endl << storage->use_count << std::endl;
	}

	friend weak_ptr<T>;
	friend Storage<T>;
};

template<class T>
class weak_ptr
{
	Storage<T> * master_storage;

	void erase_self() {
		if (master_storage == nullptr)
			return;
		if (master_storage->weak_arr == nullptr)
			return;
		master_storage->weak_arr->erase(std::find(master_storage->weak_arr->begin(),
						  master_storage->weak_arr->end(),
						  this));
	}
	void push_self() {
		if (master_storage == nullptr)
			return;
		if (master_storage->weak_arr == nullptr)
			master_storage->weak_arr = new std::list<weak_ptr *>;
		master_storage->weak_arr->push_back(this);
	}

public:
	weak_ptr() {
		master_storage = nullptr;
	}

	weak_ptr(weak_ptr const & other) {
		if (other.master_storage == nullptr) {
			master_storage = nullptr;
			return;
		}
		master_storage = other.master_storage;
		push_self();
	}

	weak_ptr(weak_ptr && other) {
		if (other.master_storage == nullptr) {
			master_storage = nullptr;
			return;
		}
		master_storage = other.master_storage;
		push_self();
		other.erase_self();
		other.master_storage = nullptr;
	}

	weak_ptr(shared_ptr<T> const &master) {
		if (master.storage->ptr != nullptr) {
			master_storage = master.storage;
			push_self();
		}
		else
			master_storage = nullptr;
	}
		//создание weak_ptr, разделяющего владение с shared
	~weak_ptr() {
		if (master_storage != nullptr) {
			erase_self();
			if (master_storage->ptr != nullptr and master_storage->use_count==0) {
				delete master_storage->ptr;
				master_storage->ptr = nullptr;
			}
			master_storage = nullptr;
		}
	}
	weak_ptr& operator = (weak_ptr const & other) {
		erase_self();
		if (other.master_storage == nullptr) {
			master_storage = nullptr;
			return *this;
		}
		master_storage = other.master_storage;
		push_self();
		return *this;
	}

	weak_ptr& operator = (weak_ptr && other) {
		erase_self();
		if (other.master_storage == nullptr) {
			master_storage = nullptr;
			return *this;
		}
		master_storage = other.master_storage;
		push_self();
		other.erase_self();
		other.master_storage = nullptr;
		return *this;
	}

	void swap (weak_ptr &other) {
		erase_self();
		other.erase_self();
		std::swap(master_storage, other.master_storage);
		push_self();
		other.push_self();
	}
		//обмен без копирования и стирания
	void reset() {
		erase_self();
		master_storage = nullptr;
	}
		//сброс владения
	int use_count() {
		if (master_storage == nullptr)
			return 0;
		return master_storage->use_count;
	} 	//число shared_ptr владеющих объектом
	bool expired() {
		if (master_storage == nullptr)
			return true;
		return (master_storage->ptr == nullptr);
	}
		//проверка на валидность. true, если объект "испортился", false, если объект валиден
	shared_ptr<T> lock() {
		if (master_storage == nullptr)
			return shared_ptr<T>(nullptr);
		shared_ptr<T> tmp;
		tmp.storage = master_storage;
		master_storage->use_count++;
		return tmp;
	}
		//возвращает shared_ptr, владеющий тем же объектом
	friend Storage<T>;
	friend shared_ptr<T>;
};

}
#endif // SHARED_PTR_H
