#include <list>
#include <algorithm>

namespace student {
	
	template <class T>
	class shared_ptr {
		T* ptr;
		std::list<shared_ptr<T> > *shared_list;
		typename std::list<shared_ptr<T> >::iterator shared_it;
	public:
		void f() {
			std::cout << "f size=" << shared_list->size() << std::endl;
		}
		shared_ptr() {
			ptr = NULL;
			shared_list = new std::list<shared_ptr<T> >;
		}
		shared_ptr(T* pointer) {
			ptr = pointer;
			shared_list = new std::list<shared_ptr<T> >;
			shared_list->push_back(*this);
			shared_it = shared_list->end()--;
		}
		shared_ptr(shared_ptr<T> &&other) {
//			this->ptr = other.ptr;
//			this->shared_list = new std::list<shared_ptr<T> >;
//			other.ptr = NULL;
//			other.shared_list->erase(other.shared_it);
//			*(this->shared_list) = *(other.shared_list);
//			std::list<shared_ptr<T> >* p = new std::list<shared_ptr<T> >;
//			std::cout << (this->shared_list==p) << "***************";
//			other.shared_list = p;
//			std::cout << (shared_list==p);
//			shared_list->push_back(*this);
//			shared_it = shared_list->end()--;
		}
		shared_ptr(shared_ptr<T> const &other) {
			ptr = other.ptr;
			shared_list = other.shared_list;
			shared_list->push_back(*this);
			shared_it = shared_list->end()--;
		}
//		~shared_ptr() {
//			shared_list.erase(std::find(shared_list.begin(), shared_list.end(), *this));
//			if (shared_list.size() == 0) {
//				delete ptr;
//			}
//		}
		T& operator * () {
			return *ptr;
		}
		T* operator -> () {return ptr;}
//		shared_ptr& operator =(shared_ptr<T> &&other) {
//			shared_list.erase(std::find(shared_list.begin(), shared_list.end(), *this));
//			ptr = other.ptr;
//			shared_list = other.shared_list;
//			other.ptr = NULL;
//			std::list<T> tmp;
//			other.shared_list = &tmp;	
//		}
//		shared_ptr& operator =(shared_ptr<T> const &other) {
//			shared_list.erase(std::find(shared_list.begin(), shared_list.end(), *this));
//			ptr = other.ptr;
//			shared_list = other.shared_list;
//			if (*this)
//				shared_list.push_back(*this);
//		}
//		void reset(T* pointer) {
//			shared_list.erase(std::find(shared_list.begin(), shared_list.end(), *this));
//			ptr = pointer;
//			std::list<T> tmp;
//			shared_list = &tmp;
//			if (*this)
//				shared_list.push_back(*this);
//		}
//		T* get() {return ptr;}
//		void swap(shared_ptr<T> &x) {
//			shared_list.erase(std::find(shared_list.begin(), shared_list.end(), *this));
//			x.shared_list.erase(std::find(shared_list.begin(), shared_list.end(), x));
//			T* tmp_ptr = ptr;
//			ptr = x.ptr;
//			x.ptr = tmp_ptr;
//			std::list<T> &tmp_list = shared_list;
//			shared_list = x.shared_list;
//			x.shared_list = tmp_list;
//			if (*this)
//				shared_list.push_back(*this);
//			if (x)
//				x.shared_list.push_back(x);
//		}
		operator bool() {return (ptr != NULL);}
		int use_count() {
			return shared_list->size();
		}
	};
}
