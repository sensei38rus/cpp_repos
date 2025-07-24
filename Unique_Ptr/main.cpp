#include "Unique_Ptr.h"
#include <iostream>



int main() {
	Unique_Ptr<int> ptr = make_unique<int>(10);
	*ptr = 15;
	std::cout << *ptr;
}