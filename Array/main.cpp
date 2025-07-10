#include <iostream>
#include "Array.h"

int main() {
	try {
		Array<int, 5> arr{ 1,2,3,4,5 };
		auto arr2 = std::move(arr);
		std::cout << arr2 << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
