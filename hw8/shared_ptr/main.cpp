#include <iostream>
#include "shared_ptr_storage.h"

using namespace student;

int main()
{
	std::cout << std::endl;

	shared_ptr<int> p1;
	if (!(p1) and (p1.use_count() == 0))
		std::cout << "OK 1" << std::endl;
	shared_ptr<int> p2(new int(2));
	if ((p2) and (p2.use_count() == 1))
		std::cout << "OK 2" << std::endl;
	shared_ptr<int> p3(std::move(p2));
	if ((p2.use_count() == 0) and (p3.use_count() == 1) and !(p2) and (*p3 == 2))
		std::cout << "OK 3" << std::endl;
	shared_ptr<int> p4(p3);
	if ((p3.use_count() == 2) and (p4.use_count() == 2) and (*p3 == 2) and (*p4 == 2))
		std::cout << "OK 4" << std::endl;
	shared_ptr<int> p5(p4);
	if ((p3.use_count() == 3 and p5.use_count() == 3) and (*p5 == 2))
		std::cout << "OK 5" << std::endl;
	shared_ptr<int> p6(std::move(p3));
	if ((p3.use_count() == 0) and (p6.use_count() == 3))
		std::cout << "OK 6" << std::endl;
	shared_ptr<int> p7(std::move(p1));
	if ((p7.use_count() == 0))
		std::cout << "OK 7" << std::endl;
	p7 = std::move(p6);
	p6.print(); p7.print();
// 0 0 0x.. 3
// it's ok
	std::cout << "OK 8" << std::endl;
	p6 = p7;
	p4.print(); p5.print(); p6.print(); p7.print();
// 0x.. 4 0x.. 4 0x.. 4 0x.. 4
	std::cout << "OK 9" << std::endl;
	p3.reset(new int(3));
	p5 = p3;
	p3.print(); p5.print(); p6.print();
// 0x.1 2 0x.1 2 0x.2 4
	std::cout << "OK 10" << std::endl;
	p5.swap(p6);
	p3.print(); p5.print(); p6.print();
// 0x.1 2 0x.2 4 0x.1 2
	std::cout << "OK 11" << std::endl;
	p1.reset(nullptr);
	p2 = p1;
	p3 = std::move(p2);
	p4.swap(p3);
	p1.print(); p2.print(); p3.print(); p4.print();
// 0 0 0 0 0x.. 4 0 0
	std::cout << "OK 12" << std::endl;

	weak_ptr<int> w1;
	weak_ptr<int> w2(w1);
	weak_ptr<int> w3(std::move(w2));
	weak_ptr<int> w4(p3);
	if (w4.use_count() == 3)
		std::cout << "OK 13" << std::endl;
	p3.reset(new int);
	if (w4.use_count() == 2)
		std::cout << "OK 14" << std::endl;
	p5.reset(nullptr);
	p7.reset(nullptr);
	if (w4.use_count() == 0 and w4.expired())
		std::cout << "OK 15" << std::endl;
	p6.reset(nullptr);
	p3.reset(nullptr);
	p1.reset(new int(10));
	weak_ptr<int> w5(p1);
	p2 = p1;
	weak_ptr<int> w6(p2);
	p3 = w6.lock();
	shared_ptr<int> p8(new int(20));
	w1 = p8;
	w2 = p8;
	w3 = p8;
	w4 = p8;
	p8.reset();
	p8 = w4.lock();
	return 0;
}
