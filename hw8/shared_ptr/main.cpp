#include <iostream>
#include "shared_ptr.h"

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
	if ((p2.use_count() == 0) and (p3.use_count() == 1))
		std::cout << "OK 3" << std::endl;
	return 0;
}
